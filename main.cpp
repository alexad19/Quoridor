#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

int NumberOfPlayers=2;

struct mut{
    int fel, lin, col;
};

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
    int nrWalls=20/NumberOfPlayers;
};


int nrPereti;
casuta  d[5];
walls perete, pereti[100];
players player[10];
sf::RenderWindow window(sf::VideoMode(800, 800), "Quoridor");
int Map[20][20], Vali[20][20];



void meniu();
void selectPlayerMode();
void initializare();
bool pause();
void play();
void singlePlay ();
void help();
int lee(int indPlayer);
int gata (int indPlayer);
bool winner (int indPlayer);

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
                    if( (29<=eveniment.mouseButton.x && eveniment.mouseButton.x<=140) && (334<=eveniment.mouseButton.y && eveniment.mouseButton.y<=402) )
                    {
                        //play

                        cout<<"N-ai ce juca!\n";
                        initializare();
                        selectPlayerMode();
                    }
                    else if( (29<=eveniment.mouseButton.x && eveniment.mouseButton.x<=160) && (448<=eveniment.mouseButton.y && eveniment.mouseButton.y<=514) )
                    {
                        //help
                        help();
                        cout<<"Esti neajutorat\n";
                    }
                    else if( (29<=eveniment.mouseButton.x && eveniment.mouseButton.x<=135) && (570<=eveniment.mouseButton.y && eveniment.mouseButton.y<=620) )
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

void selectPlayerMode()
{


    sf::Event eveniment;
    sf::Texture textura;
    textura.loadFromFile("nrPlayers.png");
    sf::Sprite ajutor(textura);

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
                    if( (260<=eveniment.mouseButton.x && eveniment.mouseButton.x<=520) && (360<=eveniment.mouseButton.y && eveniment.mouseButton.y<=420) )
                    {
                        //singlePlay
                        NumberOfPlayers=2;
                        singlePlay();
                        return;
                    }
                    else if( (290<=eveniment.mouseButton.x && eveniment.mouseButton.x<=500) && (350<=eveniment.mouseButton.y && eveniment.mouseButton.y<=582) )
                    {
                        //back to meniu
                        NumberOfPlayers=2;
                        play();
                        return;
                    }
                    else if( (290<=eveniment.mouseButton.x && eveniment.mouseButton.x<=500) && (595<=eveniment.mouseButton.y && eveniment.mouseButton.y<=635) )
                    {
                        //back to meniu
                        NumberOfPlayers=4;
                        play();
                        return;
                    }
                }
            }
        }

        window.clear();
        window.draw(ajutor);
        window.display();
    }
}


void help()
{
    int pag=1;
    char pagina[]={"Help0.png"};
    sf::Event eveniment;
    sf::Texture textura;


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
                    if( pag==1 && (635<=eveniment.mouseButton.x && eveniment.mouseButton.x<=745) && (685<=eveniment.mouseButton.y && eveniment.mouseButton.y<=770) )
                    {
                        //next
                        pag=2;
                    }
                    else if( pag==2 && (620<=eveniment.mouseButton.x && eveniment.mouseButton.x<=730) && (695<=eveniment.mouseButton.y && eveniment.mouseButton.y<=780) )
                    {
                        //back to meniu
                        return;
                    }
                }
            }
        }
        pagina[4]=pag+'0';
        textura.loadFromFile(pagina);
        sf::Sprite ajutor(textura);

        window.clear();
        window.draw(ajutor);
        window.display();
    }
}

bool pause()
{


    sf::Event eveniment;
    sf::Texture textura;
    textura.loadFromFile("PauseMenu.png");
    sf::Sprite ajutor(textura);

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
                    if( (285<=eveniment.mouseButton.x && eveniment.mouseButton.x<=505) && (420<=eveniment.mouseButton.y && eveniment.mouseButton.y<=485) )
                    {
                        //back to game
                        return 1;
                    }
                    else if( (230<=eveniment.mouseButton.x && eveniment.mouseButton.x<=565) && (520<=eveniment.mouseButton.y && eveniment.mouseButton.y<=580) )
                    {
                        //back to menu

                        return 0;
                    }
                }
            }
        }

        window.clear();
        window.draw(ajutor);
        window.display();
    }
}


