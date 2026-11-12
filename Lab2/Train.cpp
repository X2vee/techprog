#include "Train.h"
#include <cstring>
#include <iomanip>
#include <stdexcept>

#pragma warning(disable: 4996)

// Конструкторы

TRAIN::TRAIN() : Base(), destination(nullptr), trainNumber(0), depHour(0), depMinute(0) {
    std::cout << "[TRAIN] Вызван конструктор по умолчанию" << std::endl;
}

TRAIN::TRAIN(const char* newDestination, int newTrainNumber, int newHour, int newMinute, const char* newCarrier)
    : Base(newCarrier), destination(nullptr), trainNumber(0), depHour(0), depMinute(0) {
    std::cout << "[TRAIN] Вызван конструктор с параметрами" << std::endl;
    setDestination(newDestination);
    setTrainNumber(newTrainNumber);
    setDepartureTime(newHour, newMinute);
}

TRAIN::TRAIN(const TRAIN& other)
    : Base(other), destination(nullptr), trainNumber(other.trainNumber),
    depHour(other.depHour), depMinute(other.depMinute) {
    std::cout << "[TRAIN] Вызван конструктор копирования" << std::endl;
    if (other.destination) {
        destination = new char[strlen(other.destination) + 1];
        std::strcpy(destination, other.destination);
    }
}

// Деструктор

TRAIN::~TRAIN() {
    std::cout << "[TRAIN] Вызван деструктор" << std::endl;
    delete[] destination;
}

// Переопределение виртуальных функций

void TRAIN::print() const {
    std::cout << *this << std::endl;
}

Base* TRAIN::clone() const {
    return new TRAIN(*this);
}

const char* TRAIN::getType() const {
    return "Поезд";
}

// Геттеры и сеттеры

const char* TRAIN::getDestination() const {
    return destination ? destination : "Не указан";
}

void TRAIN::setDestination(const char* newDestination) {
    if (!newDestination || strlen(newDestination) == 0) {
        throw std::invalid_argument("Ошибка: название пункта назначения не может быть пустым!");
    }
    delete[] destination;
    destination = new char[strlen(newDestination) + 1];
    std::strcpy(destination, newDestination);
}

int TRAIN::getTrainNumber() const {
    return trainNumber;
}

void TRAIN::setTrainNumber(int newTrainNumber) {
    if (newTrainNumber <= 0) {
        throw std::invalid_argument("Ошибка: номер поезда должен быть положительным числом!");
    }
    trainNumber = newTrainNumber;
}

int TRAIN::getDepHour() const {
    return depHour;
}

int TRAIN::getDepMinute() const {
    return depMinute;
}

void TRAIN::setDepartureTime(int newHour, int newMinute) {
    if (newHour < 0 || newHour > 23) {
        throw std::invalid_argument("Ошибка: часы отправления должны быть в диапазоне от 0 до 23!");
    }
    if (newMinute < 0 || newMinute > 59) {
        throw std::invalid_argument("Ошибка: минуты отправления должны быть в диапазоне от 0 до 59!");
    }
    depHour = newHour;
    depMinute = newMinute;
}

// Переопределение операторов

TRAIN& TRAIN::operator=(const TRAIN& other) {
    if (this != &other) {
        Base::operator=(other);
        delete[] destination;
        if (other.destination) {
            destination = new char[strlen(other.destination) + 1];
            std::strcpy(destination, other.destination);
        }
        else {
            destination = nullptr;
        }
        trainNumber = other.trainNumber;
        depHour = other.depHour;
        depMinute = other.depMinute;
    }
    return *this;
}

std::istream& operator>>(std::istream& in, TRAIN& train) {
    char buffer[256];
    int number, hour, minute;

    std::cout << "Пункт назначения: ";
    in >> std::ws;
    in.getline(buffer, 256);
    if (in.fail() || strlen(buffer) == 0) {
        throw std::invalid_argument("Ошибка: некорректное название пункта назначения!");
    }

    std::cout << "Номер поезда: ";
    if (!(in >> number)) {
        throw std::invalid_argument("Ошибка: номер поезда должен быть целым числом!");
    }

    std::cout << "Время отправления (часы и минуты через пробел, например 14 30): ";
    if (!(in >> hour >> minute)) {
        throw std::invalid_argument("Ошибка: часы и минуты должны быть целыми числами!");
    }

    train.setTrainNumber(number);
    train.setDepartureTime(hour, minute);
    train.setDestination(buffer);

    return in;
}

std::ostream& operator<<(std::ostream& out, const TRAIN& train) {
    out << "Поезд №" << train.trainNumber
        << " | Пункт назначения: " << train.getDestination()
        << " | Время отправления: "
        << std::setfill('0') << std::setw(2) << train.depHour << ":"
        << std::setfill('0') << std::setw(2) << train.depMinute
        << std::setfill(' ')
        << " | Перевозчик: " << train.getCarrier();
    return out;
}