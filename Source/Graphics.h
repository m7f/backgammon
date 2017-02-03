#ifndef NEW_BACKGAMMON_GRAPHICS_H
#define NEW_BACKGAMMON_GRAPHICS_H

#include <SFML/Graphics.hpp>
#include "Algorithm.h"

class Graphics: public Algorithm {
public:
    const int StandartSpeed = 10;

    const int EnemySpeed = 30;

    int Speed = StandartSpeed;

    const int Y = 11;

    void MainMenu(sf::RenderWindow& window) {
        IsGraphicMode = true;
		sf::Texture menuTexture1, menuTexture2;
		menuTexture1.loadFromFile("../Images/newgame.jpg");
		menuTexture2.loadFromFile("../Images/exit.jpg");
		sf::Sprite menu1(menuTexture1);
		sf::Sprite menu2(menuTexture2);
		bool isMenu = 1;
		int menuNum;
		menu1.setPosition(150, 170);
		menu2.setPosition(150, 245);
		while (isMenu) {
			menu1.setColor(sf::Color(129, 181, 221));
			menu2.setColor(sf::Color(129, 181, 221));
			menuNum = 0;
			window.clear(sf::Color(129, 181, 221));
            if (sf::IntRect(150, 170, 300, 30).contains(sf::Mouse::getPosition(window))) { menu1.setColor(sf::Color::White); menuNum = 1; }
			if (sf::IntRect(150, 245, 300, 30).contains(sf::Mouse::getPosition(window))) { menu2.setColor(sf::Color::White); menuNum = 2; }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {};
				if (menuNum == 1) {
					window.clear();
                    NewGameMenu(window);
				}
				if (menuNum == 2) {
					isMenu = false;
				}
			}
			window.draw(menu1);
			window.draw(menu2);
			window.display();
		}
	}

    void NewGameMenu(sf::RenderWindow& window) {
		sf::Texture menuTexture1, menuTexture2, menuTexture3, menuTexture4, menuTexture5, menuTexture6, menuTexture7, menuTexture8, menuTexture9, menuTexture10, startTexture, exitTexture;
		menuTexture1.loadFromFile("../Images/player1.jpg");
		menuTexture2.loadFromFile("../Images/player2.jpg");
		menuTexture3.loadFromFile("../Images/random.jpg");
		menuTexture4.loadFromFile("../Images/random.jpg");
		menuTexture5.loadFromFile("../Images/greedy.jpg");
		menuTexture6.loadFromFile("../Images/greedy.jpg");
		menuTexture7.loadFromFile("../Images/regression.jpg");
		menuTexture8.loadFromFile("../Images/regression.jpg");
		menuTexture9.loadFromFile("../Images/gradient.jpg");
		menuTexture10.loadFromFile("../Images/gradient.jpg");
        startTexture.loadFromFile("../Images/start.jpg");
		exitTexture.loadFromFile("../Images/mainmenu.jpg");
		sf::Sprite menu1(menuTexture1);
		sf::Sprite menu2(menuTexture2);
		sf::Sprite menu3(menuTexture3);
		sf::Sprite menu4(menuTexture4);
		sf::Sprite menu5(menuTexture5);
		sf::Sprite menu6(menuTexture6);
		sf::Sprite menu7(menuTexture7);
		sf::Sprite menu8(menuTexture8);
		sf::Sprite menu9(menuTexture9);
		sf::Sprite menu10(menuTexture10);
        sf::Sprite start(startTexture);
        sf::Sprite exit(exitTexture);
        bool isMenu = true;
		int menuNum;
        int WhiteStrategy = 0, BlackStrategy = 0;
        start.setPosition(150, 425);
        exit.setPosition(150, 425);
		menu1.setPosition(0, 50);
		menu2.setPosition(300, 50);
		menu3.setPosition(0, 125);
		menu4.setPosition(300, 125);
		menu5.setPosition(0, 200);
		menu6.setPosition(300, 200);
		menu7.setPosition(0, 275);
		menu8.setPosition(300, 275);
		menu9.setPosition(0, 350);
		menu10.setPosition(300, 350);
        std::map<int, std::string> strategies = { {5, "Player"}, { 1, "Random" }, { 2, "Greedy" }, { 3, "Regression" }, { 4, "Gradient" } };
		while (isMenu) {
            if (WhiteStrategy != 5) {
                menu1.setColor(sf::Color(129, 181, 221));
            } else {
                menu1.setColor(sf::Color(199, 251, 251));
            }
            if (BlackStrategy != 5) {
                menu2.setColor(sf::Color(129, 181, 221));
            } else {
                menu2.setColor(sf::Color(199, 251, 251));
            }
            if (WhiteStrategy != 1) {
                menu3.setColor(sf::Color(129, 181, 221));
            } else {
                menu3.setColor(sf::Color(199, 251, 251));
            }
            if (BlackStrategy != 1) {
                menu4.setColor(sf::Color(129, 181, 221));
            } else {
                menu4.setColor(sf::Color(199, 251, 251));
            }
            if (WhiteStrategy != 2) {
                menu5.setColor(sf::Color(129, 181, 221));
            } else {
                menu5.setColor(sf::Color(199, 251, 251));
            }
            if (BlackStrategy != 2) {
                menu6.setColor(sf::Color(129, 181, 221));
            } else {
                menu6.setColor(sf::Color(199, 251, 251));
            }
            if (WhiteStrategy != 3) {
                menu7.setColor(sf::Color(129, 181, 221));
            } else {
                menu7.setColor(sf::Color(199, 251, 251));
            }
            if (BlackStrategy != 3) {
                menu8.setColor(sf::Color(129, 181, 221));
            } else {
                menu8.setColor(sf::Color(199, 251, 251));
            }
            if (WhiteStrategy != 4) {
                menu9.setColor(sf::Color(129, 181, 221));
            } else {
                menu9.setColor(sf::Color(199, 251, 251));
            }
            if (BlackStrategy != 4) {
                menu10.setColor(sf::Color(129, 181, 221));
            } else {
                menu10.setColor(sf::Color(199, 251, 251));
            }
			menuNum = 0;
			window.clear(sf::Color(129, 181, 221));
            if (WhiteStrategy != 0 && BlackStrategy != 0) {
                start.setColor(sf::Color::White);
            } else {
                exit.setColor(sf::Color::White);
            }
            if (sf::IntRect(0, 50, 300, 30).contains(sf::Mouse::getPosition(window))) { if (WhiteStrategy == 0) menu1.setColor(sf::Color::White);menuNum = 1; }
			if (sf::IntRect(300, 50, 300, 30).contains(sf::Mouse::getPosition(window))) { if (BlackStrategy == 0) menu2.setColor(sf::Color::White); menuNum = 2; }
            if (sf::IntRect(0, 125, 300, 30).contains(sf::Mouse::getPosition(window))) { if (WhiteStrategy == 0) menu3.setColor(sf::Color::White);menuNum = 3; }
			if (sf::IntRect(300, 125, 300, 30).contains(sf::Mouse::getPosition(window))) { if (BlackStrategy == 0) menu4.setColor(sf::Color::White); menuNum = 4; }
            if (sf::IntRect(0, 200, 300, 30).contains(sf::Mouse::getPosition(window))) { if (WhiteStrategy == 0) menu5.setColor(sf::Color::White);menuNum = 5; }
			if (sf::IntRect(300, 200, 300, 30).contains(sf::Mouse::getPosition(window))) { if (BlackStrategy == 0) menu6.setColor(sf::Color::White); menuNum = 6; }
            if (sf::IntRect(0, 275, 300, 30).contains(sf::Mouse::getPosition(window))) { if (WhiteStrategy == 0) menu7.setColor(sf::Color::White);menuNum = 7; }
			if (sf::IntRect(300, 275, 300, 30).contains(sf::Mouse::getPosition(window))) { if (BlackStrategy == 0) menu8.setColor(sf::Color::White); menuNum = 8; }
            if (sf::IntRect(0, 350, 300, 30).contains(sf::Mouse::getPosition(window))) { if (WhiteStrategy == 0) menu9.setColor(sf::Color::White);menuNum = 9; }
			if (sf::IntRect(300, 350, 300, 30).contains(sf::Mouse::getPosition(window))) { if (BlackStrategy == 0) menu10.setColor(sf::Color::White); menuNum = 10; }
			if (sf::IntRect(150, 425, 300, 30).contains(sf::Mouse::getPosition(window))) { start.setColor(sf::Color(199, 251, 251)); menuNum = 11; }
			if (sf::IntRect(150, 425, 300, 30).contains(sf::Mouse::getPosition(window)) && WhiteStrategy * BlackStrategy == 0) { exit.setColor(sf::Color(199, 251, 251)); menuNum = 12; }
            if (WhiteStrategy != 0 && BlackStrategy != 0) {
                window.draw(start);
            } else {
                window.draw(exit);
            }
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {};
                if (menuNum == 11) {
                    GraphicStartGame(window, strategies[WhiteStrategy], strategies[BlackStrategy]);
                    WhiteStrategy = 0, BlackStrategy = 0;
                }
                if (menuNum == 12) {
                    isMenu = false;
                }
                if (menuNum == 1) {
                    if (WhiteStrategy == 0) {
                        WhiteStrategy = 5;
                    } else {
                        WhiteStrategy = 0;
                    }
				}
				if (menuNum == 2) {
                    if (BlackStrategy == 0) {
                        BlackStrategy = 5;
                    } else {
                        BlackStrategy = 0;
                    }
                }
				if (menuNum == 3) {
                    if (WhiteStrategy == 0) {
                        WhiteStrategy = 1;
                    } else {
                        WhiteStrategy = 0;
                    }
				}
				if (menuNum == 4) {
                    if (BlackStrategy == 0) {
                        BlackStrategy = 1;
                    } else {
                        BlackStrategy = 0;
                    }
                }
 				if (menuNum == 5) {
                    if (WhiteStrategy == 0) {
                        WhiteStrategy = 2;
                    } else {
                        WhiteStrategy = 0;
                    }
				}
				if (menuNum == 6) {
                    if (BlackStrategy == 0) {
                        BlackStrategy = 2;
                    } else {
                        BlackStrategy = 0;
                    }
                }
				if (menuNum == 7) {
                    if (WhiteStrategy == 0) {
                        WhiteStrategy = 3;
                    } else {
                        WhiteStrategy = 0;
                    }
				}
				if (menuNum == 8) {
                    if (BlackStrategy == 0) {
                        BlackStrategy = 3;
                    } else {
                        BlackStrategy = 0;
                    }
                }
				if (menuNum == 9) {
                    if (WhiteStrategy == 0) {
                        WhiteStrategy = 4;
                    } else {
                        WhiteStrategy = 0;
                    }
				}
				if (menuNum == 10) {
                    if (BlackStrategy == 0) {
                        BlackStrategy = 4;
                    } else {
                        BlackStrategy = 0;
                    }
                }

			}
			window.draw(menu1);
			window.draw(menu2);
            window.draw(menu3);
			window.draw(menu4);
			window.draw(menu5);
			window.draw(menu6);
            window.draw(menu7);
			window.draw(menu8);
			window.draw(menu9);
			window.draw(menu10);
			window.display();
        }
    }

    std::pair<std::pair<int, int>, std::pair<int, int>> GetCoordinates(std::pair<int, int> elem, std::vector<std::vector<sf::Sprite>> table) {
        std::pair<int, int> start, finish;
        if (elem.first < 12) {
            start.first = 21 + (12 - elem.first) * 43;
            start.second = 21 + (table[elem.first].size() - 1) * Y;
            if (elem.first > 5) start.first -= 43;
        } else {
            start.first = 21 + (elem.first % 12) * 43;
            start.second = 418 - (table[elem.first].size() - 1) * Y;
            if (elem.first > 17) start.first += 43;
        }
        if (elem.second < 12 && elem.second != -1) {
            finish.first = 21 + (12 - elem.second) * 43;
            finish.second = 21 + (table[elem.second].size()) * Y;
            if (elem.second > 5) finish.first -= 43;
        } else if (elem.second >= 12) {
            finish.first = 21 + (elem.second % 12) * 43;
            finish.second = 418 - (table[elem.second].size()) * Y;
            if (elem.second > 17) finish.first += 43;
        } else if (elem.second == -1) {
            finish.first = 650;
            finish.second = 531;
            if (!IsWhite) {
                finish.first = -50;
                finish.second = -50;
            }
        }
        return {start, finish};
    }

    int GetPosition(std::pair<double, double> coord) {
        int result = 24;
        if (coord.first >= 21 && coord.first < 64) result = 11;
        if (coord.first >= 64 && coord.first < 107) result = 10;
        if (coord.first >= 107 && coord.first < 150) result = 9;
        if (coord.first >= 150 && coord.first < 193) result = 8;
        if (coord.first >= 193 && coord.first < 236) result = 7;
        if (coord.first >= 236 && coord.first <= 279) result = 6;
        if (coord.first >= 322 && coord.first < 365) result = 5;
        if (coord.first >= 365 && coord.first < 408) result = 4;
        if (coord.first >= 408 && coord.first < 451) result = 3;
        if (coord.first >= 451 && coord.first < 494) result = 2;
        if (coord.first >= 494 && coord.first < 537) result = 1;
        if (coord.first >= 537 && coord.first <= 580) result = 0;
        if (coord.second > 241 && result != 24) result = 23 - result;
        return result;
    }

    void DrawDice(sf::RenderWindow& window, std::pair<int, int> dice, std::vector<int> coord, std::vector<int> rotate) {
        sf::Texture tdice1, tdice2, tdice3, tdice4, tdice5, tdice6;
		tdice1.loadFromFile("../Images/dice1.jpg");
		tdice2.loadFromFile("../Images/dice2.jpg");
		tdice3.loadFromFile("../Images/dice3.jpg");
		tdice4.loadFromFile("../Images/dice4.jpg");
		tdice5.loadFromFile("../Images/dice5.jpg");
		tdice6.loadFromFile("../Images/dice6.jpg");
    	sf::Sprite dice1(tdice1);
		sf::Sprite dice2(tdice2);
        sf::Sprite dice3(tdice3);
		sf::Sprite dice4(tdice4);
        sf::Sprite dice5(tdice5);
		sf::Sprite dice6(tdice6);
        std::vector<sf::Sprite> PossibleDice = {dice1, dice2, dice3, dice4, dice5, dice6};
        sf::Sprite firstDice = PossibleDice[dice.first - 1], secondDice = PossibleDice[dice.second - 1];
        firstDice.setPosition(coord[0], coord[1]);
        secondDice.setPosition(coord[0] + coord[2], coord[1] + coord[3]);
        firstDice.setRotation(rotate[0]);
        secondDice.setRotation(rotate[1]);
        window.draw(firstDice);
        window.draw(secondDice);



    }

    void Player(sf::RenderWindow& window, std::vector<int>& TPosition, std::vector<std::vector<sf::Sprite>>& table) {
        sf::Image deskImage;
		deskImage.loadFromFile("../Images/table.jpg");
		sf::Texture deskTexture;
		deskTexture.loadFromImage(deskImage);
		sf::Sprite deskSprite;
		deskSprite.setTexture(deskTexture);
		deskSprite.setPosition(0, 0);
        std::pair<int, int> dice = RandomDice();
        srand((unsigned int)time(NULL) + rand());
		std::vector<int> coord { rand() % 190 + 50 + 300 * (rand() % 2), rand() % 50 + 210, rand() % 10 + 20, rand() % 20 - 40 };
        std::vector<int> rotate {rand() % 90, rand() % 90};
        window.clear();
        window.draw(deskSprite);
        for (int p = 0; p != 24; ++p) {
            for (int s = 0; s != table[p].size(); ++s) {
                window.draw(table[p][s]);
            }
        }
        DrawDice(window, dice, coord, rotate);
        window.display();
        TListOfMoves possible = PossibleMoves(TPosition, dice);
        TSetOfMoves correct;
        bool helpcorrect, globalcorrect;
        for (auto elem : possible) correct.insert(elem);
        if (possible.size() == 0) return;
        int start = 24, finish = 24;
        std::pair<int, int> move;
        for (int i = 0; i != possible[0].size(); ++i) {
            bool moved = false;
            while (!moved) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    double xMouse = sf::Mouse::getPosition(window).x;
                    double yMouse = sf::Mouse::getPosition(window).y;
                    int p;
                    for (int j = 0; j != 24; ++j) {
                        if (IsWhite) {
                            p = j;
                        } else {
                            if (j >= 0 && j <= 11) p = j + 12; else p = j - 12;
                        }
                        if ((TPosition[p] > 0)
                            && xMouse <= (table[j][table[j].size() - 1].getPosition().x + 20) + 20
                            && xMouse >= (table[j][table[j].size() - 1].getPosition().x + 20) - 20
                            && yMouse <= (table[j][table[j].size() - 1].getPosition().y + 20) + 20
                            && yMouse >= (table[j][table[j].size() - 1].getPosition().y + 20) - 20) {
                            move = PlayerDrag(window, TPosition, table, table[j][table[j].size() - 1]);
                            start = move.first;
                            finish = move.second;
                            moved = true;
                            break;
                        }
                    }
                } else if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    while (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {};
                    double xMouse = sf::Mouse::getPosition(window).x;
                    double yMouse = sf::Mouse::getPosition(window).y;
                    int p;
                    for (int j = 0; j != 24; ++j) {
                        if (IsWhite) {
                            p = j;
                        } else {
                            if (j >= 0 && j <= 11) p = j + 12; else p = j - 12;
                        }
                        if ((TPosition[p] > 0)
                            && xMouse <= (table[j][table[j].size() - 1].getPosition().x + 20) + 20
                            && xMouse >= (table[j][table[j].size() - 1].getPosition().x + 20) - 20
                            && yMouse <= (table[j][table[j].size() - 1].getPosition().y + 20) + 20
                            && yMouse >= (table[j][table[j].size() - 1].getPosition().y + 20) - 20) {
                            move = PlayerDrag(window, TPosition, table, table[j][table[j].size() - 1]);
                            start = move.first;
                            finish = -1;
                            moved = true;
                            break;
                        }
                    }
                }
            }
            if (false) {  // Corrent?
                helpcorrect = false;
                globalcorrect = false;
                for (auto elem : correct) {
                    for (int k = 0; k != elem.size(); ++k) {
                        if (elem[k].first == start && elem[k].second == finish) {
                            elem[k] = {0, 0};
                            helpcorrect = true;
                            globalcorrect = true;
                            break;
                        }
                    }
                    if (!helpcorrect) {
                        for (int k = 0; k != elem.size(); ++k) {
                            elem[k] = {0, 0};
                        }
                    }
                    helpcorrect = false;
                }
                if (!globalcorrect) {
                    std::swap(start, finish);
                }
            }




            if (true) {             // Correct?

                if (!IsWhite) {
                    if (start >= 0 && start <= 11) start += 12; else start -= 12;
                    if (finish != -1) {
                        if (finish >= 0 && finish <= 11) finish += 12; else finish -= 12;
                    }
                }
                --TPosition[start];
                if (finish != -1) ++TPosition[finish];
                if (!IsWhite) {
                    if (start >= 0 && start <= 11) start += 12; else start -= 12;
                    if (finish != -1) {
                        if (finish >= 0 && finish <= 11) finish += 12; else finish -= 12;
                    }
                }
                sf::Sprite checker = table[start][table[start].size() - 1];

                std::pair<int, int> begin = GetCoordinates({ start, finish }, table).first, end = GetCoordinates({ start, finish }, table).second;
                checker.setPosition(end.first, end.second);

                window.clear();
                window.draw(deskSprite);

                std::pair<int, int> vstart, vfinish;
                vstart = {sf::Mouse::getPosition(window).x - 20, sf::Mouse::getPosition(window).y - 20};
                vfinish = GetCoordinates({ start, finish }, table).second;
                int x = vfinish.first - vstart.first, y = vfinish.second - vstart.second;
                for (int time = 0; time != Speed; ++time) {
                    table[start][table[start].size() - 1].move(1.0 * x / Speed, 1.0 * y / Speed);
                    window.clear();
                    window.draw(deskSprite);
                    for (int p = 0; p != 24; ++p) {
                        for (int s = 0; s != table[p].size(); ++s) {
                                window.draw(table[p][s]);
                        }
                    }
                    window.draw(table[start][table[start].size() - 1]);
                    DrawDice(window, dice, coord, rotate);
                    window.display();
                    Sleep(10);
                }

                if (start == finish) {
                    int e = (start == finish) * (Y - 2*Y*(start >= 12));
                    checker.setPosition(begin.first, begin.second - e);
                    --i;
                }


                table[start].pop_back();
                if (finish != -1) table[finish].push_back(checker);

                window.clear();
                window.draw(deskSprite);

                for (int p = 0; p != 24; ++p) {
                    for (int s = 0; s != table[p].size(); ++s) {
                        window.draw(table[p][s]);
                    }
                }

                window.draw(checker);
                DrawDice(window, dice, coord, rotate);
                window.display();
            }
            globalcorrect = false;
        }
    }

    std::pair<int, int> PlayerDrag(sf::RenderWindow& window, std::vector<int>& TPosition, std::vector<std::vector<sf::Sprite>>& table, sf::Sprite& checker) {
        sf::Image deskImage;
		deskImage.loadFromFile("../Images/table.jpg");
		sf::Texture deskTexture;
		deskTexture.loadFromImage(deskImage);
		sf::Sprite deskSprite;
		deskSprite.setTexture(deskTexture);
		deskSprite.setPosition(0, 0);
        double xStart = checker.getPosition().x;
        double yStart = checker.getPosition().y;
        while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            checker.setPosition(sf::Mouse::getPosition(window).x - 20, sf::Mouse::getPosition(window).y - 20);
            window.clear();
            window.draw(deskSprite);
            for (int p = 0; p != 24; ++p) {
                for (int s = 0; s != table[p].size(); ++s) {
                    window.draw(table[p][s]);
                }
            }
            window.draw(checker);

            window.display();
        }
        double xMouse = sf::Mouse::getPosition(window).x;
        double yMouse = sf::Mouse::getPosition(window).y;
        double xEnd = xStart, yEnd = yStart;
        for (int i = 0; i != 24; ++i) {
            if (xMouse <= GetCoordinates({0, i}, table).second.first + 40
            && xMouse >= GetCoordinates({0, i}, table).second.first
            && yMouse <= GetCoordinates({0, i}, table).second.second + 40
            && yMouse >= GetCoordinates({0, i}, table).second.second) {
                xEnd = GetCoordinates({0, i}, table).second.first;
                yEnd = GetCoordinates({0, i}, table).second.second;
                checker.setPosition(xEnd, yEnd);
                break;
            }
        }

        window.clear();
        window.draw(deskSprite);
        for (int p = 0; p != 24; ++p) {
            for (int s = 0; s != table[p].size(); ++s) {
                window.draw(table[p][s]);
            }
        }
        window.draw(checker);
        window.display();
        return { GetPosition({ xStart, yStart }), GetPosition({ xEnd, yEnd }) };
    }

    void GraphicStartGame(sf::RenderWindow& window, std::string WhiteStrategy, std::string BlackStrategy) {
        sf::Texture menuTextureW, menuTextureB;
        menuTextureW.loadFromFile("../Images/whitewins.jpg");
		menuTextureB.loadFromFile("../Images/blackwins.jpg");
        sf::Sprite whitewins(menuTextureW);
		sf::Sprite blackwins(menuTextureB);
        whitewins.setPosition(150, 210);
        blackwins.setPosition(150, 210);
        bool isMenu = true;
        IsWhite = true;
        TMove move;
        std::vector<std::vector<sf::Sprite>> table(24);
        std::vector<int> TPosition = StartPosition();
        sf::Image deskImage;
		deskImage.loadFromFile("../Images/table.jpg");
		sf::Texture deskTexture;
		deskTexture.loadFromImage(deskImage);
		sf::Sprite deskSprite;
		deskSprite.setTexture(deskTexture);
		deskSprite.setPosition(0, 0);
		sf::Image whiteImage;
		whiteImage.loadFromFile("../Images/white.png");
		sf::Texture whiteTexture;
		whiteTexture.loadFromImage(whiteImage);
		sf::Image blackImage;
		blackImage.loadFromFile("../Images/black.png");
		sf::Texture blackTexture;
		blackTexture.loadFromImage(blackImage);
        window.clear();
		window.draw(deskSprite);
        for (int i = 0; i != 15; ++i) {
            sf::Sprite whiteSprite;
		    whiteSprite.setTexture(whiteTexture);
            sf::Sprite blackSprite;
		    blackSprite.setTexture(blackTexture);
            table[0].push_back(whiteSprite);
			table[0][i].setPosition(21 + 12 * 43, 21 + i * Y);
            table[12].push_back(blackSprite);
			table[12][i].setPosition(21 + 0 * 43, 418 - i * Y);
        }
        window.display();
        while (isMenu) {
            while(CheckEnd(TPosition)) {
                window.clear();
                window.draw(deskSprite);
                for (int p = 0; p != 24; ++p) {
                    for (int s = 0; s != table[p].size(); ++s) {
                        window.draw(table[p][s]);
                    }
                }
                window.display();
                if (WhiteStrategy == "Player") {
                    Speed = StandartSpeed;
                    Player(window, TPosition, table);
                }
                else {
                    if (BlackStrategy == "Player") {
                        Speed = EnemySpeed;
                    } else {
                        Speed = StandartSpeed;
                    }
                    move = ChooseStrategy(TPosition, WhiteStrategy);
                    for (auto elem : move) {
                        std::pair<int, int> start, finish;
                        start = GetCoordinates({ elem.first, elem.second }, table).first;
                        finish = GetCoordinates({ elem.first, elem.second }, table).second;
                        int x = finish.first - start.first, y = finish.second - start.second;
                        for (int time = 0; time != Speed; ++time) {
                            table[elem.first][table[elem.first].size() - 1].move(1.0 * x / Speed, 1.0 * y / Speed);
                            window.clear();
                            window.draw(deskSprite);
                            for (int p = 0; p != 24; ++p) {
                                for (int s = 0; s != table[p].size(); ++s) {
                                        window.draw(table[p][s]);
                                }
                            }
                            window.draw(table[elem.first][table[elem.first].size() - 1]);
                            window.display();
                            Sleep(10);
                        }
                        table[elem.first].pop_back();
                        if (elem.second != -1) {
                            sf::Sprite whiteSprite;
		                    whiteSprite.setTexture(whiteTexture);
                            table[elem.second].push_back(whiteSprite);
                            table[elem.second][table[elem.second].size() - 1].setPosition(finish.first, finish.second);
                        }
                    }
                }
	    		if (CheckEnd(TPosition)) ChangePlayers(TPosition);

                if (BlackStrategy == "Player") {
                    Speed = StandartSpeed;
                    Player(window, TPosition, table);
                }
                else {
                    if (WhiteStrategy == "Player") {
                        Speed = EnemySpeed;
                    } else {
                        Speed = StandartSpeed;
                    }
                    move = ChooseStrategy(TPosition, BlackStrategy);
                    for (auto elem : move) {
                        std::pair<int, int> start, finish;
                        start = GetCoordinates({ elem.first, elem.second }, table).first;
                        finish = GetCoordinates({ elem.first, elem.second }, table).second;
                        int x = finish.first - start.first, y = finish.second - start.second;
                        for (int time = 0; time != Speed; ++time) {
                            table[elem.first][table[elem.first].size() - 1].move(1.0 * x / Speed, 1.0 * y / Speed);
                            window.clear();
                            window.draw(deskSprite);
                            for (int p = 0; p != 24; ++p) {
                                for (int s = 0; s != table[p].size(); ++s) {
                                        window.draw(table[p][s]);
                                }
                            }
                            window.draw(table[elem.first][table[elem.first].size() - 1]);
                            window.display();
                            Sleep(10);
                        }
                        table[elem.first].pop_back();
                        if (elem.second != -1) {
                            sf::Sprite blackSprite;
		                    blackSprite.setTexture(blackTexture);
                            table[elem.second].push_back(blackSprite);
                            table[elem.second][table[elem.second].size() - 1].setPosition(finish.first, finish.second);
                        }
                    }
                }
                if (CheckEnd(TPosition)) ChangePlayers(TPosition);
            }
			window.clear(sf::Color(129, 181, 221));
            whitewins.setColor(sf::Color(129, 181, 221));
            blackwins.setColor(sf::Color(129, 181, 221));
            if (IsWhite) window.draw(whitewins); else window.draw(blackwins);
            window.display();
            while (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {};
            while (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {};
            isMenu = false;
        }
    }
};

#endif
