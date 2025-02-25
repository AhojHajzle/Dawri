#include "include/goblin.hpp"
#include <cmath>
#include <random>

Goblin::Goblin(float x, float y) {
    shape.setRadius(20.f);
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(sf::Vector2f(x, y));

    speed = 100.0f;
    changeTimer = 2.0f;
    randomizeDirection();
}

void Goblin::update(float deltaTime) {
    changeTimer -= deltaTime;
    shape.move(direction * speed * deltaTime);

    if (changeTimer <= 0.0f) {
        randomizeDirection();
        changeTimer = 2.0f;
    }
}

void Goblin::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::Vector2f Goblin::getPosition() const {
    return shape.getPosition();
}

float Goblin::getRadius() const {
    return shape.getRadius();
}

void Goblin::reverseX() {
    direction.x *= -1;
}

void Goblin::reverseY() {
    direction.y *= -1;
}

void Goblin::randomizeDirection() {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> dist(0.0f, 360.0f);

    float angle = dist(rng);
    direction.x = cos(angle);
    direction.y = sin(angle);
}