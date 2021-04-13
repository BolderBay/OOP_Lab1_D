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
    bool operator!= (Card sortCard);
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
    Deck(int number)              // Конструктор, создающий колоду из number карт, определяемых случайно
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
    Deck(const Card& card) : lenght(1), list(new Card[lenght])                 // Конструктор, создающий колоду из одной указанной карты
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
    char getSuit(int position) const;     // Гттер на масть карты по ее позиции
    int getRank(int position) const;      // Геттер на ранг карты по ее позиции
    int getLenght() const;                // Геттер на длину колоды
    Deck selectSuit(char selectSuit, Deck& newdeck);     // Возврат колоды по масти
    void sort();                          // Сортировка
    void NewSort();                       // Новая сортировка
    Deck& addCard(Card& card);              // Доп функция для доавления карты в колоду
    Deck& addAnyCard(Card& card);
    friend std::ostream& operator <<(std::ostream& c, const Deck& d);   // Перегрузка оператора << для вывода
    friend std::istream& operator >>(std::istream& c, Deck& d);         // Перегрузка оператора >> для ввода
    Deck& operator++();                                                 // Перегрузка оператора ++ для добавления случайной карты в колоду
    int operator[] (int index) const;                                   // Перегрузка оператора [] для получения масти карты в позиции index
    char operator() (int index) const;                                  // Перегрузка оператора () для получения ранга карты в позиции index
    Card getCard(int index);                                            // Дополнительный метод получения карты
    void shiftCard();                                                   // Дополнительный метод сдвига карт в колоде
    Deck& delCard();                                                    // Дополнительный метод удаления карты
    ~Deck() 
    {
       delete[] list;
    }
    Deck& operator =(const Deck& d);
    Deck& operator =(Deck&& d);
};

