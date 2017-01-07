#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

struct walls
{
    int lin, col, poz;
};

struct casuta
{
    int lin, col;
};

struct players
{
    casuta pozitie;
    int nrPereti=5;
};


int nrPereti;
walls perete, pereti[100];
players player[10];
sf::RenderWindow window(sf::VideoMode(800, 800), "Quoridor");
int Map[20][20];



void meniu();
void play();

int main()
{

    meniu();
    return 0;
}


void meniu ()
{
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
                        play();
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
}

void play ()
{
    int i, turn=1, actualX, actualY;
    char numeImagine[]={"pawn0.png"}, rand[]={"cerc0.png"}, numePerete[]={"perete0.png"};
    casuta next, d[5];
    d[0].lin=-1; d[1].lin=0; d[2].lin=1; d[3].lin=0;
    d[0].col=0; d[1].col=1; d[2].col=0; d[3].col=-1;
    sf::Event eveniment;
    sf::Texture textura, texturaPawn, texturaTurn, texturaWall;
    textura.loadFromFile("tabla1.png");
    sf::Sprite board(textura);

    player[1].pozitie.lin=9; player[1].pozitie.col=5; Map[2*player[1].pozitie.lin-1][2*player[1].pozitie.col-1]=1;
    player[2].pozitie.lin=1; player[2].pozitie.col=5; Map[2*player[2].pozitie.lin-1][2*player[2].pozitie.col-1]=1;
    player[3].pozitie.lin=5; player[3].pozitie.col=1; Map[2*player[3].pozitie.lin-1][2*player[3].pozitie.col-1]=1;
    player[4].pozitie.lin=5; player[4].pozitie.col=9; Map[2*player[4].pozitie.lin-1][2*player[4].pozitie.col-1]=1;

    while (window.isOpen() )
    {
        while(window.pollEvent(eveniment) )
        {
            if(eveniment.type==sf::Event::EventType::Closed)
                window.close();

            else if(eveniment.type == sf::Event::MouseButtonPressed)
            {


                    cout<<"Am apasat\n";
                    if(eveniment.mouseButton.button==sf::Mouse::Left)
                    {
                        actualX=eveniment.mouseButton.x;
                        actualY=eveniment.mouseButton.y;

                        for(i=0; i<4; ++i)
                        {
                            next.lin=player[turn].pozitie.lin+d[i].lin;
                            next.col=player[turn].pozitie.col+d[i].col;
                            if(
                               !Map[2*next.lin-1][2*next.col-1] && !Map[2*player[turn].pozitie.lin-1+d[i].lin][2*player[turn].pozitie.col-1+d[i].col] &&
                                (0<next.lin && next.lin<=9) && (0<next.col && next.col<=9) &&
                                ( next.lin-1)*79 +51 <=actualY && actualY<=(next.lin-1)*79 +102
                               && ( (next.col-1)*79 +51<=actualX && actualX<=(next.col-1)*79 +102  ) )
                            {

                                Map[2*player[turn].pozitie.lin-1][2*player[turn].pozitie.col-1]=0;
                                player[turn].pozitie=next;
                                Map[2*player[turn].pozitie.lin-1][2*player[turn].pozitie.col-1]=1;
                                cout<<"Am modificat\n";
                                ++turn;
                                if(turn==5) turn=1;

                            }
                            else if(
                                Map[2*next.lin-1][2*next.col-1] && !Map[2*player[turn].pozitie.lin-1+d[i].lin][2*player[turn].pozitie.col-1+d[i].col] &&
                               (0<next.lin && next.lin<=9) && (0<next.col && next.col<=9) &&
                                ( next.lin-1)*79 +51 <=actualY && actualY<=(next.lin-1)*79 +102
                               && ( (next.col-1)*79 +51<=actualX && actualX<=(next.col-1)*79 +102  ) )
                               {
                                    next.lin=next.lin+d[i].lin;
                                    next.col=next.col+d[i].col;
                                    Map[2*player[turn].pozitie.lin-1][2*player[turn].pozitie.col-1]=0;
                                    player[turn].pozitie=next;
                                    Map[2*player[turn].pozitie.lin-1][2*player[turn].pozitie.col-1]=1;
                                    cout<<"Am modificat\n";
                                    ++turn;
                                    if(turn==5) turn=1;
                               }
                        }

                        if (    51<actualY &&actualY<748 &&
                                51<actualX &&actualX<748  &&
                                (actualY-116)%79<14 )
                        {

                            ++nrPereti;
                            pereti[nrPereti].col=51+(actualX-116)-(actualX-116)%79;
                            pereti[nrPereti].lin=118+(actualY-116)-(actualY-116)%79;
                            pereti[nrPereti].poz=1;
                            ++turn;
                            if(turn==5) turn=1;
                        }
                        else if(    51<actualY &&actualY<748 &&
                                    51<actualX &&actualX<748  &&
                                (actualX-116)%79<14 )
                        {
                            ++nrPereti;
                            pereti[nrPereti].col=118+(actualX-116)-(actualX-116)%79;
                            pereti[nrPereti].lin=51+(actualY-116)-(actualY-116)%79;
                            pereti[nrPereti].poz=2;
                            ++turn;
                            if(turn==5) turn=1;
                        }

                    }


            }
            else if (eveniment.type == sf::Event::KeyPressed)
            {
                if (eveniment.key.code == sf::Keyboard::Escape)
                {
                    //pause();
                    cout<<"n-ai scapare\n";
                }
            }
        }

        if (    51<eveniment.mouseMove.y &&eveniment.mouseMove.y<748 &&
                51<eveniment.mouseMove.x &&eveniment.mouseMove.x<748  &&
                (eveniment.mouseMove.y-116)%79<14 )
        {

            perete.col=51+(eveniment.mouseMove.x-116)-(eveniment.mouseMove.x-116)%79;
            perete.lin=118+(eveniment.mouseMove.y-116)-(eveniment.mouseMove.y-116)%79;
            perete.poz=1;
        }
        else if(    51<eveniment.mouseMove.y &&eveniment.mouseMove.y<748 &&
                    51<eveniment.mouseMove.x &&eveniment.mouseMove.x<748  &&
                (eveniment.mouseMove.x-116)%79<14 )
        {
            perete.col=118+(eveniment.mouseMove.x-116)-(eveniment.mouseMove.x-116)%79;
            perete.lin=51+(eveniment.mouseMove.y-116)-(eveniment.mouseMove.y-116)%79;
            perete.poz=2;
        }
        else perete.poz=0;


        //desenez
        window.clear();
        window.draw(board);

        //desenez perete virtual
        if(perete.poz)
        {
            numePerete[6]=perete.poz+'0';
            texturaWall.loadFromFile(numePerete);
            sf::Sprite wall(texturaWall);
            wall.setPosition(perete.col, perete.lin);
            window.draw(wall);
        }

        //desenez pioni

        for(i=1; i<=4; ++i)
        {
            numeImagine[4]=i+'0';
            texturaPawn.loadFromFile(numeImagine);
            sf::Sprite pawn(texturaPawn);
            pawn.setPosition( (player[i].pozitie.col-1)*79 +51, (player[i].pozitie.lin-1)*79 +51  );
            window.draw(pawn);

            rand[4]=turn+'0';
            texturaTurn.loadFromFile(rand);
            sf::Sprite Turn(texturaTurn);
            Turn.setPosition( 20, 20  );
            window.draw(Turn);
        }

        //desenez peretii

        for(i=1; i<=nrPereti; ++i)
        {
            numePerete[6]=pereti[i].poz+'0';
            texturaWall.loadFromFile(numePerete);
            sf::Sprite wall(texturaWall);
            wall.setPosition(pereti[i].col, pereti[i].lin);
            window.draw(wall);
        }

        window.display();


    }
}
