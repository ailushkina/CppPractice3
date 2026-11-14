#ifndef GAME_H
#define GAME_H

#include "card.h"

inline bool isBust(const Player& player) {
    return player.score > MAX_SCORE;
}

inline bool dealerShouldHit(const Player& dealer) {
    return dealer.score < 17;
}

typedef void (*ActionFunc)(Player&, Deck&);

void hit(Player& player, Deck& deck);
void stand(Player& player, Deck& deck);

void display(const Card& card);
void display(const Player& player);
void display(const Player& player, const char* label);

void dealerTurn(Player& dealer, Deck& deck);
void printRoundResult(const Player& player, const Player& dealer);
void playRound(Player& player, Player& dealer, Deck& deck);
bool askPlayAgain();

#endif