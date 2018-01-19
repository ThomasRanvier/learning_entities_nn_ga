#ifndef LEARNING_ENTITIES_NN_GA_MAP_H
#define LEARNING_ENTITIES_NN_GA_MAP_H

#include "Entity.h"

class Map {
private:
    std::vector<Entity *> population;
    std::vector<Food *> targets;
    int iterations, generations;
public:
    Map();

    void nextStep();
    void draw(sf::RenderWindow *);
    void nextPopulation();
    Entity * selectTournament();
    void sortPopulation(int, int);
};


#endif
