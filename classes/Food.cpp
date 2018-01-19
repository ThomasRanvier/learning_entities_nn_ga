
#include "../headers/Food.h"

Food::Food(Point pos) : pos(pos) {}

void Food::draw(sf::RenderWindow * window) {
    sf::CircleShape target(TARGET_RADIUS);
    target.setFillColor(TARGET_COLOR);
    target.setPosition(this->pos.x - TARGET_RADIUS, this->pos.y - TARGET_RADIUS);
    (*window).draw(target);
}

const Point Food::getPos() const {
    return pos;
}

void Food::setPos(const Point pos) {
    Food::pos = pos;
}
