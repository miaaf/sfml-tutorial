/*
    author: miaf
    license: MIT License
*/


#include "Game.h"

//Private functions
void Game::initVariables()
{
    this->window = nullptr;

    //Game logic
    this->endGame = false;
    this->points = 0;
    this->health = 10;
    this->enemySpawnTimerMax = 10.f;
    this->enemySpawnTimer = this->enemySpawnTimerMax;
    this->maxEnemies = 10;
    this->foodSpawnTimerMax = 1000.f;
    this->foodSpawnTimer = this->foodSpawnTimerMax;
    this->maxFoods = 2;
    this->mouseHeld = false;
}

void Game::initWindow()
{
    this->videoMode.width = 800;
    this->videoMode.height = 600;

    this->window = new sf::RenderWindow(this->videoMode, "SFML Tutorial", sf::Style::Titlebar | sf::Style::Close);

    this->window->setFramerateLimit(60);
}


void Game::initFonts()
{
    if(!this->font.loadFromFile("Fonts/Dosis-Light.ttf"))
    {
        std::cout << "ERROR::GAME::INITFONTS::Failed to load font!" << std::endl;
    }
}

void Game::initText()
{
    this->uiText.setFont(this->font);
    this->uiText.setCharacterSize(24);
    this->uiText.setFillColor(sf::Color::White);
    this->uiText.setString("NONE");
}

void Game::initFood()
{
    this->food.setPosition(10.f, 10.f);
    this->food.setSize(sf::Vector2f(70.f, 70.f));
    this->food.setFillColor(sf::Color::Green);
}

void Game::initEnemies()
{
    this->enemy.setPosition(10.f, 10.f);
    this->enemy.setSize(sf::Vector2f(100.f, 100.f));
    this->enemy.setFillColor(sf::Color::Cyan);
    //this->enemy.setOutlineColor(sf::Color::Red);
    //this->enemy.setOutlineThickness(1.f);
}

Game::Game()
{   
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
    this->initFood();
    this->initEnemies();
}


Game::~Game()
{
    delete this->window;
}

const bool Game::isRunning() const
{
    return this->window->isOpen();
}

const bool Game::getEndGame() const
{
    return this->endGame;
}


void Game::spawnEnemy()
{
    /*
        Spawn enemies.
    */
    this->enemy.setPosition(
       static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)),
        0.f
    );
    int type = rand() % 5;

    switch(type)
    {
        //Hardest enemy
        case 0:
            this->enemy.setSize(sf::Vector2f(10.f, 10.f));
            this->enemy.setFillColor(sf::Color::Magenta);
            break;
        case 1:
            this->enemy.setSize(sf::Vector2f(30.f, 30.f));
            this->enemy.setFillColor(sf::Color::Yellow);
            break;
        case 2:
            this->enemy.setSize(sf::Vector2f(50.f, 50.f));
            this->enemy.setFillColor(sf::Color::Red);
            break;
        case 3:
            this->enemy.setSize(sf::Vector2f(80.f, 80.f));
            this->enemy.setFillColor(sf::Color::Blue);
            break;
        //Easiest enemy
        case 4:
            this->enemy.setSize(sf::Vector2f(100.f, 100.f));
            this->enemy.setFillColor(sf::Color::White);
            break;
        default:
            break;
    }

    //Spawn enemy
    this->enemies.push_back(this->enemy);
}

void Game::spawnFood()
{
    this->food.setPosition(
       static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->food.getSize().x)),
        0.f
    );

    this->foods.push_back(this->food);
}

