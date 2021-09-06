#ifndef PEOPLE_HPP
#define PEOPLE_HPP

enum PeopleType {
    SUSCEPTIBLE = 0,
    INFECTIOUS = 1,
    RECOVERED = 2
};


class Vector2D {
private:
    int x, y;
public:
    Vector2D();
    Vector2D(const int x, const int y);
    int getX() const;
    int getY() const;
    void setX(const int x);
    void setY(const int y);
};


class People {
private:
    Vector2D coords;
    Vector2D direction;
    PeopleType type;
public:
    int infected_steps = 0;
public:
    People();
    People(const PeopleType people_type);
    Vector2D getCoords() const;
    int getX() const;
    int getY() const;
    PeopleType getPeopleType() const;
    void changePeopleType(PeopleType type);
    void move();
    bool checkRecovering() const;
};



#endif // PEOPLE_HPP
