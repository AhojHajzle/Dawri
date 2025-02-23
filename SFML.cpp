#include <SFML/Graphics.hpp>
#include <iostream>
#include <optional>
#include <random>
#include <vector>
#include <algorithm> // For std::remove_if

// Define Goblin structure
struct Goblin {
    sf::CircleShape shape;
    sf::Vector2f direction;
    float speed;
    float changeTimer;
};

// Random number generator
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> distDir(-1.f, 1.f);
std::uniform_real_distribution<float> distTime(1.f, 3.f); // Change direction every 1-3 sec
std::uniform_int_distribution<int> distX(50, 750);
std::uniform_int_distribution<int> distY(50, 550);

int main() {
    sf::RenderWindow window(sf::VideoMode({1000, 800}), "SFML 3.0 - Goblin Game");
    sf::Clock clock; // Track time for smooth movement

    // Player setup (White Circle)
    sf::CircleShape player(50.f);
    player.setFillColor(sf::Color::White);
    player.setPosition(sf::Vector2f(375.f, 275.f));

    // Goblin storage
    std::vector<Goblin> goblins;

    // Spawn 5 goblins with random movement
    for (int i = 0; i < 5; ++i) {
        Goblin goblin;
        goblin.shape = sf::CircleShape(40.f);
        goblin.shape.setFillColor(sf::Color::Green);
        goblin.shape.setPosition(sf::Vector2f(distX(gen), distY(gen)));
        goblin.direction = sf::Vector2f(distDir(gen), distDir(gen));
        goblin.speed = 450.f;
        goblin.changeTimer = distTime(gen);
        goblins.push_back(goblin);
    }

    float playerSpeed = 200.f;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds(); // Time since last frame

        while (std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Goblin movement & collision with borders
        for (Goblin& goblin : goblins) {
            goblin.shape.move(goblin.direction * goblin.speed * deltaTime);

            // Get goblin position
            sf::Vector2f pos = goblin.shape.getPosition();
            float radius = goblin.shape.getRadius();

            // Define borders
            float leftLimit = 0.f;
            float rightLimit = 1000.f - 2 * radius; // Window width - diameter
            float topLimit = 0.f;
            float bottomLimit = 800.f - 2 * radius; // Window height - diameter

            // Reverse direction on collision
            if (pos.x < leftLimit || pos.x > rightLimit) {
                goblin.direction.x *= -1;
            }
            if (pos.y < topLimit || pos.y > bottomLimit) {
                goblin.direction.y *= -1;
            }

            // Change direction after a timer
            goblin.changeTimer -= deltaTime;
            if (goblin.changeTimer <= 0.f) {
                goblin.direction = sf::Vector2f(distDir(gen), distDir(gen));
                goblin.changeTimer = distTime(gen);
            }
        }

        // Player movement
        sf::Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= playerSpeed * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += playerSpeed * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= playerSpeed * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += playerSpeed * deltaTime;
        player.move(movement);

        // Rendering
        window.clear(sf::Color::Black);
        window.draw(player);
        for (const auto& goblin : goblins) {
            window.draw(goblin.shape);
        }
        window.display();
    }

    return 0;
}




//cd C:/SFML_Project
//g++ -std=c++17 -o sfml_game.exe SFML.cpp -IC:/SFML/include -LC:/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
//./sfml_game.exe