void initializare()
{
    nrPereti=0;
    for(int i=1; i<=18; ++i)
        for(int j=1; j<=18; ++j)
        Map[i][j]=0;
}

void play ()
{
    int i, turn=1, actualX, actualY;
    char numeImagine[]={"pawn0.png"}, rand[]={"cerc0.png"}, numePerete[]={"perete0.png"};
    casuta next;
    d[0].lin=-1; d[1].lin=0; d[2].lin=1; d[3].lin=0;
    d[0].col=0; d[1].col=1; d[2].col=0; d[3].col=-1;

    sf::Event eveniment;
    sf::Texture textura, texturaPawn, texturaTurn, texturaWall;
    textura.loadFromFile("tabla1.png");
    sf::Sprite board(textura);

    player[1].pozitie.lin=9; player[1].pozitie.col=5; Map[2*player[1].pozitie.lin-1][2*player[1].pozitie.col-1]=1;
    player[2].pozitie.lin=1; player[2].pozitie.col=5; Map[2*player[2].pozitie.lin-1][2*player[2].pozitie.col-1]=1;

    if(NumberOfPlayers!=2)
    {
        player[3].pozitie.lin=5; player[3].pozitie.col=1; Map[2*player[3].pozitie.lin-1][2*player[3].pozitie.col-1]=1;
        player[4].pozitie.lin=5; player[4].pozitie.col=9; Map[2*player[4].pozitie.lin-1][2*player[4].pozitie.col-1]=1;
    }

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
                                if( winner(turn) )
                                {
                                    //avem un castigator
                                    cout<<"CASTIGATOR "<<turn<<"-> "<<player[turn].pozitie.lin<<' '<<player[turn].pozitie.col <<'\n';
                                    return;
                                }
                                ++turn;
                                if(turn==NumberOfPlayers+1) turn=1;
                                break;

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
                                    if( winner(turn) )
                                    {
                                        //avem un castigator
                                        return;
                                    }

                                    ++turn;
                                    if(turn==NumberOfPlayers+1) turn=1;
                                    break;
                               }
                        }

                        if (    player[turn].nrWalls &&
                                !Map[ 2*(  ( (actualY-116)-(actualY-116)%79) /79 +1 ) ][2*( ( (actualX-116)-(actualX-116)%79) /79) +1 ] &&
                                !Map[ 2*( ( (actualY-116)-(actualY-116)%79) /79+1 ) ][ 2*( ( (actualX-116)-(actualX-116)%79) /79 ) +2 ] &&
                                !Map[ 2*( ( (actualY-116)-(actualY-116)%79) /79 +1 ) ][ 2*( ( (actualX-116)-(actualX-116)%79) /79 ) +3 ] &&
                                51<actualY &&actualY<748 &&
                                51<actualX &&actualX<748  &&
                                0< (actualY-116)%79 && (actualY-116)%79<14 )
                        {



                            ++nrPereti;
                            pereti[nrPereti].col=51+(actualX-116)-(actualX-116)%79;
                            pereti[nrPereti].lin=118+(actualY-116)-(actualY-116)%79;
                            pereti[nrPereti].poz=1;

                            Map[ 2*( (pereti[nrPereti].lin-118)/79 +1 ) ][ 2*( (pereti[nrPereti].col-51)/79 )+1 ]=1;
                            Map[ 2*( (pereti[nrPereti].lin-118)/79 +1 ) ][ 2*( (pereti[nrPereti].col-51)/79 )+2 ]=1;
                            Map[ 2*( (pereti[nrPereti].lin-118)/79 +1 ) ][ ( 2*(pereti[nrPereti].col-51)/79 )+3 ]=1;

                            for(i=1; i<=NumberOfPlayers; ++i)
                            {
                                cout<<i<<' '<<lee(i) <<'\n';
                                if(!lee(i)) break;
                            }
                            if(i==NumberOfPlayers+1)
                            {

                                --player[turn].nrWalls;
                                ++turn;
                                if(turn==NumberOfPlayers+1) turn=1;
                            }
                            else
                            {
                                Map[ 2*( (pereti[nrPereti].lin-118)/79 +1 ) ][ 2*( (pereti[nrPereti].col-51)/79 )+1 ]=0;
                                Map[ 2*( (pereti[nrPereti].lin-118)/79 +1 ) ][ 2*( (pereti[nrPereti].col-51)/79 )+2 ]=0;
                                Map[ 2*( (pereti[nrPereti].lin-118)/79 +1 ) ][ ( 2*(pereti[nrPereti].col-51)/79 )+3 ]=0;
                                --nrPereti;
                            }

//                            for(int x=1; x<=18; ++x)
//                            {
//                                for(int y=1; y<=18; ++y)
//                                    cout<<Map[x][y]<<' ';
//
//                                cout<<'\n';
//                            }
//                            cout<<2*( (pereti[nrPereti].lin-118)/79 +1 )<<' '<<2*( (pereti[nrPereti].col-51)/79  )+1<<'\n';
//                            cout<<2*( (pereti[nrPereti].lin-118)/79 +1 )<<' '<<2*( (pereti[nrPereti].col-51)/79 )+2<<'\n';
//                            cout<<2*( (pereti[nrPereti].lin-118)/79 +1 )<<' '<<( 2*(pereti[nrPereti].col-51)/79 )+3<<'\n';


                        }
                        else if(     player[turn].nrWalls &&
                                    !Map[ 2*( ( (actualY-116)-(actualY-116)%79)/79 +1) -1 ][ 2*( ( (actualX-116)-(actualX-116)%79)/79 +1) ] &&
                                    !Map[  2*( ( (actualY-116)-(actualY-116)%79)/79 +1) ][ 2*( ( (actualX-116)-(actualX-116)%79)/79 +1) ] &&
                                    !Map[  2*( ( (actualY-116)-(actualY-116)%79)/79 +1) +1 ][ 2*( ( (actualX-116)-(actualX-116)%79)/79 +1) ] &&
                                    51<actualY &&actualY<748 &&
                                    51<actualX &&actualX<748  &&
                                0<(actualX-116)%79 &&(actualX-116)%79<14 )
                        {


                            ++nrPereti;
                            pereti[nrPereti].col=118+(actualX-116)-(actualX-116)%79;
                            pereti[nrPereti].lin=51+(actualY-116)-(actualY-116)%79;
                            pereti[nrPereti].poz=2;

                            Map[ 2* ( (pereti[nrPereti].lin-51)/79 +1) -1 ][ 2*( (pereti[nrPereti].col-118)/79 +1) ]=1;
                            Map[  2* ( (pereti[nrPereti].lin-51)/79 +1)  ][ 2*( (pereti[nrPereti].col-118)/79 +1) ]=1;
                            Map[  2* ( (pereti[nrPereti].lin-51)/79 +1) +1 ][ 2*( (pereti[nrPereti].col-118)/79 +1) ]=1;

                            for(i=1; i<=NumberOfPlayers; ++i)
                            {
                                cout<<i<<' '<<lee(i)<<'\n';
                                if(!lee(i)) break;
                            }

                            if(i==NumberOfPlayers+1)
                            {
                                --player[turn].nrWalls;
                                ++turn;
                                if(turn==NumberOfPlayers+1) turn=1;
                            }
                            else
                            {

                                Map[ 2* ( (pereti[nrPereti].lin-51)/79 +1) -1 ][ 2*( (pereti[nrPereti].col-118)/79 +1) ]=0;
                                Map[  2* ( (pereti[nrPereti].lin-51)/79 +1)  ][ 2*( (pereti[nrPereti].col-118)/79 +1) ]=0;
                                Map[  2* ( (pereti[nrPereti].lin-51)/79 +1) +1 ][ 2*( (pereti[nrPereti].col-118)/79 +1) ]=0;
                                --nrPereti;
                            }
//
//                            for(int x=1; x<=18; ++x)
//                            {
//                                for(int y=1; y<=18; ++y)
//                                    cout<<Map[x][y]<<' ';
//
//                                cout<<'\n';
//                            }
//
//
//                            cout<<2* ( (pereti[nrPereti].lin-51)/79 +1) -1 <<' '<< 2*( (pereti[nrPereti].col-118)/79 +1)<<'\n';
//                            cout<<2* ( (pereti[nrPereti].lin-51)/79 +1) <<' '<< 2*( (pereti[nrPereti].col-118)/79 +1)<<'\n';
//                            cout<<2* ( (pereti[nrPereti].lin-51)/79 +1) +1 <<' '<< 2*( (pereti[nrPereti].col-118)/79 +1)<<'\n';
                        }

                    }


                for(int x=1; x<=18; ++x)
                {
                    for(int y=1; y<=18; ++y)
                        cout<<Map[x][y]<<' ';

                    cout<<'\n';
                }

                cout<<'\n';

            }
            else if (eveniment.type == sf::Event::KeyPressed)
            {
                if (eveniment.key.code == sf::Keyboard::Escape)
                {
                    //pause();
                    if(!pause())
                        return;
                }
            }
        }



        if (    //lee(1) && lee(2) && lee(3) &&lee(4) &&
                player[turn].nrWalls &&
                51<eveniment.mouseMove.y &&eveniment.mouseMove.y<748 &&
                51<eveniment.mouseMove.x &&eveniment.mouseMove.x<748  &&
               0<(eveniment.mouseMove.y-116)%79&& (eveniment.mouseMove.y-116)%79<14 )
        {


            perete.col=51+(eveniment.mouseMove.x-116)-(eveniment.mouseMove.x-116)%79;
            perete.lin=118+(eveniment.mouseMove.y-116)-(eveniment.mouseMove.y-116)%79;
            perete.poz=1;
        }
        else if(    //lee(1) && lee(2) && lee(3) &&lee(4) &&
                    player[turn].nrWalls &&
                    51<eveniment.mouseMove.y &&eveniment.mouseMove.y<748 &&
                    51<eveniment.mouseMove.x &&eveniment.mouseMove.x<748  &&
                0<(eveniment.mouseMove.x-116)%79 && (eveniment.mouseMove.x-116)%79<14 )
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

        for(i=1; i<=NumberOfPlayers; ++i)
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



