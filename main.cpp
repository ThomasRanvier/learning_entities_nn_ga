#include "headers/Map.h"

void sleep(clock_t ms) {
    clock_t end(clock() + 1000 * ms);
    while (clock() <= end);
}

int main() {
    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Entities controlled by a neural network learning from a GA",
                            sf::Style::Default, settings);

    srand(time(0));
    Map map;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        window.clear();

        map.nextStep();
        map.draw(&window);

        window.display();

        sleep(REST_TIME);
    }
    return 0;
}