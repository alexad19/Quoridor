int NumberOfPlayers;

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
    int nrWalls;
};

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
void whoWonMP (int indPlayer);
void whoWonSP (int indPlayer);

