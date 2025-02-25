#include <SFML/Graphics.hpp>
#include "include/goblin.hpp"
#include <vector>
#include <random>
#include <ctime>
#include <optional> // SFML 3.0 requires this for event handling

int main() {
    // Seed random number generator
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Create SFML Window
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1000, 800)), "SFML 3.0 - Goblin Game");
    window.setFramerateLimit(60);

    // Player setup
    sf::CircleShape player(50.f);
    player.setFillColor(sf::Color::White);
    player.setPosition({375.f, 275.f});

    // Goblin storage
    std::vector<Goblin> goblins;
    float respawnTimer = 0.0f;
    float playerSpeed = 200.f;

    sf::Clock clock; // Game clock

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        // Handle events (Proper SFML 3.0)
        while (std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }

        // Respawn goblins when needed
        respawnTimer -= deltaTime;
        if (goblins.size() < 5 && respawnTimer <= 0.0f) {
            goblins.emplace_back(std::rand() % 800, std::rand() % 600);
            respawnTimer = 2.0f;
        }

        // Update goblins
        for (Goblin& goblin : goblins) {
            goblin.update(deltaTime);
        }

        // Player movement
        sf::Vector2f movement{0.f, 0.f};
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= playerSpeed * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += playerSpeed * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= playerSpeed * deltaTime;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += playerSpeed * deltaTime;
        player.move(movement);

        // Rendering
        window.clear(sf::Color::Black);
        window.draw(player);
        for (const auto& goblin : goblins) {
            goblin.draw(window);
        }
        window.display();
    }

    return 0;
}




//cd C:/SFML_Project
//g++ -std=c++17 -o sfml_game.exe SFML.cpp -IC:/SFML/include -LC:/SFML/lib -lsfml-graphics -lsfml-window -lsfml-system
//./sfml_game.exe