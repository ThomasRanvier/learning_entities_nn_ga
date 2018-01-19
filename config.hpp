#include <iostream>
#include <vector>
#include <random>
#include <SFML/Graphics.hpp>

const double PI = 3.14159265359;

const int WIDTH = 1300;
const int HEIGHT = 700;

const int FOV_DIST = 250;
const int FOV_ANGLE = 10;
const sf::Color ACTIVE_FOV_COLOR = sf::Color::Green;
const sf::Color INACTIVE_FOV_COLOR = sf::Color::Red;

const int NB_ENTITIES = 24;
const int NB_SURVIVAL = 12;
const int NB_TARGETS = 80;

const double ENTITY_RADIUS = 15;

const sf::Color ENTITY_COLOR = sf::Color::Blue;
const double TARGET_RADIUS = 4;

const sf::Color TARGET_COLOR = sf::Color(255,0,255);
const int ENTITY_STEP = 7;

const int ENTITY_ROTATION = 8;

const int REST_TIME = 0;
const int MAX_ITERATIONS = 500;

const double MUTATION_RATE = 0.15;
const double MUTATION_VARIATION = 0.1;
const double LIMIT_WEIGHT = 1.4;
