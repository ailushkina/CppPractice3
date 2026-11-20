#include "game.h"
#include <iostream>

using namespace std;

void hit(Player& player, Deck& deck) {
    Card card = dealCard(deck);
    cout << player.name << " берет карту: ";
    display(card);
    addCardToHand(player, card);
}

void stand(Player& player, Deck&) {
    cout << player.name << " останавливается (Stand).\n";
}

void display(const Card& card) {
    cout << rankName(card.rank) << " " << suitName(card.suit)
        << " (" << card.points << ")\n";
}

void display(const Player& player) {
    cout << player.name << " [" << player.score << "]: ";
    for (int i = 0; i < player.cardCount; ++i) {
        if (i > 0) cout << ", ";
        cout << rankName(player.hand[i].rank) << " "
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
    cout << dealer.name << " берет карту: ";
    display(card);
    addCardToHand(dealer, card);
    dealerTurn(dealer, deck);
}

void printRoundResult(const Player& player, const Player& dealer) {
    static int roundCounter = 0;
    ++roundCounter;

    cout << "\n=== Результат раунда " << roundCounter << " ===\n";
    display(player);
    display(dealer);

    bool playerBust = isBust(player);
    bool dealerBust = isBust(dealer);

    if (playerBust && dealerBust)          cout << "Перебор у обоих. Ничья.\n";
    else if (playerBust)                   cout << "У вас перебор. Дилер победил.\n";
    else if (dealerBust)                   cout << "У дилера перебор. Вы победили!\n";
    else if (player.score > dealer.score)  cout << "Вы победили!\n";
    else if (player.score < dealer.score)  cout << "Дилер победил.\n";
    else                                   cout << "Ничья.\n";
}

void playRound(Player& player, Player& dealer, Deck& deck) {
    resetPlayer(player);
    resetPlayer(dealer);

    for (int i = 0; i < 2; ++i) {
        Card card = dealCard(deck);
        cout << player.name << " берет карту: ";
        display(card);
        addCardToHand(player, card);
    }
    for (int i = 0; i < 2; ++i)
        addCardToHand(dealer, dealCard(deck));

    cout << "\nОткрытая карта дилера: ";
    display(dealer.hand[0]);

    ActionFunc actions[2] = { hit, stand };

    while (!isBust(player)) {
        display(player, "Ваши текущие карты:");
        cout << "Действие (0 - Взять карту [Hit], 1 - Остановиться [Stand]): ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка ввода.\n";
            continue;
        }
        if (choice < 0 || choice > 1) {
            cout << "Неверный выбор.\n";
            continue;
        }
        actions[choice](player, deck);
        if (choice == 1) break;
    }

    if (!isBust(player)) {
        cout << "\nХод дилера:\n";
        dealerTurn(dealer, deck);
    }

    printRoundResult(player, dealer);
}

bool askPlayAgain() {
    char answer;
    cout << "\nСыграть еще раз? (y/n): ";
    cin >> answer;
    return answer == 'y' || answer == 'Y';
}