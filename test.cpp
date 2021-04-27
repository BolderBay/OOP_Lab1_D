#include "pch.h"
#include "gtest\\gtest.h"
#include "C:\Users\���������\source\repos\LaboratoryWork1-D\Deck.h"

#include <iostream>
#include <string>
#include <fstream> 

TEST(DeckConstructor, DefaultConstructor)
{
	bool uniqFlag = true;
	Deck testdeck;
	ASSERT_EQ(QUANTITY, testdeck.getLenght());
	for (int count = 0; count < testdeck.getLenght(); ++count) {
		ASSERT_EQ((count % MAXRANG)+1, testdeck.getRank(count));
		ASSERT_EQ(letters[count % (sizeof(letters) / sizeof(letters[0]))], testdeck.getSuit(count));
	}
	for (int count = 0; count < testdeck.getLenght(); ++count) {			// �������������
		for (int compare = count; compare < testdeck.getLenght(); ++compare) {
			if (testdeck.getSuit(count) == testdeck.getSuit(compare) && testdeck.getRank(count) == testdeck.getRank(compare) && count != compare) uniqFlag = false;
		}
	}
	ASSERT_EQ(true, uniqFlag);
}

TEST(DeckConstructor, InitConstructors_1) //�������� �������� n
{
	int n = 5;
	bool uniqFlag = true;
	Deck testdeck(5);
	ASSERT_EQ(n, testdeck.getLenght());
	for (int count = 0; count < testdeck.getLenght(); ++count) {
		for (int compare = count; compare < testdeck.getLenght(); ++compare) {
			if (testdeck.getSuit(count) == testdeck.getSuit(compare) && testdeck.getRank(count) == testdeck.getRank(compare) && count != compare) uniqFlag = false;
		}
	}
	ASSERT_EQ(true, uniqFlag);

}

TEST(DeckConstructor, InitConstructors_2)
{
	Card testcard(2, 'd');
	Deck deck1(testcard);
	ASSERT_EQ(1, deck1.getLenght());
	ASSERT_EQ(2, deck1.getRank(0));
	ASSERT_EQ('d', deck1.getSuit(0));

}

TEST(DeckConstructor, InitConstructors_3)
{
	bool identicalFlag = true;
	bool uniqFlag = true;
	int n = 5;
	Deck checkDesk(n);
	Deck testdeck(checkDesk);
	ASSERT_EQ(n, testdeck.getLenght());
	for(int count = 0; count < testdeck.getLenght(); ++count) {
		if (testdeck.getRank(count) != checkDesk.getRank(count) || testdeck.getSuit(count) != checkDesk.getSuit(count)) identicalFlag = false;
	}
	ASSERT_EQ(true, identicalFlag);									// �������������
	for (int count = 0; count < testdeck.getLenght(); ++count) {			
		for (int compare = count; compare < testdeck.getLenght(); ++compare) {
			if (testdeck.getSuit(count) == testdeck.getSuit(compare) && testdeck.getRank(count) == testdeck.getRank(compare) && count != compare) uniqFlag = false;
		}
	}
	ASSERT_EQ(true, uniqFlag);
}

TEST(DeckMethods, TestException)
{
	Card h(1, 'h');
	Deck testdeck(h);
	Deck zerodeck(0);
	Deck fulldeck(QUANTITY);
	ASSERT_THROW(testdeck.getRank(-1), std::exception);
	ASSERT_THROW(testdeck.getRank(2), std::exception);
	ASSERT_THROW(testdeck.getSuit(-1), std::exception);
	ASSERT_THROW(testdeck.getSuit(2), std::exception);
	ASSERT_THROW(testdeck.getCard(-1), std::exception);
	ASSERT_THROW(testdeck.getCard(2), std::exception);
	ASSERT_THROW(testdeck.addCard(h), std::exception);
	ASSERT_THROW(zerodeck.delCard(), std::exception);
	ASSERT_THROW(fulldeck.addCard(h), std::exception);
	ASSERT_THROW(fulldeck.selectSuit('j',zerodeck), std::exception);
	ASSERT_THROW(testdeck[-1], std::exception);
	ASSERT_THROW(testdeck[2], std::exception);
	ASSERT_THROW(testdeck(-1), std::exception);
	ASSERT_THROW(testdeck(2), std::exception);
}

