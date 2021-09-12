#include <cstdlib>

#include "people.hpp"
#include "settings.hpp"

Vector2D::Vector2D() {
    x = 0;
    y = 0;
}

Vector2D::Vector2D(const int x, const int y) {
    this->x = x;
    this->y = y;
}

int Vector2D::getX() const  {return x;}
int Vector2D::getY() const  {return y;}

void Vector2D::setX(const int x)  {this->x = x;}
void Vector2D::setY(const int y)  {this->y = y;}

People::People() {
    int x = rand() % SCREEN_WIDTH;
    int y = rand() % SCREEN_HEIGHT;

    int dx = rand() % 3 - 1;        // dx: [-1; 1]
    int dy = rand() % 3 - 1;        // dy: [-1; 1]

    coords = Vector2D(x, y);
    direction = Vector2D(dx, dy);
    type = SUSCEPTIBLE;
}

People::People(const PeopleType people_type): People() {
    type = people_type;
}


Vector2D People::getCoords() const              { return coords; }
int People::getX() const                        { return coords.getX();}
int People::getY() const                        { return coords.getY();}
PeopleType People::getPeopleType() const        { return type;}
void People::changePeopleType(PeopleType type)  {this->type = type;}


bool People::checkRecovering() const {
    if (type != INFECTIOUS)     return false;

    if (infected_steps / STEPS_IN_DAY > PERIOD_OF_ILLNES)     return true;
    else                                                      return false;
}


void People::move() {
    int x = coords.getX();
    int y = coords.getY();
    int dx = direction.getX();
    int dy = direction.getY();

    // 'PROBABILITY_OF_CHANGE_DIRECTION' a chance to change the direction
    if (rand() % 100 <= PROBABILITY_OF_CHANGE_DIRECTION) {
        direction.setX(rand() % 3 - 1);
        direction.setY(rand() % 3 - 1);
    }

    // Check collisions
    if (x + dx <= 0 || x + dx >= SCREEN_WIDTH) {
        direction.setX(direction.getX() * -1);
    }


    if (y + dy <= 0 || y + dy >= SCREEN_HEIGHT) {
        direction.setY(direction.getY() * -1);
    }

    // Move
    coords.setX(coords.getX() + direction.getX());
    coords.setY(coords.getY() + direction.getY());

    if (type == INFECTIOUS) {
        infected_steps++;
    }
}