void singlePlay ()
{
    int i, j, turn=1, actualX, actualY, mini;
    char numeImagine[]={"pawn0.png"}, rand[]={"cerc0.png"}, numePerete[]={"perete0.png"};
    mut mutare;
    casuta next, aux;
    d[0].lin=-1; d[1].lin=0; d[2].lin=1; d[3].lin=0;
    d[0].col=0; d[1].col=1; d[2].col=0; d[3].col=-1;

    sf::Event eveniment;
    sf::Texture textura, texturaPawn, texturaTurn, texturaWall;
    textura.loadFromFile("tabla1.png");
    sf::Sprite board(textura);

    player[1].pozitie.lin=9; player[1].pozitie.col=5; Map[2*player[1].pozitie.lin-1][2*player[1].pozitie.col-1]=1;
    player[2].pozitie.lin=1; player[2].pozitie.col=5; Map[2*player[2].pozitie.lin-1][2*player[2].pozitie.col-1]=1;

    while (window.isOpen() )
    {
        while(window.pollEvent(eveniment) )
        {
            if(eveniment.type==sf::Event::EventType::Closed)
                window.close();

            else if(eveniment.type == sf::Event::MouseButtonPressed && turn==1)
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
                                if( winner(turn) )
                                {
                                    //avem un castigator
                                    return;
                                }
                                ++turn;
                                if(turn==NumberOfPlayers+1) turn=1;
                                break;

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
                                    if( winner(turn) )
                                    {
                                        //avem un castigator
                                        return;
                                    }

                                    ++turn;
                                    if(turn==NumberOfPlayers+1) turn=1;
                                    break;
                               }
                        }

                        if (    player[turn].nrWalls &&
                                !Map[ 2*(  ( (actualY-116)-(actualY-116)%79) /79 +1 ) ][2*( ( (actualX-116)-(actualX-116)%79) /79) +1 ] &&
                                !Map[ 2*( ( (actualY-116)-(actualY-116)%79) /79+1 ) ][ 2*( ( (actualX-116)-(actualX-116)%79) /79 ) +2 ] &&
                                !Map[ 2*( ( (actualY-116)-(actualY-116)%79) /79 +1 ) ][ 2*( ( (actualX-116)-(actualX-116)%79) /79 ) +3 ] &&
                                51<actualY &&actualY<748 &&
                                51<actualX &&actualX<748  &&
                                0< (actualY-116)%79 && (actualY-116)%79<14 )
                        {



                            ++nrPereti;
                            pereti[nrPereti].col=51+(actualX-116)-(actualX-116)%79;
                            pereti[nrPereti].lin=118+(actualY-116)-(actualY-116)%79;
                            pereti[nrPereti].poz=1;

                            Map[ 2*( (pereti[nrPereti].lin-118)/79 +1 ) ][ 2*( (pereti[nrPereti].col-51)/79 )+1 ]=1;
                            Map[ 2*( (pereti[nrPereti].lin-118)/79 +1 ) ][ 2*( (pereti[nrPereti].col-51)/79 )+2 ]=1;
                            Map[ 2*( (pereti[nrPereti].lin-118)/79 +1 ) ][ ( 2*(pereti[nrPereti].col-51)/79 )+3 ]=1;

                            for(i=1; i<=NumberOfPlayers; ++i)
                            {
                                cout<<i<<' '<<lee(i)<<'\n';
                                if(!lee(i)) break;
                            }
                            if(i==NumberOfPlayers+1)
                            {

                                --player[turn].nrWalls;
                                ++turn;
                                if(turn==NumberOfPlayers+1) turn=1;
                            }
                            else
                            {
                                Map[ 2*( (pereti[nrPereti].lin-118)/79 +1 ) ][ 2*( (pereti[nrPereti].col-51)/79 )+1 ]=0;
                                Map[ 2*( (pereti[nrPereti].lin-118)/79 +1 ) ][ 2*( (pereti[nrPereti].col-51)/79 )+2 ]=0;
                                Map[ 2*( (pereti[nrPereti].lin-118)/79 +1 ) ][ ( 2*(pereti[nrPereti].col-51)/79 )+3 ]=0;
                                --nrPereti;
                            }

//                            for(int x=1; x<=18; ++x)
//                            {void singlePlay ()
//                                for(int y=1; y<=18; ++y)
//                                    cout<<Map[x][y]<<' ';
//
//                                cout<<'\n';
//                            }
//                            cout<<2*( (pereti[nrPereti].lin-118)/79 +1 )<<' '<<2*( (pereti[nrPereti].col-51)/79  )+1<<'\n';
//                            cout<<2*( (pereti[nrPereti].lin-118)/79 +1 )<<' '<<2*( (pereti[nrPereti].col-51)/79 )+2<<'\n';
//                            cout<<2*( (pereti[nrPereti].lin-118)/79 +1 )<<' '<<( 2*(pereti[nrPereti].col-51)/79 )+3<<'\n';


                        }
                        else if(     player[turn].nrWalls &&
                                    !Map[ 2*( ( (actualY-116)-(actualY-116)%79)/79 +1) -1 ][ 2*( ( (actualX-116)-(actualX-116)%79)/79 +1) ] &&
                                    !Map[  2*( ( (actualY-116)-(actualY-116)%79)/79 +1) ][ 2*( ( (actualX-116)-(actualX-116)%79)/79 +1) ] &&
                                    !Map[  2*( ( (actualY-116)-(actualY-116)%79)/79 +1) +1 ][ 2*( ( (actualX-116)-(actualX-116)%79)/79 +1) ] &&
                                    51<actualY &&actualY<748 &&
                                    51<actualX &&actualX<748  &&
                                0<(actualX-116)%79 &&(actualX-116)%79<14 )
                        {


                            ++nrPereti;
                            pereti[nrPereti].col=118+(actualX-116)-(actualX-116)%79;
                            pereti[nrPereti].lin=51+(actualY-116)-(actualY-116)%79;
                            pereti[nrPereti].poz=2;

                            Map[ 2* ( (pereti[nrPereti].lin-51)/79 +1) -1 ][ 2*( (pereti[nrPereti].col-118)/79 +1) ]=1;
                            Map[  2* ( (pereti[nrPereti].lin-51)/79 +1)  ][ 2*( (pereti[nrPereti].col-118)/79 +1) ]=1;
                            Map[  2* ( (pereti[nrPereti].lin-51)/79 +1) +1 ][ 2*( (pereti[nrPereti].col-118)/79 +1) ]=1;

                            for(i=1; i<=NumberOfPlayers; ++i)
                            {
                                cout<<i<<' '<<lee(i)<<'\n';
                                if(!lee(i)) break;
                            }

                            if(i==NumberOfPlayers+1)
                            {
                                --player[turn].nrWalls;
                                ++turn;
                                if(turn==NumberOfPlayers+1) turn=1;
                            }
                            else
                            {

                                Map[ 2* ( (pereti[nrPereti].lin-51)/79 +1) -1 ][ 2*( (pereti[nrPereti].col-118)/79 +1) ]=0;
                                Map[  2* ( (pereti[nrPereti].lin-51)/79 +1)  ][ 2*( (pereti[nrPereti].col-118)/79 +1) ]=0;
                                Map[  2* ( (pereti[nrPereti].lin-51)/79 +1) +1 ][ 2*( (pereti[nrPereti].col-118)/79 +1) ]=0;
                                --nrPereti;
                            }
//
//                            for(int x=1; x<=18; ++x)
//                            {
//                                for(int y=1; y<=18; ++y)
//                                    cout<<Map[x][y]<<' ';
//
//                                cout<<'\n';
//                            }
//
//
//                            cout<<2* ( (pereti[nrPereti].lin-51)/79 +1) -1 <<' '<< 2*( (pereti[nrPereti].col-118)/79 +1)<<'\n';
//                            cout<<2* ( (pereti[nrPereti].lin-51)/79 +1) <<' '<< 2*( (pereti[nrPereti].col-118)/79 +1)<<'\n';
//                            cout<<2* ( (pereti[nrPereti].lin-51)/79 +1) +1 <<' '<< 2*( (pereti[nrPereti].col-118)/79 +1)<<'\n';
                        }

                    }


            }
            else if (eveniment.type == sf::Event::KeyPressed)
            {
                if (eveniment.key.code == sf::Keyboard::Escape)
                {
                    //pause();
                    if(!pause())
                        return;
                }
            }


        }


        if(turn==2)
        {

            mini=100;
            for(i=0; i<4; ++i)
            {
                next.lin=player[turn].pozitie.lin+d[i].lin;
                next.col=player[turn].pozitie.col+d[i].col;

                if(
                   !Map[2*next.lin-1][2*next.col-1] && !Map[2*player[turn].pozitie.lin-1+d[i].lin][2*player[turn].pozitie.col-1+d[i].col] &&
                    (0<next.lin && next.lin<=9) && (0<next.col && next.col<=9) )
                {

                    Map[2*player[turn].pozitie.lin-1][2*player[turn].pozitie.col-1]=0;
                    aux=player[turn].pozitie;
                    player[turn].pozitie=next;
                    Map[2*next.lin-1][2*next.col-1]=1;

                    cout<<next.lin<<" de aci "<< next.col<<"---> "<<lee(2)-lee(1)<<'\n';
                    if(mini > lee(2)-lee(1))
                    {
                        mini=lee(2)-lee(1);
                        mutare.fel=0;
                        mutare.lin=next.lin;
                        mutare.col=next.col;
                        cout<<2*mutare.lin-1<<' '<<2*mutare.col-1<<'\n';

                    }
                    player[turn].pozitie=aux;
                    Map[2*next.lin-1][2*next.col-1]=0;
                    Map[2*player[turn].pozitie.lin-1][2*player[turn].pozitie.col-1]=1;


                }
                else if(
                    Map[2*next.lin-1][2*next.col-1] && !Map[2*player[turn].pozitie.lin-1+d[i].lin][2*player[turn].pozitie.col-1+d[i].col] &&
                   (0<next.lin && next.lin<=9) && (0<next.col && next.col<=9) )
                   {
                        next.lin=next.lin+d[i].lin;
                        next.col=next.col+d[i].col;

                        Map[2*player[turn].pozitie.lin-1][2*player[turn].pozitie.col-1]=0;
                        //player[turn].pozitie=next;
                        Map[2*next.lin-1][2*next.col-1]=1;

                        cout<<next.lin<<' '<< next.col<<"---> "<<lee(2)-lee(1)<<'\n';
                        if(mini > lee(2)-lee(1))
                        {
                            mini=lee(2)-lee(1);
                            mutare.fel=0;
                            mutare.lin=next.lin;
                            mutare.col=next.col;
                            cout<<2*mutare.lin-1<<' '<<2*mutare.col-1<<'\n';

                        }

                        Map[2*next.lin-1][2*next.col-1]=0;
                        Map[2*player[turn].pozitie.lin-1][2*player[turn].pozitie.col-1]=1;
                   }
            }

            if(player[turn].nrWalls>0)
            {
                //orizontal

                for(i=2; i<=16; i=i+2)
                    for(j=1; j<=15; j=j+2)
                    if(!Map[i][j] && !Map[i][j+1] && !Map[i][j+2])
                    {
                        //pun perete
                        Map[i][j]=Map[i][j+1]=Map[i][j+2]=1;
                        if( mini > lee(2)-lee(1) && lee(1) && lee(2))
                        {
                            cout<<"PL\n";
                            mini=lee(2)-lee(1);
                            mutare.fel=1;
                            mutare.lin=i;
                            mutare.col=j;
                        }
                        Map[i][j]=Map[i][j+1]=Map[i][j+2]=0;
                    }

                //vertical
                for(i=2; i<=16; i=i+2)
                    for(j=1; j<=15; j=j+2)
                    if(!Map[j][i] && !Map[j+1][i] && !Map[j+2][i])
                    {
                        //pun perete
                        //cout<<Map[j][i]<<' '<<Map[j+1][i]<<' '<<Map[j+2][i]<<'\n';
                        Map[j][i]=Map[j+1][i]=Map[j+2][i]=1;
                        if( mini > lee(2)-lee(1) && lee(1) && lee(2))
                        {
                            cout<<"PL\n";
                            mini=lee(2)-lee(1);
                            mutare.fel=2;
                            mutare.lin=j;
                            mutare.col=i;
                        }
                        Map[j][i]=Map[j+1][i]=Map[j+2][i]=0;
                    }
            }

            //cout<<mutare.fel<<' '<<mutare.lin<<' '<<mutare.col<<' '<<mini<<'\n';
            //cout<<"MINI: "<<mini<<'\n';
            if(!mutare.fel)
            {
                cout<<2*mutare.lin-1<<' '<<2*mutare.col-1<<'\n';
                Map[ 2*player[turn].pozitie.lin-1 ][ 2*player[turn].pozitie.col-1 ]=0;
                player[turn].pozitie.lin=mutare.lin;
                player[turn].pozitie.col=mutare.col;
                Map[ 2*player[turn].pozitie.lin-1 ][ 2*player[turn].pozitie.col-1 ] =1;


                if(winner(turn))
                {
                    //te-a batut, fraiere
                    return;
                }

                ++turn;
                if(turn==NumberOfPlayers+1) turn=1;
            }
            else if(mutare.fel==1)
            {
                ++nrPereti;
                pereti[nrPereti].col=(mutare.col/2)*79+51;
                pereti[nrPereti].lin=(mutare.lin/2-1)*79+118;
                pereti[nrPereti].poz=1;

                Map[ mutare.lin ][ mutare.col ]=1;
                Map[ mutare.lin ][ mutare.col+1 ]=1;
                Map[ mutare.lin ][ mutare.col+2 ]=1;

                --player[turn].nrWalls;
                ++turn;
                if(turn==NumberOfPlayers+1) turn=1;

            }
            else if(mutare.fel==2)
            {
                ++nrPereti;
                pereti[nrPereti].col=(mutare.col/2-1)*79+118;
                pereti[nrPereti].lin=(mutare.lin/2)*79+51;
                pereti[nrPereti].poz=2;

                Map[ mutare.lin ][ mutare.col ]=1;
                Map[ mutare.lin+1 ][ mutare.col ]=1;
                Map[ mutare.lin+2 ][ mutare.col ]=1;

                --player[turn].nrWalls;
                ++turn;
                if(turn==NumberOfPlayers+1) turn=1;

            }

            for(int x=1; x<=18; ++x)
            {
                for(int y=1; y<=18; ++y)
                    cout<<Map[x][y]<<' ';

                cout<<'\n';
            }

        }




        if (    //lee(1) && lee(2) && lee(3) &&lee(4) &&
                player[turn].nrWalls &&
                51<eveniment.mouseMove.y &&eveniment.mouseMove.y<748 &&
                51<eveniment.mouseMove.x &&eveniment.mouseMove.x<748  &&
               0<(eveniment.mouseMove.y-116)%79&& (eveniment.mouseMove.y-116)%79<14 )
        {


            perete.col=51+(eveniment.mouseMove.x-116)-(eveniment.mouseMove.x-116)%79;
            perete.lin=118+(eveniment.mouseMove.y-116)-(eveniment.mouseMove.y-116)%79;
            perete.poz=1;
        }
        else if(    //lee(1) && lee(2) && lee(3) &&lee(4) &&
                    player[turn].nrWalls &&
                    51<eveniment.mouseMove.y &&eveniment.mouseMove.y<748 &&
                    51<eveniment.mouseMove.x &&eveniment.mouseMove.x<748  &&
                0<(eveniment.mouseMove.x-116)%79 && (eveniment.mouseMove.x-116)%79<14 )
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

        for(i=1; i<=NumberOfPlayers; ++i)
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

