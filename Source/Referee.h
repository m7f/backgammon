#ifndef NEW_BACKGAMMON_REFEREE_H
#define NEW_BACKGAMMON_REFEREE_H

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <math.h>
#include <ostream>
#include <set>
#include <string>
#include <time.h>
#include <vector>
#include <windows.h>

typedef std::vector<std::pair<int, int>> TMove;
typedef std::vector<TMove> TListOfMoves;
typedef std::set<TMove> TSetOfMoves;

class Referee {
public:
    bool IsWhite = true;

    bool IsGraphicMode = false;

    std::pair<int, int> RandomDice() {
		srand((unsigned int)time(NULL) + rand());
		return { rand() % 6 + 1, rand() % 6 + 1 };
	};

    std::vector<int> StartPosition() {
        std::vector<int> TPosition(24);
        TPosition[0] = 15;
        TPosition[12] = -15;
        return TPosition;
    }

    void ChangePlayers(std::vector<int>& TPosition) {
        for (int i = 0; i != 12; ++i) {
            std::swap(TPosition[i], TPosition[i + 12]);
            TPosition[i] *= -1;
            TPosition[i + 12] *= -1;
        }
        IsWhite = !IsWhite;
    }

    bool IsNotBlocked(std::vector<int>& TPosition, const std::pair<int, int> move) {
        --TPosition[move.first];
        if (move.second != -1) {
			++TPosition[move.second];
		}
		int count = 0;
        for (int i = 11; i >= 0; --i) {
            if (count == 6) {
                ++TPosition[move.first];
                if (move.second != -1) {
			        --TPosition[move.second];
		        }
                return false;
            }
            if (TPosition[i] < 0) {
		        ++TPosition[move.first];
                if (move.second != -1) {
			        --TPosition[move.second];
		        }
                return count < 6;
            } else if (TPosition[i] > 0) {
                ++count;
            } else {
                count = 0;
            }
        }
        for (int i = 23; i >= 12; --i) {
            if (count == 6) {
                ++TPosition[move.first];
                if (move.second != -1) {
			        --TPosition[move.second];
		        }
                return false;
            }
            if (TPosition[i] < 0) {
		        ++TPosition[move.first];
                if (move.second != -1) {
			        --TPosition[move.second];
		        }
                return count < 6;
            } else if (TPosition[i] > 0) {
                ++count;
            } else {
                count = 0;
            }
        }
        ++TPosition[move.first];
        if (move.second != -1) {
			--TPosition[move.second];
		}
        return count < 6;
	};

    bool CheckHome(std::vector<int>& TPosition) {
		for (auto i = TPosition.begin(); i != TPosition.begin() + 18; ++i) {
			if (*i > 0) {
				return true;
			}
		}
		return false;
	};

    bool CheckEnd(std::vector<int>& TPosition) {
		for (auto i = TPosition.begin(); i != TPosition.end(); ++i) {
			if (*i > 0) {
				return true;
			}
		}
        return false;
	};

    bool CanMove(std::vector<int>& TPosition, const int dice, const int start) {
        return TPosition[start] > 0 && start + dice < 24
            && TPosition[start + dice] >= 0 && IsNotBlocked(TPosition, { start, start + dice });
    }

    bool CanLeave(std::vector<int>& TPosition, const int dice, int start) {
        bool result = TPosition[start] > 0 && start + dice >= 24;
        if (start + dice > 24) {
            while (start-- != 18) {
                result = result && TPosition[start] <= 0;
            }
        }
        return result;
    }

    void PushMove(TMove& move, TSetOfMoves& variants) {
        if (variants.size() > 0) {
            if (move.size() == (*variants.begin()).size()) {
                variants.insert(move);
            }
            else if (move.size() > (*variants.begin()).size()) {
                variants.clear();
                variants.insert(move);
            }
        }
        else {
            variants.insert(move);
        }
    }

