#include "BlackJack.h"
#include "ncursesw/ncurses.h"

#include <iostream>
using namespace std;

string itos(int x) {
    string s = "";
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
    init_pair(RED, COLOR_RED, COLOR_WHITE);
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
            mvaddstr(20, 35, "Press 'Q' to Quit.");
            mvaddstr(22, 35, "Press Any Other Key to Replay.");
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
            break;
        
        case 'h':
            // HIT
            hit();
            break;
        
        case 's':
            // STAND
            stand();
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
        if (hand.cards[i].getValue() == ACE) {
            aceCount++;
            sum += 11;
            continue;
        }

        sum += hand.cards[i].getValue();
    }

    while ((sum > 21) and (aceCount)) {
        sum -= 10;
    }

    return sum;
}

void BlackJack::draw_button(string text, int x, int y, int padding) {

    int len = text.length();

    mvaddstr(y, x, text.c_str());
    mvaddch(y - padding, x - padding, ACS_ULCORNER);
    mvaddch(y + padding, x - padding, ACS_LLCORNER);
    mvaddch(y + padding, x + padding + len, ACS_LRCORNER);
    mvaddch(y - padding, x + padding + len, ACS_URCORNER);

    mvhline(y - padding, x - padding + 1, ACS_HLINE, len + padding + 1);
    mvhline(y + padding, x - padding + 1, ACS_HLINE, len + padding + 1);

    mvvline(y - padding + 1, x - padding, ACS_VLINE, padding + 1);
    mvvline(y - padding + 1, x + padding + len, ACS_VLINE, padding + 1);
}

void BlackJack::hit() {
    PlayerHand.add_card(deck.getCard());

    if (PlayerHand.getValue() > 21) {
        gameOver = true;
        playerWins = false;
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
    }
    
    if (hand_value(DealerHand) == 21 && hand_value(PlayerHand) == 21) {
        playerWins = false;
    }

    DealerHand.reveal();
    gameOver = true;

}

void BlackJack::draw() {

    clear();
    DealerHand.draw(50, 10);
    PlayerHand.draw(50, 20);

    for (int i = 0; i < buttons.size(); i++) {
        if (buttonSelect == i) {
            color_set(YELLOW, nullptr);
        }
        else {
            color_set(WHITE, nullptr);
        }

        // mvaddstr(20, 20 + (i * 3), buttons[i].c_str());
        draw_button(buttons[i], 20 + (i * 10), 30, 2);
    }

    if (gameOver) {

        color_set(WHITE, nullptr);
        mvaddstr(10, 20, "Dealer's Hand:");
        mvaddstr(11, 20, itos(hand_value(DealerHand)).c_str());
        mvaddstr(20, 20, "Your Hand:");
        mvaddstr(21, 20, itos(hand_value(PlayerHand)).c_str());

        if (playerWins) {
            color_set(GREEN, nullptr);
            mvaddstr(17, 55, "YOU WIN!");
        }
        else {
            color_set(RED, nullptr);
            mvaddstr(17, 55, "YOU LOST!");
        }
    }
}