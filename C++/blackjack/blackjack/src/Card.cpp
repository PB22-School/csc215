#include "Card.h"
#include "ncursesw/ncurses.h"

Card::Card() {
    suit = 0;
    rank = 0;
}

Card::Card(int suit, int rank) {
    this->suit = suit;
    this->rank = rank;
}

int Card::getValue() const {
    return rank;
}


/*

[--]
|4 |
|* |
[--]

*/
void Card::display(int x, int y, bool visible = false) {

    if (suit == 0 || suit == 3) {
        color_set(COLOR_CARD_BLACK, nullptr);
    }
    else {
        color_set(COLOR_CARD_RED, nullptr);
    }

    if (visible) {
        switch (suit) {
        case 0:
            color_set(COLOR_CARD_BLACK, nullptr);
            mvaddstr(x + 1, y, "♣ ");
            break;
        case 1:
            color_set(COLOR_CARD_RED, nullptr);
            mvaddstr(x + 1, y, "♦ ");
            break;
        case 2:
            color_set(COLOR_CARD_RED, nullptr);
            mvaddstr(x + 1, y, "♦ ");
            break;
        case 3:
            color_set(COLOR_CARD_RED, nullptr);
            mvaddstr(x + 1, y, "♦ ");
            break;
        }
    }
    else {
        mvaddstr(x + 1, y, "█ ");
        mvaddstr(x + 1, y + 1, " █");
    }

    mvvline(x, y - 1, 0, 2);
    mvvline(x, y + 1, 0, 2);
    mvvline(x - 1, y - 1, 0, 2);
    mvvline(x + 2, y - 1, 0, 2);
    mvaddch(x - 1, y - 1, ACS_ULCORNER);
    mvaddch(x - 1, y + 2, ACS_URCORNER);
    mvaddch(x + 2, y - 1, ACS_LLCORNER);
    mvaddch(x + 2, y + 2, ACS_LRCORNER);

    if (!visible) {
        return;
    }

    switch (rank) {
    case 1:
        mvaddstr(x, y, "A ");
        break;
    case 2:
        mvaddstr(x, y, "2 ");
        break;
    case 3:
        mvaddstr(x, y, "3 ");
        break;
    case 4:
        mvaddstr(x, y, "4 ");
        break;
    case 5:
        mvaddstr(x, y, "5 ");
        break;
    case 6:
        mvaddstr(x, y, "6 ");
        break;
    case 7:
        mvaddstr(x, y, "7 ");
        break;
    case 8:
        mvaddstr(x, y, "8 ");
        break;
    case 9:
        mvaddstr(x, y, "9 ");
        break;
    case 10:
        mvaddstr(x, y, "10");
        break;
    case 11:
        mvaddstr(x, y, "J ");
        break;
    case 12:
        mvaddstr(x, y, "Q ");
        break;
    case 13:
        mvaddstr(x, y, "K ");
        break;
    }

}