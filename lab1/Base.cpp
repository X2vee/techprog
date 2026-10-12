#include "Base.h"

#pragma warning(disable: 4996)

//Конструкторы
Base::Base() : name(nullptr), cargoVolume(0.0) {
    std::cout << "[Base] Вызван конструктор по умолчанию" << std::endl;
}

Base::Base(const char* newName, double newVolume) : name(nullptr), cargoVolume(0.0) {
    std::cout << "[Base] Вызван конструктор с параметрами" << std::endl;
    setName(newName);
    setCargoVolume(newVolume);
}

Base::Base(const Base& other) : name(nullptr), cargoVolume(0.0) {
    std::cout << "[Base] Вызван конструктор копирования" << std::endl;
    if (other.name) {
        name = new char[strlen(other.name) + 1];
        std::strcpy(name, other.name);
    }
    cargoVolume = other.cargoVolume;
}

//Деструктор
Base::~Base() {
    std::cout << "[Base] Вызван деструктор" << std::endl;
    delete[] name; 
}

//Геттеры и сеттеры
const char* Base::getName() const {
    return name ? name : "Не указано";
}

void Base::setName(const char* newName) {
    delete[] name; 
    if (newName) {
        name = new char[strlen(newName) + 1];
        std::strcpy(name, newName);
    }
    else {
        name = nullptr;
    }
}

double Base::getCargoVolume() const {
    return cargoVolume;
}

void Base::setCargoVolume(double volume) {
    if (volume < 0.0) {
        throw std::invalid_argument("Ошибка: Объем перевозимого груза не может быть отрицательным!");
    }
    cargoVolume = volume;
}