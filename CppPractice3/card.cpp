#include "card.h"
#include <cstdlib>

extern const int MAX_SCORE = 21;

void initDeck(Deck& deck) {
    int idx = 0;
    for (int r = 6; r <= 14; ++r) {
        for (int s = 0; s < 4; ++s) {
            Card c;
            c.suit = static_cast<Suit>(s);
            c.rank = static_cast<Rank>(r);
            if (r <= 10)                       c.points = r;
            else if (r >= 11 && r <= 13)       c.points = 10;
            else                               c.points = 11;
            deck.cards[idx++] = c;
        }
    }
    deck.topIndex = 0;
}

void shuffleDeck(Deck& deck) {
    for (int i = DECK_SIZE - 1; i > 0; --i) {
        int j = std::rand() % (i + 1);
        Card tmp = deck.cards[i];
        deck.cards[i] = deck.cards[j];
        deck.cards[j] = tmp;
    }
    deck.topIndex = 0;
}

Card dealCard(Deck& deck) {
    if (deck.topIndex >= DECK_SIZE)
        shuffleDeck(deck);
    if (deck.topIndex >= DECK_SIZE)
        deck.topIndex = 0;
    return deck.cards[deck.topIndex++];
}

void initPlayer(Player& player, const char* name) {
    int i = 0;
    while (i < static_cast<int>(sizeof(player.name)) - 1 && name[i] != '\0') {
        player.name[i] = name[i];
        ++i;
    }
    player.name[i] = '\0';
    player.cardCount = 0;
    player.score = 0;
}

void resetPlayer(Player& player) {
    player.cardCount = 0;
    player.score = 0;
}

void addCardToHand(Player& player, Card card) {
    if (player.cardCount < MAX_HAND) {
        player.hand[player.cardCount++] = card;
        player.score += card.points;
    }
}

const char* suitName(Suit suit) {
    switch (suit) {
    case Suit::Spades:   return "Spades";
    case Suit::Clubs:    return "Clubs";
    case Suit::Diamonds: return "Diamonds";
    case Suit::Hearts:   return "Hearts";
    }
    return "?";
}

const char* rankName(Rank rank) {
    switch (rank) {
    case Rank::Six:   return "Six";
    case Rank::Seven: return "Seven";
    case Rank::Eight: return "Eight";
    case Rank::Nine:  return "Nine";
    case Rank::Ten:   return "Ten";
    case Rank::Jack:  return "Jack";
    case Rank::Queen: return "Queen";
    case Rank::King:  return "King";
    case Rank::Ace:   return "Ace";
    }
    return "?";
}