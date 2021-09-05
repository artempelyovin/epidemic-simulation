#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <SDL2/SDL.h>

const float PI = 3.1415926535;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int NUMBER_OF_PEOPLE = 100;
const int PEOPLE_SIZE = 5;
const int INFECTION_RADIUS = PEOPLE_SIZE * 5 / 2;

const SDL_Color INFECTION_RADIUS_COLOR = {51, 22, 3, 255};

const int STEPS_IN_DAY = 100;

const int PROBABILITY_OF_INFECTION = 1;        // (in %)

#endif
