
#include "../headers/Entity.h"

Entity::Entity(Point pos, int angle, NeuralNetwork *dna) : pos(pos), angle(angle), dna(dna), score(0) {}

void Entity::reborn(Entity * parent1, Entity * parent2) {
    crossover(parent1->dna, parent2->dna);
}

void Entity::draw(sf::RenderWindow * window) {
    sf::CircleShape body(ENTITY_RADIUS);
    body.setOutlineThickness(ENTITY_RADIUS / 4);
    body.setFillColor(sf::Color::Transparent);
    body.setOutlineColor(ENTITY_COLOR);
    body.setPosition(this->pos.x - ENTITY_RADIUS, this->pos.y - ENTITY_RADIUS);
    (*window).draw(body);

    sf::RectangleShape fov(sf::Vector2f(FOV_DIST,1));
    fov.rotate(angle + FOV_ANGLE);
    fov.setFillColor(this->actualFOV >= 0 ? ACTIVE_FOV_COLOR : INACTIVE_FOV_COLOR);
    fov.setPosition(this->pos.x, this->pos.y);
    (*window).draw(fov);
    fov.rotate(- 2 * FOV_ANGLE);
    (*window).draw(fov);

    sf::RectangleShape direction(sf::Vector2f(ENTITY_RADIUS,1));
    direction.rotate(angle);
    direction.setFillColor(ENTITY_COLOR);
    direction.setPosition(this->pos.x, this->pos.y);
    (*window).draw(direction);

    sf::Font font;
    font.loadFromFile("../fonts/arial.ttf");
    sf::Text text(std::to_string(score), font, ENTITY_RADIUS);
    text.setPosition(this->pos.x - (ENTITY_RADIUS / 2), this->pos.y - (ENTITY_RADIUS / 2));
    text.setColor(ENTITY_COLOR);
    (*window).draw(text);
}

void Entity::move(std::vector<Food *> * targets) {
    std::vector<double> entrie, outputs;
    entrie.push_back(this->actualFOV);

    outputs = this->dna->forward(entrie);

    if (abs(outputs[1]) > 0.25) {
        addToAngle(outputs[1] * ENTITY_ROTATION);
    }

    if (outputs[0] >= 0) {
        goForward(outputs[0]);
    }

    getFieldOfView(targets);
}

void Entity::addToAngle(double value) {
    this->angle += value;
    this->angle %= 360;
    if (this->angle < 0) {
        this->angle += 360;
    }
}

void Entity::goForward(double value) {
    this->pos.x += value * ENTITY_STEP * cos((this->angle * PI) / 180);
    this->pos.y += value * ENTITY_STEP * sin((this->angle * PI) / 180);
    if (this->pos.x < 0) {
        this->pos.x = 0;
    } else if (this->pos.x > WIDTH) {
        this->pos.x = WIDTH;
    }
    if (this->pos.y < 0) {
        this->pos.y = 0;
    } else if (this->pos.y > HEIGHT) {
        this->pos.y = HEIGHT;
    }
}

void Entity::checkFood(std::vector<Food *> * food) {
    for (int i(NB_TARGETS - 1); i >= 0; i--) {
        Food * target = (*food)[i];
        if (dist2(target) <= pow(TARGET_RADIUS + ENTITY_RADIUS, 2)) {
            this->score++;
            target->setPos(Point(rand() % WIDTH, rand() % HEIGHT));
        }
    }
}

double Entity::dist2(Food * target) {
    return pow(target->getPos().x - this->pos.x,2) + pow(target->getPos().y - this->pos.y,2);
}

double Entity::getFieldOfView(std::vector<Food *> * targets) {
    double result(-1), mem(pow(FOV_DIST, 2));

    for (int i(0); i < NB_TARGETS; i++) {
        Food * target = (*targets)[i];
        double dist(dist2(target));
        if (dist <= mem) {
            std::vector<Point> polygon = {this->pos};

            for (int i(0); i <= 8; i++) {
                sf::RectangleShape fov(sf::Vector2f(FOV_DIST,1));
                fov.setPosition(this->pos.x, this->pos.y);
                fov.rotate(angle - FOV_ANGLE + (((i * 1.0) / 4.0) * FOV_ANGLE * 1.0));
                polygon.push_back(Point(fov.getTransform().transformPoint(fov.getPoint(1)).x,
                                        fov.getTransform().transformPoint(fov.getPoint(1)).y));
            }

            if (pointInPoly(target->getPos(), polygon)) {
                mem = dist;
                result = 1 - (dist / (FOV_DIST * FOV_DIST * 1.0));
            }
        }
    }

    this->actualFOV = result;
}

bool Entity::pointInPoly(const Point point, std::vector<Point> poly) {
    int i, j, nvert = poly.size();
    bool c = false;

    for(i = 0, j = nvert - 1; i < nvert; j = i++) {
        if(((poly[i].y >= point.y) != (poly[j].y >= point.y)) &&
                (point.x <= (poly[j].x - poly[i].x) * (point.y - poly[i].y) / (poly[j].y - poly[i].y) + poly[i].x))
            c = !c;
    }
    return c;
}

int Entity::getScore() const {
    return score;
}

void Entity::crossover(NeuralNetwork * dna1, NeuralNetwork * dna2) {
    std::vector<int> layers(dna1->getLayers());

    std::vector<std::vector<std::vector<double>>> weights1(dna1->getWeights()), weights2(dna2->getWeights()), weights;

    for (unsigned int i(0); i < weights1.size(); i++) {
        std::vector<std::vector<double>> layerWeights;
        for (unsigned int j(0); j < weights1[i].size(); j++) {
            std::vector<double> neuronWeights;
            neuronWeights = rand() % 2 ? weights1[i][j] : weights2[i][j];
            if (rand() % RAND_MAX <= MUTATION_RATE) {
                for (unsigned int k(0); k < neuronWeights.size(); k++) {
                    double value((((rand() % RAND_MAX) * 2) - 1) / MUTATION_VARIATION);
                    neuronWeights[k] += value;
                    if (neuronWeights[k] > LIMIT_WEIGHT) neuronWeights[k] = LIMIT_WEIGHT;
                    if (neuronWeights[k] < -LIMIT_WEIGHT) neuronWeights[k] = -LIMIT_WEIGHT;
                }
            }
            layerWeights.push_back(neuronWeights);
        }
        weights.push_back(layerWeights);
    }
    this->dna->setWeights(weights);
}

void Entity::setPos(const Point &pos) {
    Entity::pos = pos;
}

void Entity::setScore(int score) {
    Entity::score = score;
}

void Entity::resetFOV() {
    this->actualFOV = -1;
}
