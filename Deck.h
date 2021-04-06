#include <iostream>
#include "DeckConst.h"
using namespace DeckConst;              // Использование своего пространства имен

struct Card {           // Структура для задачи карты
private:
    int rank;           // Значение ранга
    char suit;          // значение масти
public:
    Card();                         // Конструктор по умолчанию создает "пустую" карту
    Card(int rank, char suit);      // Коструктор, создающий карту с рангом и мастью
    int  getRank() const;           // Геттер ранга
    char getSuit() const;           // Геттер масти
    Card& setRank(int rank);       // Сеттер ранга
    Card& setSuit(char suit);      // Сеттер масти
    bool operator> (Card sortCard);
};

class Deck {                        // класс колоды
private:
    Card *list;                     // Массив колоды 
    int  lenght;                    // Длинна колоды
    void sortRank(int left, int right);
public:
    Deck() : lenght(QUANTITY), list(new Card[lenght]) {
        for (int filler = 0; filler < QUANTITY; ++filler) {
            Card basekard((filler % MAXRANG) + 1, letters[filler % (sizeof(letters) / sizeof(letters[0]))]);
            list[filler] = basekard;
        };
    };
    Deck(int number) : lenght(number), list(new Card[lenght])              // Конструктор, создающий колоду из number карт, определяемых случайно
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
    Deck(Card& card) : lenght(1), list(new Card[lenght])                 // Конструктор, создающий колоду из одной указанной карты
    {
        list[0] = card;
    };                      
    char getSuit(int position) const;     // Гттер на масть карты по ее позиции
    int getRank(int position) const;      // Геттер на ранг карты по ее позиции
    int getLenght() const;                // Геттер на длину колоды
    Deck selectSuit(char selectSuit, Deck& newdeck);     // Возврат колоды по масти
    void sort();                          // Сортировка
    void NewSort();                       // Новая сортировка
    Deck& addCard(Card& card);              // Доп функция для доавления карты в колоду  
    friend std::ostream& operator <<(std::ostream& c, const Deck& d);   // Перегрузка оператора << для вывода
    friend std::istream& operator >>(std::istream& c, Deck& d);         // Перегрузка оператора >> для ввода
    Deck& operator++();                                                 // Перегрузка оператора ++ для добавления случайной карты в колоду
    int operator[] (int index) const;                                   // Перегрузка оператора [] для получения масти карты в позиции index
    char operator() (int index) const;                                  // Перегрузка оператора () для получения ранга карты в позиции index
    Card getCard(int index);                                            // Дополнительный метод получения карты
    void shiftCard();                                                   // Дополнительный метод сдвига карт в колоде

    ~Deck() 
    {
        memset(list, 0, sizeof(list));
    }
    Deck& operator +=(Deck& d); // ??????????? ?????? ?? ?????? ??????? ? ??????	
    Deck& operator =(Deck& d); // ??????????? ?????? ?? ?????? ??????? ? ??????
};