void Game::pollEvents()
{
    while(this->window->pollEvent(this->ev))
    {
        switch(this->ev.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if(this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
        }
    }
}

void Game::updateMousePositions()
{

   this->mousePosWindow = sf::Mouse::getPosition(*this->window);
   this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}

void Game::updateText()
{
    std::stringstream ss;

    ss << "Points: " << this->points << "\n"
    << "Health: " << this->health;

    this->uiText.setString(ss.str());
}

void Game::updateEnemies()
{
    if (this->enemies.size() < this->maxEnemies)
    {
        if(this->enemySpawnTimer >= this->enemySpawnTimerMax)
        {
            //Spawn the enemy and reset the timer
            this->spawnEnemy();
            this->enemySpawnTimer = 0.f;
        }
        else
        {
            this->enemySpawnTimer += 1.f;
        }
    }

    //Move the enemies
    for (int i = 0; i < this->enemies.size(); i++)
    {
        this->enemies[i].move(0.f, 1.5f);

        if(this->enemies[i].getPosition().y > this->window->getSize().y)
        {
            this->enemies.erase(this->enemies.begin() + i);
            this->health -= 1;
        }

    }
    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if(this->mouseHeld == false)
        {
            this->mouseHeld = true;
            bool deleted = false;
            for (size_t i = 0; i < this->enemies.size() && deleted == false; i++)
            {
                if(this->enemies[i].getGlobalBounds().contains(this->mousePosView))
                {
                    if(this->enemies[i].getFillColor() == sf::Color::Magenta)
                    {
                        //Get points
                        this->points += 10.f;
                    }
                    else if(this->enemies[i].getFillColor() == sf::Color::Yellow)
                    {
                        //Get points
                        this->points += 7.f;
                    }
                    else if(this->enemies[i].getFillColor() == sf::Color::Red)
                    {
                        //Get points
                        this->points += 5.f;
                    }
                    else if(this->enemies[i].getFillColor() == sf::Color::Blue)
                    {
                        //Get points
                        this->points += 3.f;
                    }
                    else if(this->enemies[i].getFillColor() == sf::Color::White)
                    {
                        //Get points
                        this->points += 1.f;
                    }
                    deleted = true;
                    this->enemies.erase(this->enemies.begin() + i);
                }
            }
        }
        else
        {
            this->mouseHeld = false;
        }
    }
    
}

void Game::updateFood()
{
    if(this->foods.size() < this->maxFoods)
    {
        if(this->foodSpawnTimer >= this->foodSpawnTimerMax)
        {
            //Spawn the food and reset the timer
            this->spawnFood();
            this->foodSpawnTimer = 0.f;
        }
        else
        {
            this->foodSpawnTimer += 1.f;
        }
    }

    for (int i = 0; i < this->foods.size(); i++)
    {
        this->foods[i].move(0.f, 1.5f);

        if(this->foods[i].getPosition().y > this->window->getSize().y)
        {
            this->foods.erase(this->foods.begin() + i);
        }

    }

    if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {

        bool deleted = false;
        for (size_t i = 0; i < this->foods.size() && deleted == false; i++)
        {
            if(this->foods[i].getGlobalBounds().contains(this->mousePosView))
            {
                if(this->foods[i].getFillColor() == sf::Color::Green)
                {
                    //Get health
                    this->health += 1.f;
                }
                deleted = true;
                this->foods.erase(this->foods.begin() + i);
            }
        }
    }
}


void Game::update()
{
    this->pollEvents();

    if(this->endGame == false)
    {
        this->updateMousePositions();

        this->updateText();

        this->updateFood();

        this->updateEnemies();
    }

    if(this-> health <= 0)
    {
        this->endGame = true;
    }

}

void Game::renderText(sf::RenderTarget& target)
{
    target.draw(this->uiText);
}

void Game::renderFood(sf::RenderTarget& target)
{
    //Rendering all foods
    for (auto &e : this->foods)
    {
        target.draw(e);
    }
}

void Game::renderEnemies(sf::RenderTarget& target)
{
    //Rendering all enemies.
    for (auto &e : this->enemies)
    {
        target.draw(e);

    }
}

void Game::render()
{
    this->window->clear();

    this->renderEnemies(*this->window);

    this->renderFood(*this->window);

    this->renderText(*this->window);

    this->window->display();
}