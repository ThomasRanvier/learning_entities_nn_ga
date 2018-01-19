#ifndef LEARNING_ENTITIES_NN_GA_ENTITY_H
#define LEARNING_ENTITIES_NN_GA_ENTITY_H

#include "Food.h"

class Entity {
private:
    Point pos;
    int angle, score;
    NeuralNetwork *dna;
    double actualFOV;

    void addToAngle(double);
    void goForward(double);
    double getFieldOfView(std::vector<Food *> *);
    double dist2(Food *);
    bool pointInPoly(const Point, std::vector<Point>);
    void crossover(NeuralNetwork *, NeuralNetwork *);

public:
    Entity(Point pos, int angle, NeuralNetwork *dna);
    void reborn(Entity *, Entity *);
    void draw(sf::RenderWindow *);
    void checkFood(std::vector<Food *> *);
    void move(std::vector<Food *> *);
    int getScore() const;
    void setPos(const Point &pos);
    void setScore(int score);
    void resetFOV();
};


#endif
