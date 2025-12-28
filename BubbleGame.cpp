#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>

class BubbleGame {
private:
    sf::RenderWindow window;
    sf::CircleShape player;
    sf::RectangleShape target;
    sf::Font font;
    sf::Text scoreText;

    float speed = 0.5f; // Further reduce speed for smoother movement
    int score = 0;

public:
    BubbleGame() 
        : window(sf::VideoMode(800, 600), "Simple SFML Game") 
    {
        std::srand(std::time(nullptr));

        // Player
        player.setRadius(25.f);
        player.setFillColor(sf::Color::Blue);
        player.setPosition(400, 300);

        // Target
        target.setSize(sf::Vector2f(30, 30));
        target.setFillColor(sf::Color::Red);
        randomizeTargetPosition();

        // Font
        font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf");

        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10);
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

private:
    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Movement
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            player.move(-speed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            player.move(speed, 0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            player.move(0, -speed);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            player.move(0, speed);
    }

    void update() {
        // Collision detection
        if (player.getGlobalBounds().intersects(target.getGlobalBounds())) {
            score++;
            randomizeTargetPosition();
        }

        scoreText.setString("Score: " + std::to_string(score));
    }

    void render() {
        window.clear(sf::Color::Black);
        window.draw(player);
        window.draw(target);
        window.draw(scoreText);
        window.display();
    }

    void randomizeTargetPosition() {
        target.setPosition(std::rand() % 770, std::rand() % 570);
    }
};

int main() {
    BubbleGame* game = new BubbleGame();
    game->run();
    delete game;
    return 0;
}
