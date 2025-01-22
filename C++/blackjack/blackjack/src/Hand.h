#include "Card.h"
#include <vector>
using namespace std;

typedef unsigned long ulong;

class Hand {
    vector<Card> cards;
    ulong visibility;
    bool is_private;

    public:
    Hand(ulong visiblity= ULONG_MAX);
    void add_card(Card card);
    Card drop_card(int cardIndex);

    bool equal();
    int size();
    int getValue();

    void reveal();
    void draw(int x, int y);
};