#ifndef LEARNING_ENTITIES_NN_GA_TARGET_H
#define LEARNING_ENTITIES_NN_GA_TARGET_H

#include "Point.h"

class Food {
private:
    Point pos;
public:
    Food(Point);

    void draw(sf::RenderWindow *);

    const Point getPos() const;
    void setPos(const Point pos);
};


#endif
