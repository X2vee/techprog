#ifndef KEEPER_H
#define KEEPER_H

#include "Base.h"
#include "Airplane.h"
#include "Train.h"
#include "Car.h"
#include <fstream>
#include <stdexcept>

class Keeper {
private:
    Base** items; 
    int count; // Текущее количество элементов
    int capacity; // Выделенная емкость массива

    void resize(); // Вспомогательный метод для увеличения массива

public:
    // Конструкторы и деструктор
    Keeper();
    Keeper(const Keeper& other);
    ~Keeper();

    // Основные методы управления
    void addItem(Base* item); 
    void removeItem(int index);
    void clear(); 

    // Просмотр данных
    void printAll() const;
    Base* getItem(int index) const;
    int getCount() const;

    // Работа с файлами
    void saveToFile(const char* filename) const;
    void loadFromFile(const char* filename);

    // Переопределение операторов 
    Keeper& operator=(const Keeper& other);
    bool operator==(const Keeper& other) const; 
};

#endif