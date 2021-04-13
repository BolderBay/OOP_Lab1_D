#include "pch.h"
#include "Deck.h"
#include <strstream>
#include <stdio.h>

Card::Card()              // ����������� �� ��������� ������� ����� ������������ ����� ������ �������� �����
{
	rank = MINRANG;
	suit = letters[0];
};
Card::Card(int rank, char suit)         // ����������, ��������� ����� � ������ � ������
{
	bool StandFlag = false;
	for (int searcher = 0; searcher < sizeof(letters) / sizeof(letters[0]); ++searcher) {
		if (letters[searcher] == suit) {
			StandFlag = true;
			break;
		}
	}
	if (rank < MINRANG || rank > MAXRANG && StandFlag == false) throw std::exception("Invalid rang and suit\n");
	if (rank < MINRANG || rank > MAXRANG) throw std::exception("Invalid rang\n");         // ����������� �� ���� [MINRANG, MAXRANG] � �� ����� 
	if (StandFlag == false) throw std::exception("Invalid suit\n");
	Card::rank = rank;
	Card::suit = suit;

};
int Card::getRank() const { return rank; };
char Card::getSuit() const { return suit; };
Card& Card::setRank(int rank) {
	if (rank < MINRANG || rank > MAXRANG) throw std::exception("Invalid rang\n");          // ����������� �� ���� [MINRANG, MAXRANG]
	else {
		Card::rank = rank;
		Card::suit = suit;
		return *this;
	}
};
Card& Card::setSuit(char suit) {
	bool StandFlag = false;

	for (int searcher = 0; searcher < sizeof(letters) / sizeof(letters[0]); ++searcher) {
		if (letters[searcher] == suit) {
			StandFlag = true;
			break;
		}
	}
	if (StandFlag == false) throw std::exception("Invalid suit\n");          // ����������� �� ����� 
	Card::rank = rank;
	Card::suit = suit;
	return *this;
};

bool Card::operator> (Card sortCard)
{
	int suit1pos = 0;
	int suit2pos = 0;
	for (int i = 0; i < sizeof(letters); i++)
	{
		if (letters[i] == suit) suit1pos = i;
		if (letters[i] == sortCard.getSuit()) suit2pos = i;
	}
	if (suit1pos > suit2pos) return false;
	if (suit1pos < suit2pos) return true;
	if (suit1pos == suit2pos && rank > sortCard.getRank()) return true;
	if (suit1pos == suit2pos && rank < sortCard.getRank()) return false;
}
bool Card::operator!= (Card sortCard) {
	if (suit == sortCard.suit && rank == sortCard.rank) return false;
	else return true;
}

Deck& Deck::operator++()                  // ���������� ��������� ++ ��� ���������� ��������� ����� � ������
{
	srand(time(0));
	if (lenght >= QUANTITY) throw std::exception("The deck is full\n");  // ����������� �� ������ ������
	Card additionCard;
	bool FindingFlag = true;
	while (FindingFlag == true) {
		FindingFlag = false;
		additionCard.setRank((rand() % MAXRANG) + 1);
		additionCard.setSuit(letters[rand() % (sizeof(letters) / sizeof(letters[0]))]);
		for (int i = 0; i < lenght; i++)
			if (list[i].getRank() == additionCard.getRank() && list[i].getSuit() == additionCard.getSuit()) FindingFlag = true;
	}
	addCard(additionCard);
	return *this;
};

char Deck::getSuit(int position) const {
	if (position > lenght) throw std::exception("Incorrect position\n");
	return list[position].getSuit();
};
int Deck::getRank(int position) const {
	if (position > lenght) throw std::exception("Incorrect position\n");
	return list[position].getRank();
};
int Deck::getLenght() const { return lenght; };

void Deck::NewSort() {
	Card buffer;
	for (int i = 0; i < lenght; i++) {
		for (int j = 0; j < lenght - 1; j++) {
			if (list[j + 1] > list[j]) {
				buffer = list[j + 1];
				list[j + 1] = list[j];
				list[j] = buffer;
			}
		}
	}
}