int lee(int indPlayer)
{
    int i, j, prim ,ultim;
    casuta actual, next;
    casuta coada[200];
    prim=ultim=0;
    coada[0]=player[indPlayer].pozitie;

    for(i=1; i<=18; ++i)
    {
        for(j=1; j<=18; ++j)
        {
            //cout<<Vali[i][j]<<' ';
            if(i%2==0 || j%2==0)
                Vali[i][j]=-Map[i][j];
            else Vali[i][j]=0;
        }
        //cout<<'\n';
    }

    Vali[2*coada[0].lin-1][2*coada[0].col-1]=1;

    while (prim<=ultim && gata(indPlayer)==900000000 )
    {
        actual=coada[prim++];
        for(i=0; i<4; ++i)
        {
            next.lin=actual.lin+d[i].lin;
            next.col=actual.col+d[i].col;

            if(
               !Vali[2*next.lin-1][2*next.col-1] && !Vali[2*actual.lin-1+d[i].lin][2*actual.col-1+d[i].col] &&
                (0<next.lin && next.lin<=9) && (0<next.col && next.col<=9) )
            {
                Vali[2*next.lin-1][2*next.col-1]=Vali[2*actual.lin-1][2*actual.col-1]+1;
                coada[++ultim]=next;
            }
        }

    }

//    for(i=1; i<=17; ++i)
//    {
//        for(j=1; j<=17; ++j)
//            if(10<Vali[i][j] && Vali[i][j]>=0)cout<<Vali[i][j]<<' ';
//            else cout<<Vali[i][j]<<"  ";
//        cout<<'\n';
//    }
//    cout<<'\n'<<gata(indPlayer)<<'\n';
//    if(prim>ultim)
//        return 0;

    if(prim>ultim)
        return 0;
    return gata(indPlayer);
}

