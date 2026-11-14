#include "game.h"
#include <iostream>

using namespace std;

void hit(Player& player, Deck& deck) {
    Card card = dealCard(deck);
    cout << player.name << " draws: ";
    display(card);
    addCardToHand(player, card);
}

void stand(Player& player, Deck&) {
    cout << player.name << " stands.\n";
}

void display(const Card& card) {
    cout << rankName(card.rank) << " of " << suitName(card.suit)
        << " (" << card.points << ")\n";
}

void display(const Player& player) {
    cout << player.name << " [" << player.score << "]: ";
    for (int i = 0; i < player.cardCount; ++i) {
        if (i > 0) cout << ", ";
        cout << rankName(player.hand[i].rank) << " of "
            << suitName(player.hand[i].suit);
    }
    cout << "\n";
}

void display(const Player& player, const char* label) {
    cout << label << "\n";
    display(player);
}

void dealerTurn(Player& dealer, Deck& deck) {
    if (!dealerShouldHit(dealer))
        return;
    Card card = dealCard(deck);
    cout << dealer.name << " draws: ";
    display(card);
    addCardToHand(dealer, card);
    dealerTurn(dealer, deck);
}

void printRoundResult(const Player& player, const Player& dealer) {
    static int roundCounter = 0;
    ++roundCounter;

    cout << "\n=== Round " << roundCounter << " result ===\n";
    display(player);
    display(dealer);

    bool playerBust = isBust(player);
    bool dealerBust = isBust(dealer);

    if (playerBust && dealerBust)     cout << "Both bust. Draw.\n";
    else if (playerBust)                   cout << "You bust. Dealer wins.\n";
    else if (dealerBust)                   cout << "Dealer busts. You win!\n";
    else if (player.score > dealer.score)  cout << "You win!\n";
    else if (player.score < dealer.score)  cout << "Dealer wins.\n";
    else                                   cout << "Draw.\n";
}

void playRound(Player& player, Player& dealer, Deck& deck) {
    resetPlayer(player);
    resetPlayer(dealer);

    for (int i = 0; i < 2; ++i) {
        Card card = dealCard(deck);
        cout << player.name << " draws: ";
        display(card);
        addCardToHand(player, card);
    }
    for (int i = 0; i < 2; ++i)
        addCardToHand(dealer, dealCard(deck));

    cout << "\nDealer upcard: ";
    display(dealer.hand[0]);

    ActionFunc actions[2] = { hit, stand };

    while (!isBust(player)) {
        display(player, "Your current hand:");
        cout << "Action (0 - Hit, 1 - Stand): ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input.\n";
            continue;
        }
        if (choice < 0 || choice > 1) {
            cout << "Invalid choice.\n";
            continue;
        }
        actions[choice](player, deck);
        if (choice == 1) break;
    }

    if (!isBust(player)) {
        cout << "\nDealer's turn:\n";
        dealerTurn(dealer, deck);
    }

    printRoundResult(player, dealer);
}

bool askPlayAgain() {
    char answer;
    cout << "\nPlay again? (y/n): ";
    cin >> answer;
    return answer == 'y' || answer == 'Y';
}