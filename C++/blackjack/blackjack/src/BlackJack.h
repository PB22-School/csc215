#include "Deck.h"
#include "Hand.h"
#include <vector>
#include <string>
using namespace std;

class BlackJack {
    Deck deck;
    Hand DealerHand;
    Hand PlayerHand;
    bool gameOver = false;
    bool playerWins = false;

    int buttonSelect = 0;
    vector<string> buttons = {"HIT", "STAND"};

    public:
    BlackJack();
    
    void start_game();
    bool update();
    void draw();

    void hit();
    void stand();

};