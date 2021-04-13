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
	srand(time(0));
	int game = 0;
	int mysumm = 0;
	int oppsumm = 0;
	int countCard = 10;

	Deck myDeck(countCard);
	Deck opponentDeck(countCard);

	Card getterCard;

	unsigned int myWins = 0;
	unsigned int opponentWins = 0;
	unsigned int winsCount = 3;

	int myRand = 0;
	int opponentRand = 0;
	int counter = 1;

	std::cout << "Choose a game\n";
	std::cout << "1 - Draw a random card\n";
	std::cout << "2 - Drunkard\n";
	std::cout << "3 - Summ\n";
	std::cin >> game;
	
	switch (game)
	{
	case 1:
		srand(time(0));
		while (myWins != winsCount && opponentWins != winsCount)
		{
			std::cout << "Turn " << counter << ": ";
			myRand = rand() % (countCard / 2);
			opponentRand = rand() % (countCard / 2);

			if (myDeck.getCard(myRand) > opponentDeck.getCard(opponentRand)) {
				myWins++;
				std::cout << "Your card (" << myDeck.getCard(myRand).getSuit() << " " << myDeck.getCard(myRand).getRank() << ") is larger than your opponent's (" <<
					opponentDeck.getCard(myRand).getSuit() << " " << opponentDeck.getCard(myRand).getRank() << ")\n";
			}
			else {
				opponentWins++;
				std::cout << "Your card (" << myDeck.getCard(myRand).getSuit() << " " << myDeck.getCard(myRand).getRank() << ") is smaller than your opponent's (" <<
					opponentDeck.getCard(myRand).getSuit() << " " << opponentDeck.getCard(myRand).getRank() << ")\n";
			};
			counter++;
		}

		if (myWins > opponentWins) std::cout << "You wins!" << std::endl;
		else std::cout << "You lose!" << std::endl;
		break;

	case 2:
		while (myDeck.getLenght() != 0 && opponentDeck.getLenght() != 0) {
			if (myDeck.getCard(0) > opponentDeck.getCard(0)) {
				Card opCard = opponentDeck.getCard(0);
				myDeck.addAnyCard(opCard);
				opponentDeck.delCard();
				std::cout << counter << ") "<<"Your card is bigger\n";
			}
			else {
				if (opponentDeck.getCard(0) > myDeck.getCard(0) and myDeck.getCard(0) != opponentDeck.getCard(0)) {
					Card myCard = myDeck.getCard(0);
					opponentDeck.addAnyCard(myCard);
					myDeck.delCard();
					std::cout << counter << ") " << "Opponents card is bigger\n";
				}
			}
			myDeck.shiftCard();
			opponentDeck.shiftCard();
			counter++;
		}
		if (myDeck.getLenght() == 0) std::cout << "You lose\n";
		else std::cout << "You win\n";
		break;
	case 3:
		for (int summer = 0; summer < myDeck.getLenght(); ++summer) {
			mysumm = mysumm + myDeck.getRank(summer);
			oppsumm = oppsumm + opponentDeck.getRank(summer);
		}
		if (mysumm > oppsumm) std::cout << "Your summ is bigger\n";
		else if (oppsumm > mysumm) std::cout << "Opponents summ is bigger\n";
		else std::cout << "Same summ\n";
		break;
	default:
		std::cout << "There is no such game!";
		break;
	}
}

