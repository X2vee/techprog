#include "Base.h"
#include <cstring>
#include <stdexcept>

#pragma warning(disable: 4996)

// Конструкторы

Base::Base() : carrier(nullptr) {
    std::cout << "[Base] Вызван конструктор по умолчанию" << std::endl;
    setCarrier("РЖД");
}

Base::Base(const char* newCarrier) : carrier(nullptr) {
    std::cout << "[Base] Вызван конструктор с параметрами" << std::endl;
    setCarrier(newCarrier);
}

Base::Base(const Base& other) : carrier(nullptr) {
    std::cout << "[Base] Вызван конструктор копирования" << std::endl;
    if (other.carrier) {
        carrier = new char[strlen(other.carrier) + 1];
        std::strcpy(carrier, other.carrier);
    }
}

// Деструктор

Base::~Base() {
    std::cout << "[Base] Вызван деструктор" << std::endl;
    delete[] carrier;
}

// Геттеры и сеттеры

const char* Base::getCarrier() const {
    return carrier ? carrier : "Не указан";
}

void Base::setCarrier(const char* newCarrier) {
    if (!newCarrier || strlen(newCarrier) == 0) {
        throw std::invalid_argument("Ошибка: наименование перевозчика не может быть пустым!");
    }
    delete[] carrier;
    carrier = new char[strlen(newCarrier) + 1];
    std::strcpy(carrier, newCarrier);
}

// Переопределение операторов

Base& Base::operator=(const Base& other) {
    if (this != &other) {
        delete[] carrier;
        if (other.carrier) {
            carrier = new char[strlen(other.carrier) + 1];
            std::strcpy(carrier, other.carrier);
        }
        else {
            carrier = nullptr;
        }
    }
    return *this;
}