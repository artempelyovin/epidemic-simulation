#ifndef GAME_HPP
#define GAME_HPP

#include <array>
#include <vector>
#include <string>

#include <SDL2/SDL.h>

#include "people.hpp"
#include "settings.hpp"


struct StatRecord {
    size_t susceptible;
    size_t infected;
    size_t recovered;
};


class Game {
private:
    bool run = true;

    SDL_Event e;
    SDL_Window* window;
    SDL_Renderer* renderer;

    std::array<SDL_Texture*, 3> textures;
    std::vector<People*> peoples_susceptible;
    std::vector<People*> peoples_infected;
    std::vector<People*> peoples_recovered;

    std::vector<StatRecord> statistics;
    int game_steps = 0;
public:
    Game();
    ~Game();
    bool isRun() const;
    void oneStepSimulation();
    void inputProcessing();
    void render();
    void writeStatisticsToFile(const std::string path);
private:
    bool _isEndOfEpidemic() const;
    void _draw_people(const People *people);
};

#endif // GAME_HPP
