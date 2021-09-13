#include <iostream>

#include "game.hpp"


int main()
{
    Game game;
    while (game.isRun()) {
        game.oneStepSimulation();
        game.render();
        game.inputProcessing();
        SDL_Delay(10);
    }

    game.writeStatisticsToFile("statistics.txt");
}