    void GetMove(std::vector<int>& TPosition, const std::pair<int, int> dice, TMove& move, TSetOfMoves& variants, int step, int weight, int& max) {
        int k = (step != 0 && (step != 2 || dice.first == dice.second)) * CheckHome(TPosition) + 18 * !CheckHome(TPosition);
        for (int i = k; i != 24; ++i) {
            int coord1 = i, coord2 = i + dice.first * (step == 0 || step == 3) + dice.second * (step == 1 || step == 2);
            if (!IsWhite) {
                if (coord1 >= 0 && coord1 <= 11) coord1 += 12; else coord1 -= 12;
                if (coord2 >= 0 && coord2 <= 11) coord2 += 12; else coord2 -= 12;
            }
            if (CanMove(TPosition, dice.first * (step == 0 || step == 3) + dice.second * (step == 1 || step == 2), i)) {
                move.push_back({ coord1, coord2 });
                --TPosition[i];
                ++TPosition[i + dice.first * (step == 0 || step == 3) + dice.second * (step == 1 || step == 2)];
                if (step == 0 || (step == 1 && dice.first == dice.second) || (step == 2)) {
                    GetMove(TPosition, dice, move, variants, step + 1, weight + dice.first * (step == 0 || step == 3) + dice.second * (step == 1 || step == 2), max);
                }
                if (max == weight + dice.first * (step == 0 || step == 3) + dice.second * (step == 1 || step == 2)) {
                    PushMove(move, variants);
                }
                else if (max < weight + dice.first * (step == 0 || step == 3) + dice.second * (step == 1 || step == 2)) {
                    variants.clear();
                    max = weight + dice.first * (step == 0 || step == 3) + dice.second * (step == 1 || step == 2);
                    PushMove(move, variants);
                }
                move.pop_back();
                ++TPosition[i];
                --TPosition[i + dice.first * (step == 0 || step == 3) + dice.second * (step == 1 || step == 2)];
            }
            if (!CheckHome(TPosition) && CanLeave(TPosition, dice.first * (step == 0 || step == 3) + dice.second * (step == 1 || step == 2), i)) {
                move.push_back({ coord1, -1 });
                --TPosition[i];
                if (step == 0 || (step == 1 && dice.first == dice.second) || (step == 2)) {
                    GetMove(TPosition, dice, move, variants, step + 1, weight + dice.first * (step == 0 || step == 3) + dice.second * (step == 1 || step == 2), max);
                }
                if (max == weight + dice.first * (step == 0 || step == 3) + dice.second * (step == 1 || step == 2)) {
                    PushMove(move, variants);
                }
                else if (max < weight + dice.first * (step == 0 || step == 3) + dice.second * (step == 1 || step == 2)) {
                    variants.clear();
                    max = weight + dice.first * (step == 0 || step == 3) + dice.second * (step == 1 || step == 2);
                    PushMove(move, variants);
                }
                move.pop_back();
                ++TPosition[i];
            }
        }
        if (step == 0) GetMove(TPosition, dice, move, variants, 2, (weight + dice.first * (step == 0 || step == 3) + dice.second * (step == 1 || step == 2)) * (dice.first == dice.second), max);
    }

    TListOfMoves PossibleMoves(std::vector<int>& TPosition, const std::pair<int, int> dice) {
        TListOfMoves variants;
        TSetOfMoves setVariants, justSet;
        TMove move;
        int max = 0;
        if (IsWhite && TPosition[0] == 15 && dice.first == 3 && dice.second == 3) {
            variants = { { { 0, 3 }, { 0, 3 }, { 3, 6 }, { 3, 6 } }, { { 0, 3 }, { 0, 3 }, { 3, 6 }, { 6, 9 } } };
        }
        else if (IsWhite && TPosition[0] == 15 && dice.first == 4 && dice.second == 4) {
            variants = { { { 0, 4 }, { 0, 4 }, { 4, 8 }, { 4, 8 } } };
        }
        else if (IsWhite && TPosition[0] == 15 && dice.first == 6 && dice.second == 6) {
            variants = { { { 0, 6 }, { 0, 6 } } };
        }
        else {
            GetMove(TPosition, dice, move, setVariants, 0, 0, max);

            for (TMove elem : setVariants) {
                variants.push_back(elem);
            }
        }
        return variants;
    }

    void ShowConsoleTable(std::vector<int>& TPosition) {
		int milliseconds = 0;
		Sleep(milliseconds);
		std::vector<std::vector<int>> table;
		for (int i = 0; i != 31; ++i) {
			std::vector<int> line;
			for (int j = 0; j != 12; ++j) {
				line.push_back(0);
			}
			table.push_back(line);
		}
		for (int j = 11; j >= 0; --j) {
			for (int i = 0; i != abs(TPosition[j]); ++i) {
				if (TPosition[j] > 0) {
					table[i][11 - j] = 1;
				}
				else if (TPosition[j] < 0) {
					table[i][11 - j] = 2;
				}
			}
		}
		for (int j = 0; j != 12; ++j) {
			for (int i = 30; i != 30 - abs(TPosition[j + 12]); --i) {
				if (TPosition[j + 12] > 0) {
					table[i][j] = 1;
				}
				else if (TPosition[j + 12] < 0) {
					table[i][j] = 2;
				}
			}
		}
		int count = 0;
		for (int i = 0; i != 12; ++i) {
			std::cout << std::setw(5) << 11 - i;
			++count;
			if (count == 6) {
				std::cout << "  ";
			}
		}
		count = 0;
		std::cout << "\n\n";
		for (auto row : table) {
			for (int elem : row) {
				if (elem == 1) {
					std::cout << std::setw(5) << "W";
				}
				else if (elem == 2) {
					std::cout << std::setw(5) << "B";
				}
				else {
					std::cout << std::setw(5) << ".";
				}
				++count;
				if (count == 6) {
					std::cout << "  ";
				}
			}
			count = 0;
			std::cout << "\n";
		}
		std::cout << "\n";
		for (int i = 0; i != 12; ++i) {
			std::cout << std::setw(5) << i + 12;
			++count;
			if (count == 6) {
				std::cout << "  ";
			}
		}
		std::cout << "\n\n";
	};

};

#endif
