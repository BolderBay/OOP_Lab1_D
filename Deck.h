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
    Deck(int number) : lenght(number), list(new Card[lenght])              // �����������, ��������� ������ �� number ����, ������������ ��������
    {
        srand(time(0));
        Card* randomlist = new Card[QUANTITY];
        if (number > QUANTITY || number < 0) throw std::exception("Invalid number\n");
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
        memset(randomlist, 0, sizeof(randomlist));
    };                     
    Deck(Card& card) : lenght(1), list(new Card[lenght])                 // �����������, ��������� ������ �� ����� ��������� �����
    {
        list[0] = card;
    };                      
    char getSuit(int position) const;     // ����� �� ����� ����� �� �� �������
    int getRank(int position) const;      // ������ �� ���� ����� �� �� �������
    int getLenght() const;                // ������ �� ����� ������
    Deck selectSuit(char selectSuit, Deck& newdeck);     // ������� ������ �� �����
    void sort();                          // ����������
    void NewSort();                       // ����� ����������
    Deck& addCard(Card& card);              // ��� ������� ��� ��������� ����� � ������  
    friend std::ostream& operator <<(std::ostream& c, const Deck& d);   // ���������� ��������� << ��� ������
    friend std::istream& operator >>(std::istream& c, Deck& d);         // ���������� ��������� >> ��� �����
    Deck& operator++();                                                 // ���������� ��������� ++ ��� ���������� ��������� ����� � ������
    int operator[] (int index) const;                                   // ���������� ��������� [] ��� ��������� ����� ����� � ������� index
    char operator() (int index) const;                                  // ���������� ��������� () ��� ��������� ����� ����� � ������� index
    Card getCard(int index);                                            // �������������� ����� ��������� �����
    void shiftCard();                                                   // �������������� ����� ������ ���� � ������

    ~Deck() 
    {
        memset(list, 0, sizeof(list));
    }
    Deck& operator +=(Deck& d); // ??????????? ?????? ?? ?????? ??????? ? ??????	
    Deck& operator =(Deck& d); // ??????????? ?????? ?? ?????? ??????? ? ??????
};

