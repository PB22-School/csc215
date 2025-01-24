#include "BlackJack.h"
#include "ncursesw/ncurses.h"

#include <iostream>
using namespace std;

BlackJack::BlackJack() : DealerHand(1) {
    for (int i = 0; i < 2; i++) {
        DealerHand.add_card(deck.getCard());
    }
    
    PlayerHand.add_card(deck.getCard());

    init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
    init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
}

void BlackJack::start_game() {

    // mvaddstr(20, 0, "hello");
    draw();

    while (!gameOver) {
        if (update()) {
            return;
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

        case KEY_LEFT:
            buttonSelect = (buttonSelect - 1) % buttons.size();
            break;

        case KEY_RIGHT:
            buttonSelect = (buttonSelect + 1) % buttons.size();
            break;
        
        case KEY_ENTER:
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
        if (PlayerHand.getValue() > DealerHand.getValue()) {
            DealerHand.add_card(deck.getCard());
            continue;
        }
        
        break;
    }

    if (DealerHand.getValue() > 21) {
        playerWins = true;
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
        if (playerWins) {
            color_set(COLOR_GREEN, nullptr);
            mvaddstr(100, 60, "YOU WIN!");
        }
        else {
            color_set(COLOR_RED, nullptr);
            mvaddstr(100, 60, "YOU LOST!");
        }
    }
}