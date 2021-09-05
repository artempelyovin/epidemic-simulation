#include <iostream>
#include <time.h>

#include <SDL2/SDL_image.h>

#include "game.hpp"
#include "settings.hpp"


void draw_circle(SDL_Renderer *renderer, const int x0, const int y0, const int radius, int segments, const SDL_Color color) {
    if (segments < 3)   segments = 3;

    float alpha = 2. * PI / (float) segments;
    SDL_FPoint points[segments+1];

    double cos_a = cos(alpha);
    double sin_a = sin(alpha);

    points[0].x = radius;
    points[0].y = 0;

    points[segments].x = radius + x0;
    points[segments].y = y0;

    for (int i = 1; i < segments; i++) {
        points[i].x = points[i-1].x * cos_a - points[i-1].y * sin_a;
        points[i].y = points[i-1].x * sin_a + points[i-1].y * cos_a;
    }

    for (int i = 0; i < segments; i++) {
        points[i].x += x0;
        points[i].y += y0;
    }

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLinesF(renderer, points, segments+1);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}


bool check_collision(const People *people1, const People *people2) {
    int centre_x1 = people1->getX() + PEOPLE_SIZE / 2;
    int centre_y1 = people1->getY() + PEOPLE_SIZE / 2;

    int centre_x2 = people2->getX() + PEOPLE_SIZE / 2;
    int centre_y2 = people2->getY() + PEOPLE_SIZE / 2;

    int dx = centre_x1 - centre_x2;
    int dy = centre_y1 - centre_y2;

    int radius = dx*dx + dy*dy;

    if (radius < INFECTION_RADIUS * INFECTION_RADIUS) {
        if (rand() % 101 <= PROBABILITY_OF_INFECTION) {
            return true;
        }
    }
    return false;
}


void Game::draw_people(const People *people) {
    SDL_Rect people_rect;
    if (people->getPeopleType() == INFECTIOUS) {
        people_rect = {people->getX(), people->getY(), PEOPLE_SIZE, PEOPLE_SIZE};
        draw_circle(renderer,
                    people->getX() + PEOPLE_SIZE / 2,
                    people->getY() + PEOPLE_SIZE / 2,
                    INFECTION_RADIUS,
                    10,
                    INFECTION_RADIUS_COLOR);
    }
    else {
        people_rect = {people->getX(), people->getY(), PEOPLE_SIZE, PEOPLE_SIZE};
    }

    SDL_RenderCopy(renderer, textures[people->getPeopleType()], nullptr, &people_rect);
}

Game::Game()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cout << SDL_GetError() << std::endl;
        exit(1);
    }


    window = SDL_CreateWindow("Epidemic Simulation",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH,
                              SCREEN_HEIGHT,
                              SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        exit(2);
    }

    renderer = SDL_CreateRenderer(window,
                                  -1,
                                  SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr) {
        std::cout << SDL_GetError() << std::endl;
        exit(3);
    }

    // Load textures
    textures[0] = IMG_LoadTexture(renderer, "/home/artem/C++/epidemic-simulation/img/susceptible.png");
    textures[1] = IMG_LoadTexture(renderer, "/home/artem/C++/epidemic-simulation/img/infectious.png");
    textures[2] = IMG_LoadTexture(renderer, "/home/artem/C++/epidemic-simulation/img/recovered.png");


    // Create many susceptible people and one infected people
    for (int i = 0; i < NUMBER_OF_PEOPLE - 1; i++) {
        peoples_susceptible.push_back(new People());
    }

    peoples_susceptible.push_back(new People(INFECTIOUS));

}

Game::~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "The epidemic ended in " << game_steps / STEPS_IN_DAY << " days..." << std::endl;
}

bool Game::isRun() const        { return run;}

bool Game::isEndOfEpidemic() const {
    return peoples_infected.empty();
};

void Game::oneStepSimulation() {
    if (isEndOfEpidemic())  run = true;

    const size_t num_of_infected = peoples_infected.size();
    for (size_t i = 0; i <  num_of_infected; i++) {
        for (size_t j = 0; j < peoples_susceptible.size(); j++) {
            if (check_collision(peoples_infected[i], peoples_susceptible[j])) {
                peoples_infected.push_back(peoples_susceptible[j]);
                peoples_infected[i+1]->changePeopleType(INFECTIOUS);
                peoples_susceptible.erase(peoples_susceptible.begin() + j);
            }
        }
    }

    for (People* susceptible_people: peoples_susceptible) {
        susceptible_people->move();
    }

    for (People* recovered_people: peoples_recovered) {
        recovered_people->move();
    }

    for (People* infected_people: peoples_infected) {
        infected_people->move();
    }


//    for (int i = 0; i < NUMBER_OF_PEOPLE; i++) {
//        if (peoples[i].getPeopleType() == INFECTIOUS) {
//            int centre_x1 = peoples[i].getX() + PEOPLE_SIZE / 2;
//            int centre_y1 = peoples[i].getY() + PEOPLE_SIZE / 2;

//            for (int j = 0; j < NUMBER_OF_PEOPLE; j++) {
//                if (peoples[j].getPeopleType() != INFECTIOUS) {
//                    int centre_x2 = peoples[j].getX() + PEOPLE_SIZE / 2;
//                    int centre_y2 = peoples[j].getY() + PEOPLE_SIZE / 2;

//                    int dx = centre_x1 - centre_x2;
//                    int dy = centre_y1 - centre_y2;

//                    int radius = dx*dx + dy*dy;

//                    if (radius < INFECTION_RADIUS * INFECTION_RADIUS) {
//                        if (rand() % 101 <= PROBABILITY_OF_INFECTION) {
//                            peoples[j].changePeopleType(INFECTIOUS);
//                        }
//                    }
//                }
//            }
//        }
//        peoples[i].move();
//    }
    game_steps++;
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    for (People* susceptible_people: peoples_susceptible) {
        draw_people(susceptible_people);
    }

    for (People* recovered_people: peoples_recovered) {
        draw_people(recovered_people);
    }

    for (People* infected_people: peoples_infected) {
        draw_people(infected_people);
    }

    SDL_RenderPresent(renderer);
}

void Game::inputProcessing() {
    while(SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            run = false;
        }
    }
}


