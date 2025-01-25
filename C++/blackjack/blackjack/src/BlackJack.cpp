#include "BlackJack.h"
#include "ncursesw/ncurses.h"

#include <iostream>
using namespace std;

string itos(int x) {
    string s = "";

    if (!x) {
        return "0";
    }

    while (x) {
        s += (x % 10) + '0';
        x /= 10;
    }

    for (int i = 0; i < s.length() / 2; i++) {
        char c = s[i];
        s[i] = s[s.length() - (i + 1)];
        s[s.length() - (i + 1)] = c;
    }

    return s;
}

void BlackJack::restart_game() {
    gameOver = false;
    pot = 0;

    if (buttons.size() != 3) {
        buttons.push_back("RAISE");
    }
    
    deck.resetDeck();
    DealerHand.clear();
    PlayerHand.clear();

    DealerHand.visibility = 1;

    DealerHand.add_card(deck.getCard());
    PlayerHand.add_card(deck.getCard());
    DealerHand.add_card(deck.getCard());

    draw();
}

BlackJack::BlackJack() : DealerHand(1) {
    restart_game();

    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
    init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
    init_pair(RED, COLOR_WHITE, COLOR_RED);
}

void BlackJack::start_game() {

    // mvaddstr(20, 0, "hello");
    gameOver = false;
    draw();

    while (true) {
        if (!gameOver) {
            if (update()) {
                return;
            }
        }
        else if (gameOver) {
            mvaddstr(20, 80, "Press 'Q' to Quit.");
            mvaddstr(22, 80, "Press Any Other Key to Replay.");
            char c = getch();
            if (c == 'q') {
                return;
            }
            else if (c != ERR) {
                restart_game();
            }
        }
    }

}

// returns if game is over
bool BlackJack::update() {
    bool changes = true;

    char gotChar = getch();

    switch (gotChar) {
        case 'q':
            return true;

        case 'a':
            buttonSelect = (buttonSelect - 1) % buttons.size();
            break;

        case 'd':
            buttonSelect = (buttonSelect + 1) % buttons.size();
            break;
        
        case 'w':
            if (buttons[buttonSelect] == "HIT") {
                hit();
            }
            else if (buttons[buttonSelect] == "STAND") {
                stand();
            }
            else if (buttons[buttonSelect] == "RAISE") {
                raise();
            }
            break;
        
        default:
            changes = false;
            break;
    }

    if (changes) {
        draw();
    }

    return false;
}

int BlackJack::hand_value(Hand hand) {

    int aceCount = 0;
    int sum = 0;

    for (int i = 0; i < hand.size(); i++) {

        int card = hand.cards[i].getValue();

        if (card == ACE) {
            aceCount++;
            sum += 11;
            continue;
        }
        else if (card >= MIN_FACE_CARD) {
            sum += 10;
            continue;
        }

        sum += card;
    }

    while ((sum > 21) && (aceCount)) {
        sum -= 10;
        aceCount--;
    }

    return sum;
}

/*

  0 1 2 3 4 5 6 7
0 [ - - - - - - ]
1 | * * * * * * |
2 | * T e s t * |
3 | * * * * * * |
4 [ - - - - - - ]

padding = 1 ^^^^^
(represented by *'s)

*/
void BlackJack::draw_button(string text, int x, int y, int padding) {

    int len = text.length();
    int half = padding / 2;
    int twice = (padding * 2) + 1;

    int width = twice + len;
    int height = twice;

    mvhline(y, x + 1, ACS_HLINE, width - 1);
    mvhline(y + twice + 1, x + 1, ACS_HLINE, width - 1);

    mvvline(y + 1, x, ACS_VLINE, height);
    mvvline(y + 1, x + width, ACS_VLINE, height);

    mvaddch(y, x, ACS_ULCORNER);
    mvaddch(y + height + 1, x, ACS_LLCORNER);
    mvaddch(y, x + width, ACS_URCORNER);
    mvaddch(y + height + 1, x + width, ACS_LRCORNER);

    mvaddstr(y + padding + 1, x + padding + 1, text.c_str());

}

int BlackJack::button_length(string text, int padding) {
    return text.length() + (padding * 2) + 2;
}

void BlackJack::hit() {

    if (buttons.size() == 3) {
        // get rid of raise option after hit
        buttons.pop_back();
    }

    PlayerHand.add_card(deck.getCard());

    if (hand_value(PlayerHand) > 21) {
        gameOver = true;
        playerWins = false;
        DealerHand.reveal();
    }

}

void BlackJack::stand() {

    // player > dealer, dealer draws
    // dealer >= player, dealer wins

    while (true) {
        if (hand_value(PlayerHand) > hand_value(DealerHand)) {
            DealerHand.add_card(deck.getCard());
            continue;
        }
        
        break;
    }

    if (hand_value(DealerHand) > 21) {
        playerWins = true;
        playerMoney += pot * 2;
    }
    
    if (hand_value(DealerHand) == 21 && hand_value(PlayerHand) == 21) {
        playerWins = false;
    }

    DealerHand.reveal();
    gameOver = true;

}

void BlackJack::raise() {
    pot += 100;
    playerMoney -= 100;
}

void BlackJack::draw() {

    clear();
    DealerHand.draw(50, 10);
    PlayerHand.draw(50, 20);

    int sum = 0;

    for (int i = 0; i < buttons.size(); i++) {
        if (buttonSelect == i) {
            color_set(YELLOW, nullptr);
        }
        else {
            color_set(WHITE, nullptr);
        }

        // mvaddstr(20, 20 + (i * 3), buttons[i].c_str());
        draw_button(buttons[i], sum + 20 + (i * 2), 30, 2);
        sum += button_length(buttons[i], 2);

    }

    if (playerMoney > 0) {
        color_set(GREEN, nullptr);
    }
    else {
        color_set(RED, nullptr);
    }

    mvaddstr(10, 80, "Money: $");
    mvaddstr(10, 88, itos(playerMoney).c_str());
    mvaddstr(10, 88 + itos(playerMoney).length(), "!");
    
    color_set(WHITE, nullptr);
    mvaddstr(12, 80, "Pot: $");
    mvaddstr(12, 86, itos(pot).c_str());
    mvaddstr(12, 86 + itos(pot).length(), "!");

    if (gameOver) {

        color_set(WHITE, nullptr);
        mvaddstr(10, 20, "Dealer's Hand:");
        mvaddstr(11, 20, itos(hand_value(DealerHand)).c_str());
        mvaddstr(20, 20, "Your Hand:");
        mvaddstr(21, 20, itos(hand_value(PlayerHand)).c_str());

        if (playerWins) {
            color_set(GREEN, nullptr);
            mvaddstr(17, 80, "YOU WIN $");
            mvaddstr(17, 89, itos(pot * 2).c_str());
            mvaddstr(17, 89 + itos(pot * 2).length(), "!");
        }
        else {
            color_set(RED, nullptr);
            mvaddstr(17, 80, "YOU LOST $");
            mvaddstr(17, 90, itos(pot).c_str());
            mvaddstr(17, 90 + itos(pot).length(), "!");
        }
    }
}