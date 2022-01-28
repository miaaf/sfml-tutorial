#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


/*
    author: miaf
    license: MIT License
*/


//Game engine

class Game
{
    private:
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event ev;

        sf::Vector2i mousePosWindow;
        sf::Vector2f mousePosView;

        sf::Font font;

        sf::Text uiText;

        bool endGame;
        unsigned points;
        int health;
        float enemySpawnTimer;
        float enemySpawnTimerMax;
        int maxEnemies;
        float foodSpawnTimer;
        float foodSpawnTimerMax;
        int maxFoods;
        bool mouseHeld;

        std::vector<sf::RectangleShape> enemies;
        std::vector<sf::RectangleShape> foods;
        
        sf::RectangleShape enemy;
        sf::RectangleShape food;

        void initVariables();
        void initWindow();
        void initFonts();
        void initText();
        void initFood();
        void initEnemies();

    public:
        Game();
        virtual ~Game();

        const bool isRunning() const;
        const bool getEndGame() const;

        void spawnEnemy();
        void spawnFood();

        void pollEvents();
        void updateMousePositions();
        void updateText();
        void updateEnemies();
        void updateFood();
        void update();

        void renderText(sf::RenderTarget& target);
        void renderEnemies(sf::RenderTarget& target);
        void renderFood(sf::RenderTarget& target);
        void render();
};