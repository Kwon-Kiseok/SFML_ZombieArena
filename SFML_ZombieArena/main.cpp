#include <SFML/Graphics.hpp>
#include ".\source\Utils\Utils.h"
#include ".\source\Utils\InputManager.h"
#include ".\source\player\player.h"
#include ".\source\Enemy\Zombie.h"
#include ".\source\Object\Bullet.h"
#include ".\source\Object\Crosshair.h"
#include "source/Utils/TextureHolder.h"
#include <iostream>

int CreateBackground(VertexArray& va, IntRect arena)
{
    srand(time(NULL));

    const int TILE_SIZE = 50;
    const int TILE_TYPES = 3;
    const int VERTEX_IN_QUAD = 4;

    int cols = arena.width / TILE_SIZE;
    int rows = arena.height / TILE_SIZE;

    va.setPrimitiveType(Quads);
    va.resize(cols * rows * VERTEX_IN_QUAD);

    for (int r = 0; r < rows; ++r)
    {
        for (int c = 0; c < cols; ++c)
        {
            int index = r * cols + c;

            float x = c * TILE_SIZE;
            float y = r * TILE_SIZE;

            int vertexIndex = index * VERTEX_IN_QUAD;

            va[vertexIndex + 0].position = Vector2f(x, y);
            va[vertexIndex + 1].position = Vector2f(x + TILE_SIZE, y);
            va[vertexIndex + 2].position = Vector2f(x + TILE_SIZE, y + TILE_SIZE);
            va[vertexIndex + 3].position = Vector2f(x, y + TILE_SIZE);

            int texIndex = Utils::RandomRange(0, 2);
            float offset = texIndex * TILE_SIZE;

            // outline
            if (c == 0 || c == cols-1 || r == 0 || r == rows-1)
            {
                texIndex = 3;
                offset = texIndex * TILE_SIZE;
            }
            va[vertexIndex + 0].texCoords = Vector2f(0.f, offset);
            va[vertexIndex + 1].texCoords = Vector2f(TILE_SIZE, offset);
            va[vertexIndex + 2].texCoords = Vector2f(TILE_SIZE, offset + TILE_SIZE);
            va[vertexIndex + 3].texCoords = Vector2f(0.f, offset + TILE_SIZE);

        }
    }

    return cols * rows;
}

void CreateZombies(std::vector<Zombie*>& zombies, int count, IntRect arena)
{
    for (auto it : zombies)
    {
        delete it;
    }
    zombies.clear();

    int offset = 85;
    int minX = arena.left + offset;
    int maxX = arena.width - offset;
    int minY = arena.top + offset;
    int maxY = arena.height - offset;

    // 캐릭터 근처에서 안나오도록
    int diff = 100;
    int centerX = (arena.left + arena.width) / 2;
    int centerY = (arena.top + arena.height) / 2;

    for (int i = 0; i < count; ++i)
    {
        int x = Utils::RandomRange(minX, maxX + 1);
        int y = Utils::RandomRange(minY, maxY + 1);

        while ((x > centerX - diff && x < centerX + diff) && (y > centerY - diff && y < centerY + diff))
        {
            x = Utils::RandomRange(minX, maxX + 1);
            y = Utils::RandomRange(minY, maxY + 1);
        }

        ZombieTypes type = static_cast<ZombieTypes>(Utils::RandomRange(0, static_cast<int>(ZombieTypes::COUNT)-1));
        Zombie* zombie = new Zombie();
        zombie->Spawn(x, y, type);

        zombies.push_back(zombie);
    }
}

int main()
{
    TextureHolder textureHolder;

    Vector2i resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Zombie Arena!", Style::Default);
    window.setMouseCursorVisible(false);
    View mainView(FloatRect(0, 0, resolution.x, resolution.y));

    InputManager::Init();

    IntRect ARENA;
    ARENA.width = 500;
    ARENA.height = 500;

    Player player;
    player.Spawn(ARENA, resolution, 0.f);

    Crosshair crosshair;

    std::vector<Zombie*> zombies;
    CreateZombies(zombies, 50, ARENA);

    Clock clock;

    sf::Texture texBackground = TextureHolder::GetTexture("graphics/background_sheet.png");
    texBackground.loadFromFile("graphics/background_sheet.png");

    VertexArray tileMap;
    CreateBackground(tileMap, ARENA);

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

        InputManager::Update(dt.asSeconds());

        //std::cout << "horizon: " << InputManager::GetAxis(Axis::Horizontal) << " vertical: " << InputManager::GetAxis(Axis::Vertical) << std::endl;

        player.Update(dt.asSeconds());

        mainView.setCenter(player.GetPosition());
        crosshair.Update(window);
        for (auto zombie : zombies)
        {
            zombie->Update(dt.asSeconds(), player.GetPosition(), ARENA);
        }

        window.clear();
        window.setView(mainView);
        window.draw(tileMap, &texBackground);

        for (auto zombie : zombies)
        {
            window.draw(zombie->GetSprite());
        }

        window.draw(player.GetSprite());
        if(nullptr != player.GetBullet())
            window.draw(player.GetBullet()->GetSprite());
        window.draw(crosshair.GetSprite());
        window.display();
    }


    return 0;
}