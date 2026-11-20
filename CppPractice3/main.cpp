#include "card.h"
#include "game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <locale.h>

using namespace std;

int main() {
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, "ru_RU.UTF-8");

    srand(static_cast<unsigned>(std::time(nullptr)));

    Player player;
    Player dealer;
    initPlayer(player, "Игрок");
    initPlayer(dealer, "Дилер");

    Deck deck;
    initDeck(deck);
    shuffleDeck(deck);

    cout << "=== Блэкджек ===\n";

    do {
        system("cls");
        playRound(player, dealer, deck);
    } while (askPlayAgain());

    cout << "Спасибо за игру!\n";
    return 0;
}