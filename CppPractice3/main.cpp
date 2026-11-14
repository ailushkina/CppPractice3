#include "card.h"
#include "game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(static_cast<unsigned>(std::time(nullptr)));

    Player player;
    Player dealer;
    initPlayer(player, "Player");
    initPlayer(dealer, "Dealer");

    Deck deck;
    initDeck(deck);
    shuffleDeck(deck);

    cout << "=== Blackjack (36-card deck) ===\n";

    do {
        playRound(player, dealer, deck);
    } while (askPlayAgain());

    cout << "Thanks for playing!\n";
    return 0;
}