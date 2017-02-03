#include "Graphics.h"


int main() {
    Algorithm ms;
    Graphics gf;

    //ms.PlayGame(ms.StartPosition(), "Gradient", "Gradient", std::set<std::vector<int>>(), false);

    sf::RenderWindow window(sf::VideoMode(600, 481), "Backgammon");
    gf.MainMenu(window);

    //ms.GenerateNeuralGradientCoefs(40, 100000);

    //std::cout << ms.CompareStrategies(ms.StartPosition(), "Neuron1G", "Greedy", 1000) << "%\n";

    //std::string file = "../Debug/output/dataset.txt";
    //ms.GenerateDataset(file, ms.StartPosition(), "Random", "Random", 10000, 100);

    std::cout << "\n" << std::clock() / 1000.0;
    Sleep(3000);
    return 0;
}
