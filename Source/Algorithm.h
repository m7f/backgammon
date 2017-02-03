#ifndef NEW_BACKGAMMON_ALGORITHM_H
#define NEW_BACKGAMMON_ALGORITHM_H

#include "Referee.h"

typedef std::vector<std::vector<double>> Matrix;

class Algorithm : public Referee {
public:
    double sigmoid(double a) {
        return (1 / (1 + std::exp(-a)));
    }

    Matrix DefaultMatrix(int a, int b) {
        srand((unsigned int)time(NULL) + rand());
        Matrix A(a, std::vector<double>(b));
        for (int i = 0; i != A.size(); ++i) {
            for (int j = 0; j != A[0].size(); ++j) {
                A[i][j] = (rand() % 100 - 50) / 100.0;
            }
        }
        return A;
    }

    Matrix MatrixProduct(Matrix& A, Matrix& B) {
        Matrix C(A.size(), std::vector<double>(B[0].size()));
        for (int i = 0; i != A.size(); ++i) {
            for (int j = 0; j != B[0].size(); ++j) {
                for (int k = 0; k != B.size(); ++k) {
                    C[i][j] += A[i][k] * B[k][j];
                }
            }
        }
        return C;
    }

    TMove DoMove(std::vector<int>& TPosition, const TMove move) {
        for (auto elem : move) {
            int coord1 = elem.first, coord2 = elem.second;
            if (!IsWhite) {
                if (coord1 >= 0 && coord1 <= 11) coord1 += 12; else coord1 -= 12;
                if (coord2 >= 0 && coord2 <= 11) coord2 += 12; else coord2 -= 12;
            }
            --TPosition[coord1];
            if (elem.second != -1) ++TPosition[coord2];
        }
        return move;
    }

    TMove RandomStrategy(std::vector<int>& TPosition) {
        TListOfMoves moves = PossibleMoves(TPosition, RandomDice());
        if (moves.size() == 0) {
            return DoMove(TPosition, {});
        }
        else {
            return DoMove(TPosition, moves[rand() % moves.size()]);
        }
    }

    TMove GreedyStrategy(std::vector<int>& TPosition) {
        TListOfMoves moves = PossibleMoves(TPosition, RandomDice());
        if (moves.size() == 0) {
            return DoMove(TPosition, {});
        }
        else {
            return DoMove(TPosition, moves[0]);
        }
    }

    TMove LinearModelStrategy(std::vector<int>& TPosition, std::vector<double>& factors, std::string coefs) {
        TListOfMoves moves = PossibleMoves(TPosition, RandomDice());
        if (moves.size() == 0)  {
            return DoMove(TPosition, {});
        }
        else {
            TMove best = moves[0];
            float possibility = -1000000001, current = 0, coef = 0;

            std::vector<float> coefficients;

            std::ifstream F;
            F.open(coefs, std::ios::in);
            for (int i = 0; i != factors.size(); ++i) {
                F >> coef;
                coefficients.push_back(coef);
            }
            F.close();
            for (TMove elem : moves) {
                for (int i = 0; i != factors.size(); ++i) {
                    current += coefficients[i] * factors[i];
                }
                if (possibility < current) {
                    possibility = current;
                    best = elem;
                }
                current = 0;
            }
            return DoMove(TPosition, best);
        }
    }

