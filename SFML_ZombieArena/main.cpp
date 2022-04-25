#include <SFML/Graphics.hpp>
#include ".\source\Utils\Utils.h"
#include ".\source\Utils\InputManager.h"
#include ".\source\player\player.h"
#include <iostream>

int main()
{
    Vector2i resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Zombie Arena!", Style::Default);
    
    InputManager::Init();

    IntRect ARENA;
    ARENA.width = resolution.x;
    ARENA.height = resolution.y;

    Player player;
    player.Spawn(ARENA, resolution, 0.f);

    Clock clock;
    while (window.isOpen())
    {
        Time dt = clock.restart();
        sf::Event event;

        InputManager::ClearPrevInput();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            InputManager::ProcessInput(event);
        }

        player.Update(dt.asSeconds());

        window.clear();
        window.draw(player.GetSprite());
        window.display();
    }


    return 0;
}