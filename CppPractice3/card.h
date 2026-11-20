#ifndef CARD_H
#define CARD_H

enum class Suit { Spades, Clubs, Diamonds, Hearts };
enum class Rank {
    Six = 6, Seven, Eight, Nine, Ten,
    Jack, Queen, King, Ace
};

struct Card {
    Suit suit;
    Rank rank;
    int points;
};

const int DECK_SIZE = 36;
const int MAX_HAND = 20;

struct Deck {
    Card cards[DECK_SIZE];
    int topIndex;
};

struct Player {
    char name[32];
    Card hand[MAX_HAND];
    int cardCount;
    int score;
};

extern const int MAX_SCORE;

void initDeck(Deck& deck);
void shuffleDeck(Deck& deck);
Card dealCard(Deck& deck);

void initPlayer(Player& player, const char* name);
void resetPlayer(Player& player);
void addCardToHand(Player& player, Card card);

const char* suitName(Suit suit);
const char* rankName(Rank rank);

#endif