#include "Deck.h"
#include <iostream>
#include <iomanip>

void printCards(Deck cards) {                       //функция вывода карт в колоде
	for (int j = 0; j < cards.getLenght(); j++) {
		std::cout << j + 1 << ") " << cards.getRank(j) << " " << cards.getSuit(j) << "\n";
	};
};
void printCardsLine(Deck cards) {                   //функция вывода карт в колоде в линию
	for (int j = 0; j < cards.getLenght(); j++) {
		std::cout << std::setw(2) << cards.getSuit(j) << " ";
	};
	std::cout << '\n';
	for (int j = 0; j < cards.getLenght(); j++) {
		std::cout << std::setw(2) << cards.getRank(j) << " ";
	};
	std::cout << '\n';
};



int main()
{
	Deck newDeck();
}

