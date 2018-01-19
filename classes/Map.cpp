#include "../headers/Map.h"

Map::Map() : iterations(0), generations(1) {
    std::vector<int> layers = {1, 4, 2};
    for (uint_fast16_t i(0); i < NB_ENTITIES; i++) {
        this->population.push_back(new Entity(Point(rand() % WIDTH, rand() % HEIGHT), rand() % 360,
                                              new NeuralNetwork(layers)));
    }
    for (uint_fast8_t i(0); i < NB_TARGETS; i++) {
        this->targets.push_back(new Food(Point(rand() % WIDTH, rand() % HEIGHT)));
    }
}

void Map::draw(sf::RenderWindow * window) {
    sf::RectangleShape background(sf::Vector2f(WIDTH, HEIGHT));
    background.setFillColor(sf::Color::White);
    (*window).draw(background);

    for (int i(0); i < NB_TARGETS; i++) {
        this->targets[i]->draw(window);
    }

    int maxScore(this->population[0]->getScore()), total(0);
    for (int i(0); i < NB_ENTITIES; i++) {
        total += this->population[i]->getScore();
        this->population[i]->draw(window);
        if (this->population[i]->getScore() > maxScore) maxScore = this->population[i]->getScore();
    }

    sf::Font font;
    font.loadFromFile("../fonts/arial.ttf");

    sf::Text text("Gen : " + std::to_string(generations), font, ENTITY_RADIUS);
    text.setColor(sf::Color::Black);
    (*window).draw(text);

    text.setPosition(0, ENTITY_RADIUS);
    text.setString("Ite : " + std::to_string(iterations));
    (*window).draw(text);

    text.setPosition(0, ENTITY_RADIUS * 2);
    text.setString("Max : " + std::to_string(maxScore));
    (*window).draw(text);

    text.setPosition(0, ENTITY_RADIUS * 3);
    text.setString("Tot : " + std::to_string(total));
    (*window).draw(text);
}

void Map::nextStep() {
    if (this->iterations++ <= MAX_ITERATIONS) {
        for (uint_fast16_t i(0); i < NB_ENTITIES; i++) {
            this->population[i]->move(&(this->targets));
            this->population[i]->checkFood(&(this->targets));
        }
    } else {
        nextPopulation();
    }
}

void Map::nextPopulation() {
    this->iterations = 0;
    this->generations++;
    for (int i(NB_TARGETS - 1); i >= 0; i--) {
        this->targets[i]->setPos(Point(rand() % WIDTH, rand() % HEIGHT));
    }

    sortPopulation(0, NB_ENTITIES - 1);

    for (int i(0); i < NB_SURVIVAL; i++) {
        this->population[i]->reborn(selectTournament(), selectTournament());
    }

    for (int i(0); i < NB_ENTITIES; i++) {
        this->population[i]->setScore(0);
        this->population[i]->resetFOV();
        this->population[i]->setPos(Point(rand() % WIDTH, rand() % HEIGHT));
    }
}

Entity * Map::selectTournament() {
    int i1((rand() % (NB_ENTITIES / 2)) + (NB_ENTITIES / 2)), i2((rand() % (NB_ENTITIES / 2)) + (NB_ENTITIES / 2));
    Entity * best = this->population[i1];
    if (best->getScore() < this->population[i2]->getScore()) best = this->population[i2];
    return best;
}

void Map::sortPopulation(int left, int right) {
    int i = left, j = right;
    Entity * tmp;
    int pivot = this->population[(left + right) / 2]->getScore();

    while (i <= j) {
        while (this->population[i]->getScore() < pivot)
            i++;
        while (this->population[j]->getScore() > pivot)
            j--;
        if (i <= j) {
            tmp = this->population[i];
            this->population[i] = this->population[j];
            this->population[j] = tmp;
            i++;
            j--;
        }
    };
    if (left < j)
        sortPopulation(left, j);
    if (i < right)
        sortPopulation(i, right);
}

