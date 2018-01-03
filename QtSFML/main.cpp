#include "main.h"

int main()
{
    RenderWindow window(VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32), "SFML");

    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    Input input;
    Map map;
    Player player;

    map.setLevel(1);
    map.changeLevel();

    player.initialize(map, true);
    player.setVies(3);
    player.setEtoiles(0);

    while (window.isOpen())
    {
        input.gestionInputs(window);

        player.update(input, map);

        window.clear();
        map.drawBackground(window);
        map.draw(2, window);
        map.draw(1, window);
        player.draw(map, window);
        map.draw(3, window);
        window.display();
    }

    return 0;
}
