#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "My first game");
    sf::Event eveniment;
    sf::Texture textura;
    textura.loadFromFile("Meniu1.png");
    sf::Sprite meniu(textura);

    while (window.isOpen() )
    {
        while(window.pollEvent(eveniment) )
        {
            if(eveniment.type==sf::Event::EventType::Closed)
                window.close();
            else if(eveniment.type == sf::Event::MouseButtonPressed)
            {

                if(eveniment.mouseButton.button==sf::Mouse::Left)
                {
                    if( (30<=eveniment.mouseButton.x && eveniment.mouseButton.x<=140) && (430<=eveniment.mouseButton.y && eveniment.mouseButton.y<=500) )
                    {
                        //play
                        cout<<"N-ai ce juca!\n";
                    }
                    else if( (30<=eveniment.mouseButton.x && eveniment.mouseButton.x<=160) && (555<=eveniment.mouseButton.y && eveniment.mouseButton.y<=625) )
                    {
                        //help
                        cout<<"Esti neajutorat\n";
                    }
                    else if( (30<=eveniment.mouseButton.x && eveniment.mouseButton.x<=135) && (685<=eveniment.mouseButton.y && eveniment.mouseButton.y<=740) )
                    {
                        //exit
                        window.close();
                    }
                }
            }
        }
        window.clear();
        window.draw(meniu);
        window.display();
    }
    return 0;
}
