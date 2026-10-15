#include "Train.h"
#include <cstring>
#include <stdexcept>

#pragma warning(disable: 4996)

// Конструкторы

Train::Train() : Base(), year(0), route(nullptr), wagonsCount(0) {
    std::cout << "[Train] Вызван конструктор по умолчанию" << std::endl;
}

Train::Train(const char* name, double cargoVolume, int newYear,
    const char* newRoute, int newWagonsCount)
    : Base(name, cargoVolume), year(0), route(nullptr), wagonsCount(0) {
    std::cout << "[Train] Вызван конструктор с параметрами" << std::endl;
    setYear(newYear);
    setRoute(newRoute);
    setWagonsCount(newWagonsCount);
}

Train::Train(const Train& other)
    : Base(other), year(0), route(nullptr), wagonsCount(0) {
    std::cout << "[Train] Вызван конструктор копирования" << std::endl;
    year = other.year;
    wagonsCount = other.wagonsCount;

    if (other.route) {
        route = new char[strlen(other.route) + 1];
        std::strcpy(route, other.route);
    }
}

// Деструктор 

Train::~Train() {
    std::cout << "[Train] Вызван деструктор" << std::endl;
    delete[] route;
}

// Переопределение виртуальных функций

void Train::input() {
    std::cout << "\n=== Ввод данных о поезде ===" << std::endl;

    char buffer[256];

    // Ввод наименования
    std::cout << "Наименование: ";
    std::cin.ignore();
    std::cin.getline(buffer, 256);
    setName(buffer);

    // Ввод объёма груза
    double volume;
    std::cout << "Объём перевозимого груза (тонн): ";
    std::cin >> volume;
    setCargoVolume(volume);

    // Ввод года выпуска
    int y;
    std::cout << "Год выпуска: ";
    std::cin >> y;
    setYear(y);

    // Ввод маршрута
    std::cout << "Маршрут (например, Москва - Санкт-Петербург): ";
    std::cin.ignore();
    std::cin.getline(buffer, 256);
    setRoute(buffer);

    // Ввод количества вагонов
    int w;
    std::cout << "Количество вагонов: ";
    std::cin >> w;
    setWagonsCount(w);
}

void Train::print() const {
    std::cout << "\n--- Поезд ---" << std::endl;
    std::cout << "Наименование: " << getName() << std::endl;
    std::cout << "Объём груза: " << getCargoVolume() << " т" << std::endl;
    std::cout << "Год выпуска: " << year << std::endl;
    std::cout << "Маршрут: " << (route ? route : "Не указан") << std::endl;
    std::cout << "Количество вагонов: " << wagonsCount << std::endl;
}

Base* Train::clone() const {
    return new Train(*this);
}

const char* Train::getType() const {
    return "Поезд";
}

// Геттеры и сеттеры

int Train::getYear() const {
    return year;
}

void Train::setYear(int newYear) {
    if (newYear < 1800 || newYear > 2026) {
        throw std::invalid_argument("Ошибка: Некорректный год выпуска поезда!");
    }
    year = newYear;
}

const char* Train::getRoute() const {
    return route ? route : "Не указан";
}

void Train::setRoute(const char* newRoute) {
    delete[] route;
    if (newRoute) {
        route = new char[strlen(newRoute) + 1];
        std::strcpy(route, newRoute);
    }
    else {
        route = nullptr;
    }
}

int Train::getWagonsCount() const {
    return wagonsCount;
}

void Train::setWagonsCount(int count) {
    if (count <= 0) {
        throw std::invalid_argument("Ошибка: Количество вагонов должно быть больше нуля!");
    }
    wagonsCount = count;
}

void Train::save(std::ostream& out) const {
    out << getName() << "\n" << getCargoVolume() << "\n"
        << getYear() << "\n" << getRoute() << "\n"
        << getWagonsCount() << "\n";
}

void Train::load(std::istream& in) {
    char buffer[256];
    double vol; int y, w;

    in.ignore(); in.getline(buffer, 256); setName(buffer);
    in >> vol; setCargoVolume(vol);
    in >> y; setYear(y);
    in.ignore(); in.getline(buffer, 256); setRoute(buffer);
    in >> w; setWagonsCount(w);
}