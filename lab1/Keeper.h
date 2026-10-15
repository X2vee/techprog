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
    Base** items;    // Массив указателей на базовый класс
    int count;       // Текущее количество элементов
    int capacity;    // Выделенная емкость массива

    void resize();   // Вспомогательный метод для увеличения массива

public:
    // --- Конструкторы и деструктор ---
    Keeper();
    Keeper(const Keeper& other);
    ~Keeper();

    // --- Основные методы управления ---
    void addItem(Base* item); // Добавляет объект (Keeper забирает владение указателем)
    void removeItem(int index);
    void clear(); // Полная очистка контейнера

    // --- Просмотр данных ---
    void printAll() const;
    Base* getItem(int index) const;
    int getCount() const;

    // --- Работа с файлами ---
    void saveToFile(const char* filename) const;
    void loadFromFile(const char* filename);

    // --- Переопределение операторов (требование методички) ---
    Keeper& operator=(const Keeper& other);
    bool operator==(const Keeper& other) const; // Сравнение по количеству элементов
};

#endif // KEEPER_H