#ifndef NEW_BACKGAMMON_MYSTRATEGY_H
#define NEW_BACKGAMMON_MYSTRATEGY_H

typedef std::vector<std::vector<float>> Matrix;

#include <fstream>
#include <time.h>
#include "IStrategy.h"

class MyStrategy : public IStrategy {
private:
    float sigmoid(float a) {
        return (1 / (1 + std::exp(-a)));
    }

    Matrix DefaultMatrix(int a, int b) {
        srand((unsigned int)time(NULL) + rand());
        Matrix A(a, std::vector<float>(b));
        for (int i = 0; i != A.size(); ++i) {
            for (int j = 0; j != A[0].size(); ++j) {
                A[i][j] = (rand() % 100 - 50) / 100.0;
            }
        }
        return A;
    }
    
    Matrix MatrixProduct(Matrix& A, Matrix& B) {
        Matrix C(A.size(), std::vector<float>(B[0].size()));
        for (int i = 0; i != A.size(); ++i) {
            for (int j = 0; j != B[0].size(); ++j) {
                for (int k = 0; k != B.size(); ++k) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }   
        return C;
    }
   
    std::vector<float> Factors(const std::vector<int>& TPosition) {
    std::vector<float> factors;        
    int busy = 0;  // from 0 to 23
    int enemyBusy = 0;  // from 0 to 23        
    int checkersLeft = 0;
    int enemyCheckersLeft = 0;
    int checkersInHome = 0;
    int enemyCheckersInHome = 0;
    int barrier = 0, current1 = 0;
    int enemyBarrier = 0, current2 = 0;
    int distance = 0;
    int enemyDistance = 0;
    int blocked = 0, blacks = 0;
    int enemyBlocked = 0, whites = 0;

    for (int elem : TPosition) {
        if (elem > 0) {
            checkersLeft += elem;
            ++busy;
            ++current1;
            enemyBarrier += current2 * current2;
            current2 = 0;
        }
        if (elem < 0) {
            enemyCheckersLeft -= elem;
            ++enemyBusy;
            ++current2;
            barrier += current1 * current1;
            current1 = 0;
        }
        if (elem == 0) {
            barrier += current1 * current1;
            current1 = 0;
            enemyBarrier += current2 * current2;
            current2 = 0;
        }
        factors.push_back(busy);
        factors.push_back(enemyBusy);
    }
    factors.push_back(checkersLeft);
    factors.push_back(enemyCheckersLeft);
    factors.push_back(barrier);
    factors.push_back(enemyBarrier);

    for (int i = 18; i != 24; ++i) {
        if (TPosition[i] > 0) {
            checkersInHome += TPosition[i];
        }
    }
    for (int i = 6; i != 12; ++i) {
        if (TPosition[i] < 0) {
            enemyCheckersInHome -= TPosition[i];
        }
    }
    factors.push_back(checkersInHome);
    factors.push_back(enemyCheckersInHome);

    for (int i = 0; i != 24; ++i) {
        if (TPosition[i] > 0) {
            distance += (24 - i) * (24 - i);
        }
        if (TPosition[i] < 0) {
            enemyDistance += (24 - (i + 12) % 24) * (24 - (i + 12) % 24);
        }
    }
    factors.push_back(distance);
    factors.push_back(enemyDistance);

    return factors;      
}

public:
    MyStrategy();
    
    ~MyStrategy();
    
    TMove Move(const std::vector<int>& table, const std::vector<TMove>& possibleMoves) {
        const int s = 50, deep = 2;
        std::string coefs = "mycoefs2.txt";
        if (possibleMoves.size() == 0)  {
            return {{}};
        }
        else {
            TMove best = possibleMoves[0];
            float possibility = -1000000001, current = 0, coef = 0;
            
            std::vector<float> coefficients;

            Matrix A(s, std::vector<float>(Factors(table).size())), B(1, std::vector<float>(s));

            std::ifstream F;
            F.open(coefs, std::ios::in);
            for (int i = 0; i != s; ++i) {
                for (int j = 0; j != Factors(table).size(); ++j) {
                    F >> A[i][j];
                }
            }

            for (int i = 0; i != deep - 1; ++i) {
                for (int j = 0; j != s; ++j) {
                    for (int k = 0; k != s; ++k) {
                        F >> A[j][k];
                    }
                }
            }
            for (int i = 0; i != 1; ++i) {
                for (int j = 0; j != s; ++j) {
                    F >> B[i][j];
                }
            }
            F.close();
            for (TMove elem : possibleMoves) {
                Matrix V;
                for (float el : Factors(table)) V.push_back({el});
                Matrix output = MatrixProduct(A, V);
                for (auto el : output) {
                    el[0] = sigmoid(el[0]);
                }
                output = MatrixProduct(B, output);
                float current = sigmoid(output[0][0]);
                if (possibility < current) {
                    possibility = current;
                    best = elem;
                }
                current = 0;
            }
            return best;        
        }       
	};

};


#endif