Deck Deck::selectSuit(char selectSuit, Deck& newdeck) {
	bool StandFlag = false;
	for (int searcher = 0; searcher < sizeof(letters) / sizeof(letters[0]); ++searcher) {
		if (letters[searcher] == selectSuit) {
			StandFlag = true;
			break;
		}
	}
	if (StandFlag == false) throw std::exception("Invalid suit\n");

	for (int position = 0; position < lenght; ++position) {
		if (list[position].getSuit() == selectSuit)
			newdeck.addCard(list[position]);
	};

	return 0;
};

Deck& Deck::addCard(Card& card) {
	Card additionCard(card.getRank(), card.getSuit());
	bool FindingFlag = false;
	if (lenght >= QUANTITY) throw std::exception("The deck is full\n");
	for (int seacher = 0; seacher < lenght; ++seacher) {
		if (list[seacher].getRank() == card.getRank() && list[seacher].getSuit() == card.getSuit()) {
			FindingFlag = true;
			break;
		}
	}
	if (FindingFlag == true) throw std::exception("This card is already in the deck\n");

	Card* randomlist = new Card[lenght+1];
	for (int i = 0; i < lenght; ++i) randomlist[i] = list[i];
	randomlist[lenght+1] = additionCard;
	delete[] list;
	list = randomlist;
	lenght = lenght + 1;
	return *this;
};

Deck& Deck::addAnyCard(Card& card) {
	Card additionCard(card.getRank(), card.getSuit());
	if (lenght >= QUANTITY) throw std::exception("The deck is full\n");
	Card* randomlist = new Card[lenght + 1];
	for (int i = 0; i < lenght; ++i) randomlist[i] = list[i];
	randomlist[lenght + 1] = additionCard;
	delete[] list;
	list = randomlist;
	lenght = lenght + 1;
	return *this;
};

std::ostream& operator <<(std::ostream& c, const Deck& d) // ���������� ��������� << ��� ������ �������
{
	int outputCount = 0;
	while (d.getRank(outputCount) != 0 && outputCount < d.getLenght()) {
		c << " ____\n";
		c << "|" << d.getRank(outputCount) << "  |\n";
		if (d.getRank(outputCount) > 9)
			c << "| " << d.getSuit(outputCount) << "  |\n";
		else
			c << "| " << d.getSuit(outputCount) << " |\n";
		c << "|__" << d.getRank(outputCount) << "|\n";
		outputCount++;
	};
	return c;
};
std::istream& operator >>(std::istream& c, Deck& d)
{
	int rangInput;
	char suitInput;
	int counter;

	c >> counter;
	if (counter > QUANTITY - d.getLenght()) throw std::exception("Incorrect quantity\n");
	for (int inputer = 0; inputer < counter; ++inputer) {
		c >> rangInput >> suitInput;
		try {
			Card imputCard(rangInput, suitInput);
			d.addCard(imputCard);
		}
		catch (std::exception& error) {
			c.setstate(std::ios::failbit);
			return c;
		}
	}
	return c;
};
int Deck::operator[] (int index) const {
	if (index > lenght) throw std::exception("Incorrect position\n");
	return list[index].getRank();
}
char Deck::operator() (int index) const {
	if (index > lenght) throw std::exception("Incorrect position\n");
	return list[index].getSuit();

}

Card Deck::getCard(int index) {
	if (index > lenght) throw std::exception("Incorrect position\n");
	return list[index];
}

Deck& Deck::operator =(const Deck& d) {
	if (this != &d)
	{
		delete[] list;
		lenght = d.getLenght();
		Card* list = new Card [lenght];
		for (int i = 0; i < lenght; i++)
			list[i] = d.list[i];
	}
	return *this;
}

Deck& Deck::operator =(Deck&& d) {
	if (this != &d) {
		delete[] list;
		list = d.list;
		lenght = d.lenght;
		d.list = nullptr;
	}
	return *this;
}

void Deck::shiftCard() {
	if (lenght == 0) throw std::exception("Zero length");
	Card tmp1;
	tmp1 = list[0];
	for (int i = 0; i < lenght - 1; i++)
		list[i] = list[i + 1];
	list[lenght - 1] = tmp1;
}

Deck& Deck::delCard() {
	if (lenght == 0) throw std::exception("Zero length");
	shiftCard();
	Card* randomlist = new Card[lenght - 1];
	for (int i = 0; i < lenght-1; ++i) randomlist[i] = list[i];
	delete[] list;
	list = randomlist;
	lenght--;
	return *this;
}
