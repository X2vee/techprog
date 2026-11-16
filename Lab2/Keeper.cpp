#include "Keeper.h"
#include <iostream>

// Конструкторы и деструктор

Keeper::Keeper() : items(nullptr), count(0), capacity(0) {
    std::cout << "[Keeper] Вызван конструктор по умолчанию" << std::endl;
}

Keeper::Keeper(int initialCapacity) : items(nullptr), count(0), capacity(0) {
    std::cout << "[Keeper] Вызван конструктор с параметрами" << std::endl;
    if (initialCapacity <= 0) {
        throw std::invalid_argument("Ошибка: начальная емкость контейнера должна быть больше нуля!");
    }
    capacity = initialCapacity;
    items = new TRAIN * [capacity];
}

Keeper::Keeper(const Keeper& other) : items(nullptr), count(0), capacity(0) {
    std::cout << "[Keeper] Вызван конструктор копирования" << std::endl;
    for (int i = 0; i < other.count; ++i) {
        insertItem(new TRAIN(*other.items[i]), count);
    }
}

Keeper::~Keeper() {
    std::cout << "[Keeper] Вызван деструктор" << std::endl;
    clear();
}

// Вспомогательные методы

void Keeper::resize() {
    if (count >= capacity) {
        capacity = (capacity == 0) ? 2 : capacity * 2;
        TRAIN** newItems = new TRAIN * [capacity];
        for (int i = 0; i < count; ++i) {
            newItems[i] = items[i];
        }
        delete[] items;
        items = newItems;
    }
}

void Keeper::sortByTrainNumber() {
    for (int i = 1; i < count; ++i) {
        TRAIN* key = items[i];
        int j = i - 1;
        while (j >= 0 && items[j]->getTrainNumber() > key->getTrainNumber()) {
            items[j + 1] = items[j];
            --j;
        }
        items[j + 1] = key;
    }
}

void Keeper::clear() {
    for (int i = 0; i < count; ++i) {
        delete items[i];
    }
    delete[] items;
    items = nullptr;
    count = 0;
    capacity = 0;
}

// Методы управления

void Keeper::insertItem(TRAIN* item, int index) {
    if (!item) {
        throw std::invalid_argument("Ошибка: попытка добавить пустой указатель!");
    }
    if (index < 0 || index > count) {
        delete item;
        throw std::out_of_range("Ошибка: позиция вставки вне допустимого диапазона!");
    }

    resize();
    for (int i = count; i > index; --i) {
        items[i] = items[i - 1];
    }
    items[index] = item;
    count++;

    // Упорядочивание по возрастанию номеров поездов согласно варианту
    sortByTrainNumber();
}

void Keeper::removeItem(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Ошибка: индекс элемента вне диапазона!");
    }
    delete items[index];
    for (int i = index; i < count - 1; ++i) {
        items[i] = items[i + 1];
    }
    count--;
}

void Keeper::editItem(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Ошибка: индекс элемента вне диапазона!");
    }
    std::cout << "\n=== Редактирование записи о поезде ===" << std::endl;
    TRAIN updated;
    std::cin >> updated;
    *items[index] = updated;
    sortByTrainNumber();
}

void Keeper::printAll() const {
    if (count == 0) {
        std::cout << "\nРасписание поездов пусто." << std::endl;
        return;
    }
    std::cout << "\n=== Расписание поездов (" << count << " шт., упорядочено по номеру) ===" << std::endl;
    for (int i = 0; i < count; ++i) {
        std::cout << "[" << (i + 1) << "] " << *items[i] << std::endl;
    }
}

void Keeper::findByTrainNumber(int number) const {
    if (number <= 0) {
        throw std::invalid_argument("Ошибка: номер искомого поезда должен быть положительным!");
    }
    if (count == 0) {
        std::cout << "\nРасписание поездов пусто." << std::endl;
        return;
    }

    bool found = false;
    for (int i = 0; i < count; ++i) {
        if (items[i]->getTrainNumber() == number) {
            if (!found) {
                std::cout << "\n--- Найденные поезда ---" << std::endl;
            }
            std::cout << *items[i] << std::endl;
            found = true;
        }
    }

    if (!found) {
        std::cout << "\nПоезд с номером " << number << " не найден." << std::endl;
    }
}

TRAIN* Keeper::getItem(int index) const {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Ошибка: индекс элемента вне диапазона!");
    }
    return items[index];
}

int Keeper::getCount() const {
    return count;
}

// Переопределение операторов

Keeper& Keeper::operator=(const Keeper& other) {
    if (this != &other) {
        clear();
        for (int i = 0; i < other.count; ++i) {
            insertItem(new TRAIN(*other.items[i]), count);
        }
    }
    return *this;
}

bool Keeper::operator==(const Keeper& other) const {
    return count == other.count;
}