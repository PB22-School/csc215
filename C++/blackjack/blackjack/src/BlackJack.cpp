#include "BlackJack.h"
#include "ncursesw/ncurses.h"

BlackJack::BlackJack() : DealerHand(1) {
    for (int i = 0; i < 2; i++) {
        DealerHand.add_card(deck.getCard());
        PlayerHand.add_card(deck.getCard());
    }
}

void BlackJack::start_game() {

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
    DealerHand.draw(50, 50);
    PlayerHand.draw(50, 75);

    for (int i = 1; i < buttons.size(); i++) {
        if (buttonSelect == i) {
            color_set(COLOR_YELLOW, nullptr);
        }
        else {
            color_set(COLOR_WHITE, nullptr);
        }

        mvaddstr(50, 80 + (i * 3), buttons[i].c_str());
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