int gata (int indPlayer)
{
    int i, mini=900000000;
    switch (indPlayer)
    {
        case 2:
                {

                  for(i=1; i<=17; i=i+2)
                    if(Vali[17][i]>0 && Vali[17][i]<mini)
                        mini=Vali[17][i];
                    return mini;

                }
        case 1:
                {
                    for(i=1; i<=17; i=i+2)
                        if(Vali[1][i]>0 && Vali[1][i]<mini)
                        mini=Vali[1][i];
                    return mini;
                }
        case 3:
            {
                for(i=1; i<=17; i=i+2)
                    if(Vali[i][17]>0 && Vali[i][17]<mini)
                        mini=Vali[i][17];
                    return mini;
            }
        case 4:
            {
                for(i=1; i<=17; i=i+2)
                    if(Vali[i][1]>0 && Vali[i][1]<mini)
                        mini=Vali[i][1];
                return mini;
            }

    }
    return mini;
}

bool winner (int indPlayer)
{
    switch (indPlayer)
    {
        case 2:
                {

                  cout<<indPlayer<<'\n';
                  if(player[indPlayer].pozitie.lin==9)
                        return true;

                    break;


                }
        case 1:
                {
                    if(player[indPlayer].pozitie.lin==1)

                        return true;

                    break;
                }
        case 3:
            {
                if(player[indPlayer].pozitie.col==9)
                        return true;
                break;
            }
        case 4:
            {
                if(player[indPlayer].pozitie.col==1)
                        return true;
                break;
            }

    }
    return false;
}
