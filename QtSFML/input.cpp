#include "input.h"

using namespace std;
using namespace sf;

Input::Input()
{
    button.left = button.right = button.up = button.down = button.jump =
    button.attack = button.enter = false;
}

Input::Button Input::getButton(void) const { return button; }

void Input::setButton(int bouton, bool etat)
{
    switch (bouton)
    {
        case up:
        button.up = etat;
        break;

        case down:
        button.down = etat;
        break;

        case right:
        button.right = etat;
        break;

        case left:
        button.left = etat;
        break;

        case attack:
        button.attack = etat;
        break;

        case jump:
        button.jump = etat;
        break;

        case enter:
        button.enter = etat;
        break;
    }
}

void Input::gestionInputs(RenderWindow &window)
{
    getInput(window);
}


void Input::getInput(RenderWindow &window)
{

    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case Event::Closed:
            window.close();
            break;

            case Event::KeyPressed:
                switch (event.key.code) // La touche qui a été pressée
                {
                    case Keyboard::Escape: // Echap
                    window.close();
                    break;

                    case Keyboard::C:
                    button.jump = true;
                    break;

                    case Keyboard::V:
                    button.attack = true;
                    break;

                    case Keyboard::Left:
                    button.left = true;
                    break;

                    case Keyboard::Right:
                    button.right = true;
                    break;

                    case Keyboard::Down:
                    button.down = true;
                    break;

                    case Keyboard::Up:
                    button.up = true;
                    break;


                    case Keyboard::Return:
                    button.enter = true;
                    break;

                    default:
                    break;
                }
                break;

                case Event::KeyReleased:
                    switch (event.key.code)
                    {
                        case Keyboard::C:
                        button.jump = false;
                        break;

                        case Keyboard::Left:
                        button.left = false;
                        break;

                        case Keyboard::Right:
                        button.right = false;
                        break;

                        case Keyboard::Down:
                        button.down = false;
                        break;

                        case Keyboard::Up:
                        button.up = false;
                        break;


                        case Keyboard::Return:
                        button.enter = false;
                        break;

                        default:
                        break;
                    }
                    break;

                    default:
                    break;
                }
            }
}
