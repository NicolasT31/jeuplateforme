#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>

class Input
{
struct Button { bool left, right, up, down, jump, attack, enter; };

public:
    Input();

    Button getButton(void) const;

    void setButton(int bouton, bool etat);

    void gestionInputs(sf::RenderWindow &window);
    void getInput(sf::RenderWindow &window);

private:
    sf::Event event;
    Button button;

    enum{ up, down, right, left, attack, jump, enter };
};

#endif // INPUT_H
