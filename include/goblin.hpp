#ifndef GOBLIN_HPP
#define GOBLIN_HPP

#include <SFML/Graphics.hpp>

class Goblin {
public:
    Goblin(float x, float y);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;

    sf::Vector2f getPosition() const;
    float getRadius() const;
    void reverseX();
    void reverseY();

private:
    sf::CircleShape shape;
    sf::Vector2f direction;
    float speed;
    float changeTimer;

    void randomizeDirection();
};

#endif // GOBLIN_HPP