TEST(DeckMethods, TestMethods)
{
	bool findingFlag = false;
	bool cardFlag = false;
	bool positionFlag = true;
	Deck simpleDeck;
	Deck onecardDeck(0);
	Deck selectsuitDeck(0);
	Deck sortDeck(10);

	simpleDeck.delCard();			// ��������� ������������ �����
	ASSERT_EQ(QUANTITY - 1, simpleDeck.getLenght());
	for (int count = 0; count < simpleDeck.getLenght(); ++count) {
		if (simpleDeck.getRank(count) == QUANTITY % MAXRANG && simpleDeck.getSuit(count) == QUANTITY % (sizeof(letters) / sizeof(letters[0]))) findingFlag = true;
	}
	ASSERT_EQ(false, findingFlag);


	Card h(1, 'h');
	onecardDeck.addCard(h);
	ASSERT_EQ(1, onecardDeck.getLenght());
	if (onecardDeck.getRank(0) == 1 && onecardDeck.getSuit(0) == 'h') cardFlag = true;
	ASSERT_EQ(true, cardFlag);


	char let = 'h';
	int suitcount = 0;
	simpleDeck.selectSuit(let, selectsuitDeck);
	for (int count = 0; count < selectsuitDeck.getLenght(); ++count) {
		ASSERT_EQ(let, selectsuitDeck.getSuit(count));
	}
	for (int count = 0; count < simpleDeck.getLenght(); ++count) if (simpleDeck.getSuit(count) == let) suitcount++;
	ASSERT_EQ(suitcount, selectsuitDeck.getLenght());


	sortDeck.NewSort();
	for (int count = 0; count < sortDeck.getLenght()-1; ++count) {
		if (sortDeck.getCard(count + 1) > sortDeck.getCard(count)) positionFlag = false;
	}
	ASSERT_EQ(true, positionFlag);
}

TEST(DeckMethods, TestImputMethods) // ��� �����-�� �����, �������� ������, ����� ����� � �� ����
{
	Deck testdeck(0);
	int countcards = 3;
	bool checkFlag = true;
	Card cards[]{ Card(1,'h'), Card(2,'h'), Card(3,'h') };

	std::ofstream out;          
	out.open("cards.txt"); 
	if (out.is_open())
	{
		out << countcards << std::endl;
		for (int i = 0; i < countcards; ++i) {
			out << cards[i].getRank()<< " " << cards[i].getSuit() << std::endl;
		}
	}
	out.close();
	
	std::string str;
	std::ifstream filecards("cards.txt");
	filecards >> testdeck;
	filecards.close();

	ASSERT_EQ(countcards, testdeck.getLenght());
	for (int count = 0; count < testdeck.getLenght(); ++count) {
		if (testdeck.getRank(count) == cards[count].getRank()) checkFlag = true;
	}
	ASSERT_EQ(true, checkFlag);
}

TEST(DeckMethods, TestAddCards) 
{
	Deck zeroDeck(0);
	Deck fullDeck;
	Deck testDeck(0);
	Card h1(1, 'h');
	int n = 5;

	Deck* adress = &zeroDeck;
	zeroDeck.addCard(h1);
	ASSERT_EQ(adress, &zeroDeck);
	ASSERT_EQ(1, zeroDeck.getLenght());
	ASSERT_EQ(1, zeroDeck.getRank(0));
	ASSERT_EQ('h', zeroDeck.getSuit(0));


	for (int adder = 0; adder < n; ++adder) {
		testDeck.addCard(Card(adder+1, letters[adder % (sizeof(letters) / sizeof(letters[0]))]));
	}

	ASSERT_EQ(n, testDeck.getLenght());
	for (int checker = 0; checker < n; ++checker) {
		ASSERT_EQ(checker + 1, testDeck.getRank(checker));
		ASSERT_EQ(letters[checker % (sizeof(letters) / sizeof(letters[0]))], testDeck.getSuit(checker));
	}
	
	ASSERT_THROW(zeroDeck.addCard(h1), std::exception);
	ASSERT_THROW(fullDeck.addCard(h1), std::exception);





}