#ifndef KEEPER_H
#define KEEPER_H

#include "Train.h"
#include <stdexcept>

class Keeper {
private:
    TRAIN** items; // Динамический массив указателей на поезда
    int count;     // Текущее количество элементов
    int capacity;  // Выделенная емкость массива

    void resize();              // Увеличение емкости массива
    void sortByTrainNumber();   // Сортировка записей по возрастанию номера поезда

public:
    // Конструкторы и деструктор
    Keeper();
    explicit Keeper(int initialCapacity);
    Keeper(const Keeper& other);
    ~Keeper();

    // Основные методы управления
    void insertItem(TRAIN* item, int index);
    void removeItem(int index);
    void editItem(int index);
    void clear();

    // Просмотр и поиск данных
    void printAll() const;
    void findByTrainNumber(int number) const;
    TRAIN* getItem(int index) const;
    int getCount() const;

    // Переопределение операторов
    Keeper& operator=(const Keeper& other);
    bool operator==(const Keeper& other) const;
};

#endif