    TMove NeuralNetworkStrategy(std::vector<int>& TPosition, std::vector<double>& factors, std::string coefs, int s, int deep) {
        TListOfMoves moves = PossibleMoves(TPosition, RandomDice());
        if (moves.size() == 0)  {
            return DoMove(TPosition, {});
        }
        else {
            TMove best = moves[0];
            float possibility = -1000000001, current = 0, coef = 0;

            std::vector<double> coefficients;

            Matrix A(s, std::vector<double>(factors.size())), B(1, std::vector<double>(s));


            std::ifstream F;
            F.open(coefs, std::ios::in);
            for (int i = 0; i != s; ++i) {
                for (int j = 0; j != factors.size(); ++j) {
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
            for (TMove elem : moves) {
                Matrix V;
                for (double el : factors) V.push_back({el});
                Matrix output = MatrixProduct(A, V);
                for (auto el : output) {
                    el[0] = sigmoid(el[0]);
                }
                output = MatrixProduct(B, output);
                double current = sigmoid(output[0][0]);
                if (possibility < current) {
                    possibility = current;
                    best = elem;
                }
                current = 0;
            }
            return DoMove(TPosition, best);
        }
    }

    TMove ChooseStrategy(std::vector<int>& TPosition, std::string name) {
		if (name == "Random") {
			return RandomStrategy(TPosition);
		}
        if (name == "Greedy") {
            return GreedyStrategy(TPosition);
        }

        if (name == "Regression") {
            return LinearModelStrategy(TPosition, Factors(TPosition),
            "../Debug/output/coefficients80.txt");
        }
        if (name == "Gradient") {
            return LinearModelStrategy(TPosition, Factors(TPosition),
            "../Debug/output/gradientcoefs90.txt");
        }
        if (name == "Neuron1G") {
            return NeuralNetworkStrategy(TPosition, Factors(TPosition),
            "../Debug/output/gradientneuron.txt", 40, 1);
        }
        if (name == "Neuron2G") {
            return NeuralNetworkStrategy(TPosition, Factors(TPosition),
            "../Debug/output/gradientneuron.txt", 40, 2);
        }
        if (name == "MLPNeuron") {
            return NeuralNetworkStrategy(TPosition, Factors(TPosition),
            "../Debug/output/mlpregressor.txt", 40, 1);
        }
	}

    std::vector<float> GradientDescent(int step) {
        std::vector<int> TPosition = StartPosition();
        std::vector<double> first, second;
        first = Factors(TPosition);
        std::vector<float> coefs(first.size(), 1);
        for (int z = 1; z != step + 1; ++z) {
            std::cout << z << "\n";
            TPosition = StartPosition();
            IsWhite = true;
            while (CheckEnd(TPosition)) {
                first = Factors(TPosition);
                ChooseStrategy(TPosition, "Random");
			    if (CheckEnd(TPosition)) ChangePlayers(TPosition);
			    ChooseStrategy(TPosition, "Random");
                if (CheckEnd(TPosition)) ChangePlayers(TPosition);
                second = Factors(TPosition);
                float c = 0, lNorm = 0;
                for (int i = 0; i != first.size(); ++i) {
                    c += coefs[i] * (first[i] - second[i]);
                    lNorm += (coefs[i] * (first[i] - second[i])) * (coefs[i] * (first[i] - second[i]));
                }
                lNorm = sqrt(lNorm);
                for (int i = 0; i != coefs.size(); ++i) {
                    int sign = 1;
                    if (c < 0) sign = -1;
                    coefs[i] -= 0.01 * sign * (first[i] - second[i]);
                    if (lNorm != 0) {
                        coefs[i] /= lNorm;
                    }
                }
            }
        }
        return coefs;
    }

    void GenerateGradientCoefs(int step) {
        std::ofstream F;
        std::string file = "../Debug/output/gradientcoefs.txt";
        F.open(file, std::ios::out);
        for (double elem : GradientDescent(step)) {
            F << elem << " ";
        }
        F.close();
    }

    std::vector<Matrix> NeuralNetwork_1(int s, int step) {
        double output1, output2;
        std::vector<int> TPosition = StartPosition();
        std::vector<double> first, second;
        first = Factors(TPosition);
        Matrix A = DefaultMatrix(s, first.size()), B = DefaultMatrix(1, s), V1(first.size()), hidden1, V2(first.size()), hidden2;
        Matrix A1(s, std::vector<double>(first.size()));
        Matrix B1(1, std::vector<double>(s));
        Matrix A2(s, std::vector<double>(first.size()));
        Matrix B2(1, std::vector<double>(s));

        for (int z = 1; z != step + 1; ++z) {
            std::cout << z << "\n";
            TPosition = StartPosition();
            IsWhite = true;
            while (CheckEnd(TPosition)) {

                first = Factors(TPosition);
                ChooseStrategy(TPosition, "Random");
			    if (CheckEnd(TPosition)) ChangePlayers(TPosition);
			    ChooseStrategy(TPosition, "Random");
                if (CheckEnd(TPosition)) ChangePlayers(TPosition);
                second = Factors(TPosition);



                for (int i = 0; i != V1.size(); ++i) V1[i] = {first[i]};
                hidden1 = MatrixProduct(A, V1);
                for (auto elem : hidden1) {
                    elem[0] = {sigmoid(elem[0])};
                }
                output1 = sigmoid(MatrixProduct(B, hidden1)[0][0]);
                std::vector<double> d_hidden1(s);
                for (int i = 0; i != s; ++i) {
                    d_hidden1[i] = hidden1[i][0] * output1 * (1 - output1);
                }
                for (int i = 0; i != s; ++i) {
                    for (int j = 0; j != first.size(); ++j) {
                        A1[i][j] = d_hidden1[i] * V1[j][0];
                    }
                }
                for (int i = 0; i != 1; ++i) {
                    for (int j = 0; j != s; ++j) {
                        B1[i][j] = d_hidden1[j] * hidden1[i][0];
                    }
                }



                for (int i = 0; i != V2.size(); ++i) V2[i] = {second[i]};
                hidden2 = MatrixProduct(A, V2);
                for (auto elem : hidden2) {
                    elem[0] = {sigmoid(elem[0])};
                }
                output2 = sigmoid(MatrixProduct(B, hidden2)[0][0]);
                std::vector<double> d_hidden2(s);
                for (int i = 0; i != s; ++i) {
                    d_hidden2[i] = hidden2[i][0] * output2 * (1 - output2);
                }
                for (int i = 0; i != s; ++i) {
                    for (int j = 0; j != second.size(); ++j) {
                        A2[i][j] = d_hidden2[i] * V2[j][0];
                    }
                }
                for (int i = 0; i != 1; ++i) {
                    for (int j = 0; j != s; ++j) {
                        B2[i][j] = d_hidden2[j] * hidden2[i][0];
                    }
                }



                for (int i = 0; i != s; ++i) {
                    for (int j = 0; j != first.size(); ++j) {
                        A[i][j] -= 0.01 * 2 * (output1 - output2) * (A1[i][j] - A2[i][j]);
                    }
                }
                for (int i = 0; i != 1; ++i) {
                    for (int j = 0; j != s; ++j) {
                        B[i][j] -= 0.01 * 2 * (output1 - output2) * (B1[i][j] - B2[i][j]);
                    }
                }
            }
            if (IsWhite) {
                for (int i = 0; i != s; ++i) {
                    for (int j = 0; j != first.size(); ++j) {
                        A[i][j] -= 0.01 * 2 * (-output1) * (A1[i][j]);
                    }
                }
                for (int i = 0; i != 1; ++i) {
                    for (int j = 0; j != s; ++j) {
                        B[i][j] -= 0.01 * 2 * (output1) * (B1[i][j]);
                    }
                }
            } else {
                 for (int i = 0; i != s; ++i) {
                    for (int j = 0; j != first.size(); ++j) {
                        A[i][j] -= 0.01 * 2 * (output1) * (-A1[i][j]);
                    }
                }
                for (int i = 0; i != 1; ++i) {
                    for (int j = 0; j != s; ++j) {
                        B[i][j] -= 0.01 * 2 * (-output1) * (-B1[i][j]);
                    }
                }

            }
        }
        return {A, B};
    }

    std::vector<Matrix> NeuralNetwork_2(int s, int step) {
    double output1, output2;
    std::vector<int> TPosition = StartPosition();
    std::vector<double> first, second;
    first = Factors(TPosition);
    Matrix A = DefaultMatrix(s, first.size()), B = DefaultMatrix(s, s), C = DefaultMatrix(1, s), V1(first.size()), hidden1, V2(first.size()), hidden2, hidden3, hidden4;
    Matrix A1(s, std::vector<double>(first.size()));
    Matrix A2(s, std::vector<double>(first.size()));
    Matrix B1(s, std::vector<double>(s));
    Matrix B2(s, std::vector<double>(s));
    Matrix C1(1, std::vector<double>(s));
    Matrix C2(1, std::vector<double>(s));

    for (int z = 1; z != step + 1; ++z) {
        std::cout << z << "\n";
        TPosition = StartPosition();
        IsWhite = true;
        while (CheckEnd(TPosition)) {

            first = Factors(TPosition);
            ChooseStrategy(TPosition, "Random");
			if (CheckEnd(TPosition)) ChangePlayers(TPosition);
			ChooseStrategy(TPosition, "Random");
            if (CheckEnd(TPosition)) ChangePlayers(TPosition);
            second = Factors(TPosition);



            for (int i = 0; i != V1.size(); ++i) V1[i] = {first[i]};
            hidden1 = MatrixProduct(A, V1);
            for (auto elem : hidden1) {
                elem[0] = {sigmoid(elem[0])};
            }
            hidden3 = MatrixProduct(B, hidden1);
            for (auto elem : hidden3) {
                elem[0] = {sigmoid(elem[0])};
            }
            output1 = sigmoid(MatrixProduct(C, hidden3)[0][0]);

            std::vector<double> d_hidden1(s), d_hidden3(s);

            for (int i = 0; i != s; ++i) {
                d_hidden3[i] = hidden3[i][0] * output1 * (1 - output1);
                for (int j = 0; j != s; ++j) {
                    d_hidden1[i] += B[i][j] * d_hidden3[j];
                }
            }

            for (int i = 0; i != s; ++i) {
                for (int j = 0; j != first.size(); ++j) {
                    A1[i][j] = d_hidden1[j] * V1[i][0];
                }
            }
            for (int i = 0; i != s; ++i) {
                for (int j = 0; j != s; ++j) {
                    B1[i][j] = d_hidden1[j] * hidden3[i][0];
                }
            }
            for (int i = 0; i != 1; ++i) {
                for (int j = 0; j != s; ++j) {
                    C1[i][j] = d_hidden3[j] * output1;
                }
            }

            for (int i = 0; i != V2.size(); ++i) V2[i] = {second[i]};
            hidden2 = MatrixProduct(A, V2);
            for (auto elem : hidden2) {
                elem[0] = {sigmoid(elem[0])};
            }
            hidden4 = MatrixProduct(B, hidden2);
            for (auto elem : hidden4) {
                elem[0] = {sigmoid(elem[0])};
            }
            output2 = sigmoid(MatrixProduct(C, hidden4)[0][0]);

            std::vector<double> d_hidden2(s), d_hidden4(s);

            for (int i = 0; i != s; ++i) {
                d_hidden4[i] = hidden4[i][0] * output2 * (1 - output2);
                for (int j = 0; j != s; ++j) {
                    d_hidden2[i] += B[i][j] * d_hidden4[j];
                }
            }

            for (int i = 0; i != s; ++i) {
                for (int j = 0; j != second.size(); ++j) {
                    A2[i][j] = d_hidden2[j] * V2[i][0];
                }
            }
            for (int i = 0; i != s; ++i) {
                for (int j = 0; j != s; ++j) {
                    B2[i][j] = d_hidden2[j] * hidden4[i][0];
                }
            }
            for (int i = 0; i != 1; ++i) {
                for (int j = 0; j != s; ++j) {
                    C2[i][j] = d_hidden4[j] * output2;
                }
            }

            for (int i = 0; i != s; ++i) {
                for (int j = 0; j != first.size(); ++j) {
                    A[i][j] -= 0.01 * 2 * (output1 - output2) * (A1[i][j] - A2[i][j]);
                }
            }
            for (int i = 0; i != s; ++i) {
                for (int j = 0; j != s; ++j) {
                    B[i][j] -= 0.01 * 2 * (output1 - output2) * (B1[i][j] - B2[i][j]);
                }
            }
            for (int i = 0; i != 1; ++i) {
                for (int j = 0; j != s; ++j) {
                    C[i][j] -= 0.01 * 2 * (output1 - output2) * (C1[i][j] - C2[i][j]);
                }
            }


        }
        if (IsWhite) {
            for (int i = 0; i != s; ++i) {
                for (int j = 0; j != first.size(); ++j) {
                    A[i][j] -= 0.01 * 2 * (-output1) * (A1[i][j]);
                }
            }
            for (int i = 0; i != s; ++i) {
                for (int j = 0; j != s; ++j) {
                    B[i][j] -= 0.01 * 2 * (output1) * (B1[i][j]);
                }
            }
            for (int i = 0; i != 1; ++i) {
                for (int j = 0; j != s; ++j) {
                    C[i][j] -= 0.01 * 2 * (-output1) * (C1[i][j]);
                }
            }
        } else {
                for (int i = 0; i != s; ++i) {
                for (int j = 0; j != first.size(); ++j) {
                    A[i][j] -= 0.01 * 2 * (output1) * (-A1[i][j]);
                }
            }
            for (int i = 0; i != s; ++i) {
                for (int j = 0; j != s; ++j) {
                    B[i][j] -= 0.01 * 2 * (-output1) * (-B1[i][j]);
                }
            }
            for (int i = 0; i != 1; ++i) {
                for (int j = 0; j != s; ++j) {
                    C[i][j] -= 0.01 * 2 * (output1) * (C1[i][j]);
                }
            }

        }
    }
    return {A, B, C};
}

    void GenerateNeuralGradientCoefs(int s, int step) {
        std::ofstream F;
        std::string file = "../Debug/output/gradientneuron.txt";
        F.open(file, std::ios::out);

        for (auto elem : NeuralNetwork_2(s, step)) {
            for (int i = 0; i != elem.size(); ++i) {
                for (int j = 0; j != elem[0].size(); ++j) {
                    F << elem[i][j] << " ";
                }
            }
        }
        F.close();
    }

    std::vector<double> Factors(std::vector<int>& TPosition) {
        std::vector<double> factors;
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

    bool PlayGame(std::vector<int>& TPosition, std::string WhiteStrategy, std::string BlackStrategy, std::set<std::vector<int>>& positions, bool list) {
        std::vector<int> Start = TPosition;
        while (CheckEnd(TPosition)) {
            ChooseStrategy(TPosition, WhiteStrategy);
            if (list) positions.insert(TPosition);
            //ShowConsoleTable(TPosition);
            //for (int elem : TPosition) std::cout << elem << " "; std::cout << "\n";
            //Sleep(2500);
			if (CheckEnd(TPosition)) ChangePlayers(TPosition);
			ChooseStrategy(TPosition, BlackStrategy);
            if (CheckEnd(TPosition)) ChangePlayers(TPosition);
            if (list) positions.insert(TPosition);
            //ShowConsoleTable(TPosition);
            //for (int elem : TPosition) std::cout << elem << " "; std::cout << "\n";
            //Sleep(2500);
        }
//        if (IsWhite) {
//			std::cout << "White wins!\n";
//		}
//		else {
//			std::cout << "Black wins!\n";
//		}
        TPosition = Start;
        bool winner = IsWhite;
		IsWhite = true;
		return winner;
    }

    double CompareStrategies(std::vector<int>& TPosition, std::string WhiteStrategy, std::string BlackStrategy, int games) {
        int whiteWins = 0, blackWins = 0;
        std::set<std::vector<int>> positions;
        int k;
		for (long long i = 0; i != games; ++i) {
			std::cout << i << " - ";
            if (whiteWins + blackWins != 0) k = 100 * whiteWins / (whiteWins + blackWins);
            else k = 100;
            std::cout << k << "%\n";
			if (PlayGame(TPosition, WhiteStrategy, BlackStrategy, positions, false)) {
				++whiteWins;
			}
			else {
				++blackWins;
			}
		}
		return 100 * whiteWins / (whiteWins + blackWins);
	}

    void GenerateDataset(std::string file, std::vector<int>& TPosition, std::string WhiteStrategy, std::string BlackStrategy, int games1, int games2) {
		int whiteWins = 0, blackWins = 0;
        std::ofstream output;
        std::set<std::vector<int>> positions;
		for (long long i = 0; i != games1; ++i) {
			if (PlayGame(TPosition, WhiteStrategy, BlackStrategy, positions, true)) {
				++whiteWins;
			}
			else {
				++blackWins;
			}
		}
        int size = positions.size();
        int k = 0;
        output.open(file);
        for (std::vector<int> pos : positions) {
            std::cout << ++k << "/" << size << "\n";
            double p = CompareStrategies(pos, WhiteStrategy, BlackStrategy, games2);
            output << p << " ";
            for (int elem : Factors(pos)) {
                output << elem << " ";
            }
            output << "\n";
        }
        output.close();
	}

    void TestReferee(std::string file) {
        std::string output = "../Debug/output/clone.txt";

        if (true) {
            std::ofstream clone;
            std::ifstream read;
            int a;
            char b;
            char player[8];
            int color;
            std::vector<int> position;
            std::pair<int, int> dice = {0, 0};
            std::pair<int, int> step;
            TMove move;
            TListOfMoves moves;
            read.open(file, std::ios::in);
            clone.open(output, std::ios::out);
            while (!read.eof()) {
                IsWhite = true;
                read >> player;
                read >> color;
                if (!(dice.first == 0 && dice.second == 0)) clone << "P";
                clone << player << " " << color <<  "\n";
                for (int i = 0; i != 24; ++i) {
                    read >> a;
                    position.push_back(a);
                    if (i != 23) read >> b;
                }
                for (int i = 0; i != 24; ++i) {
                    clone << position[i];
                    if (i != 23) clone << ',';
                }
                clone << "\n";
                read >> a;
                dice.first = a;
                read >> a;
                dice.second = a;
                read >> b;
                clone << dice.first << " " << dice.second << "\n";
                if (color == 1) ChangePlayers(position);
                for (auto elem : PossibleMoves(position, dice)) {
                    for (auto el : elem) {
                        clone << "(" << el.first << ", " << el.second << ") ";
                    }
                    clone << "\n";
                }
                position.resize(0);
                while (b != 'P' && !read.eof()) {
                    read >> b;
                }
            }
            read.close();
            clone.close();
        }



        std::cout << "Ready\n";
        std::ifstream readCompare, cloneCompare;
        readCompare.open(file, std::ios::in);
        cloneCompare.open(output, std::ios::in);
        std::string a1, a2;
        while (!readCompare.eof()) {
            readCompare >> a1;
            cloneCompare >> a2;
            //std::cout << a1 << "\n";
            //std::cout << a2 << "\n";
            if (a1 != a2) {
                std::cout << "ERROR\n";

                for (int i = 0; i != 30; ++i) {
                    std::cout << a1;
                    readCompare >> a1;
                }
                std::cout << "\n";
                for (int i = 0; i != 30; ++i) {
                    std::cout << a2;
                    cloneCompare >> a2;
                }

                break;
            }
        }
        std::cout << "WELL DONE!";
        readCompare.close();
        cloneCompare.close();
    }









};

#endif
