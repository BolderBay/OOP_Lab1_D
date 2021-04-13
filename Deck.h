#include <iostream>
#include "DeckConst.h"
using namespace DeckConst;              // ������������� ������ ������������ ����

struct Card {           // ��������� ��� ������ �����
private:
    int rank;           // �������� �����
    char suit;          // �������� �����
public:
    Card();                         // ����������� �� ��������� ������� "������" �����
    Card(int rank, char suit);      // ����������, ��������� ����� � ������ � ������
    int  getRank() const;           // ������ �����
    char getSuit() const;           // ������ �����
    Card& setRank(int rank);       // ������ �����
    Card& setSuit(char suit);      // ������ �����
    bool operator> (Card sortCard);
    bool operator!= (Card sortCard);
};

class Deck {                        // ����� ������
private:
    Card *list;                     // ������ ������ 
    int  lenght;                    // ������ ������
    void sortRank(int left, int right);
public:
    Deck() : lenght(QUANTITY), list(new Card[lenght]) {
        for (int filler = 0; filler < QUANTITY; ++filler) {
            Card basekard((filler % MAXRANG) + 1, letters[filler % (sizeof(letters) / sizeof(letters[0]))]);
            list[filler] = basekard;
        };
    };
    Deck(int number)              // �����������, ��������� ������ �� number ����, ������������ ��������
    {
        if (number > QUANTITY || number < 0) throw std::exception("Invalid number\n");
        lenght = number; 
        list = new Card[lenght];
        
        srand(time(0)+rand());
        
        Card* randomlist;
        try {randomlist = new Card[QUANTITY];}
        catch (std::bad_alloc err) { delete[] list; throw err; }
        
        for (int filler = 0; filler < QUANTITY; ++filler) {
            Card basekard((filler % MAXRANG) + 1, letters[filler % (sizeof(letters) / sizeof(letters[0]))]);
            randomlist[filler] = basekard;
        };

        for (int cycle = 0; cycle < 4; ++cycle) {
            for (int swapper = 0; swapper < QUANTITY; ++swapper)
            {
                Card buffer;
                int randomPosition = rand() % QUANTITY;
                buffer = randomlist[swapper];
                randomlist[swapper] = randomlist[randomPosition];
                randomlist[randomPosition] = buffer;
            };
        };
        for (int transf = 0; transf < lenght; ++transf) {
            list[transf] = randomlist[transf];
        };
        delete[] randomlist;
    };                     
    Deck(const Card& card) : lenght(1), list(new Card[lenght])                 // �����������, ��������� ������ �� ����� ��������� �����
    {
        list[0] = card;
    };
    Deck(const Deck& deck) {
        lenght = deck.getLenght();
        list = new Card[lenght];
        for (int i = 0; i < lenght; i++)
            list[i] = deck.list[i];
    }
    Deck(Deck&& deck) {
        lenght = deck.lenght;
        list = deck.list;
        deck.list = nullptr;
    }
    char getSuit(int position) const;     // ����� �� ����� ����� �� �� �������
    int getRank(int position) const;      // ������ �� ���� ����� �� �� �������
    int getLenght() const;                // ������ �� ����� ������
    Deck selectSuit(char selectSuit, Deck& newdeck);     // ������� ������ �� �����
    void sort();                          // ����������
    void NewSort();                       // ����� ����������
    Deck& addCard(Card& card);              // ��� ������� ��� ��������� ����� � ������
    Deck& addAnyCard(Card& card);
    friend std::ostream& operator <<(std::ostream& c, const Deck& d);   // ���������� ��������� << ��� ������
    friend std::istream& operator >>(std::istream& c, Deck& d);         // ���������� ��������� >> ��� �����
    Deck& operator++();                                                 // ���������� ��������� ++ ��� ���������� ��������� ����� � ������
    int operator[] (int index) const;                                   // ���������� ��������� [] ��� ��������� ����� ����� � ������� index
    char operator() (int index) const;                                  // ���������� ��������� () ��� ��������� ����� ����� � ������� index
    Card getCard(int index);                                            // �������������� ����� ��������� �����
    void shiftCard();                                                   // �������������� ����� ������ ���� � ������
    Deck& delCard();                                                    // �������������� ����� �������� �����
    ~Deck() 
    {
       delete[] list;
    }
    Deck& operator =(const Deck& d);
    Deck& operator =(Deck&& d);
};

