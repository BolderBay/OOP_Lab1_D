#include "pch.h"
#include "gtest\\gtest.h"
#include "C:\Users\Александр\source\repos\LaboratoryWork1-D\Deck.h"

TEST(DeckConstructor, DefaultConstructor)
{
	Deck testdeck;
	ASSERT_EQ(QUANTITY, testdeck.getLenght());
	ASSERT_EQ(1, testdeck.getRank(0));
	ASSERT_EQ('h', testdeck.getSuit(0));
}

TEST(DeckConstructor, InitConstructors_1)
{
	int n = 5;
	Deck deck1(n);
	ASSERT_EQ(n, deck1.getLenght());
}

TEST(DeckConstructor, InitConstructors_2)
{
	Card testcard(2, 'd');
	Deck deck1(testcard);
	ASSERT_EQ(1, deck1.getLenght());
	ASSERT_EQ(2, deck1.getRank(0));
	ASSERT_EQ('d', deck1.getSuit(0));
}

TEST(Mass_wordConstructor, TestException)
{
	Card h(1, 'h');
	Deck testdeck(h);
	Deck zerodeck(0);
	ASSERT_ANY_THROW(Deck newtestdeck(-1));
	ASSERT_ANY_THROW(testdeck.getCard(-1));
	ASSERT_ANY_THROW(testdeck.addCard(h));
	ASSERT_ANY_THROW(zerodeck.delCard());

}