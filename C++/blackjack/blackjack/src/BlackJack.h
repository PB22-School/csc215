#include "Deck.h"
#include "Hand.h"
#include <vector>
#include <string>
using namespace std;

enum colors {
    WHITE = 3,
    BLACK,
    YELLOW,
    GREEN,
    RED
};

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
    
    void restart_game();
    void start_game();
    bool update();

    void draw_button(string text, int x, int y, int padding);
    int hand_value(Hand hand);

    void draw();

    void hit();
    void stand();

};