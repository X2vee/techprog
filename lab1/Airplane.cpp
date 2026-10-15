#include "Airplane.h"
#include <cstring>
#include <stdexcept>

#pragma warning(disable: 4996)

// Конструкторы

Airplane::Airplane() : Base(), type(nullptr), dimensions(nullptr),
cities(nullptr), citiesCount(0) {
    std::cout << "[Airplane] Вызван конструктор по умолчанию" << std::endl;
}

Airplane::Airplane(const char* name, double cargoVolume, const char* newType,
    const char* newDimensions, const char** citiesList, int citiesNum)
    : Base(name, cargoVolume), type(nullptr), dimensions(nullptr),
    cities(nullptr), citiesCount(0) {
    std::cout << "[Airplane] Вызван конструктор с параметрами" << std::endl;
    setAirplaneType(newType);
    setDimensions(newDimensions);
    setCities(citiesList, citiesNum);
}

Airplane::Airplane(const Airplane& other)
    : Base(other), type(nullptr), dimensions(nullptr),
    cities(nullptr), citiesCount(0) {
    std::cout << "[Airplane] Вызван конструктор копирования" << std::endl;
    if (other.type) {
        type = new char[strlen(other.type) + 1];
        std::strcpy(type, other.type);
    }
    if (other.dimensions) {
        dimensions = new char[strlen(other.dimensions) + 1];
        std::strcpy(dimensions, other.dimensions);
    }
    if (other.cities && other.citiesCount > 0) {
        citiesCount = other.citiesCount;
        cities = new char* [citiesCount];
        for (int i = 0; i < citiesCount; ++i) {
            if (other.cities[i]) {
                cities[i] = new char[strlen(other.cities[i]) + 1];
                std::strcpy(cities[i], other.cities[i]);
            }
            else {
                cities[i] = nullptr;
            }
        }
    }
}

// Деструктор

Airplane::~Airplane() {
    std::cout << "[Airplane] Вызван деструктор" << std::endl;
    delete[] type;
    delete[] dimensions;
    for (int i = 0; i < citiesCount; ++i) {
        delete[] cities[i];
    }
    delete[] cities;
}

// Переопределение виртуальных функций

void Airplane::input() {
    std::cout << "\n=== Ввод данных о самолёте ===" << std::endl;

    // Ввод наименования
    char buffer[256];
    std::cout << "Наименование: ";
    std::cin.ignore();
    std::cin.getline(buffer, 256);
    setName(buffer);

    // Ввод объёма груза
    double volume;
    std::cout << "Объём перевозимого груза (тонн): ";
    std::cin >> volume;
    setCargoVolume(volume);

    // Ввод типа
    std::cout << "Тип самолёта: ";
    std::cin.ignore();
    std::cin.getline(buffer, 256);
    setAirplaneType(buffer);

    // Ввод габаритов
    std::cout << "Габариты (например, 70x60x15 м): ";
    std::cin.getline(buffer, 256);
    setDimensions(buffer);

    // Ввод городов
    int num;
    std::cout << "Количество городов: ";
    std::cin >> num;
    if (num < 0) {
        throw std::invalid_argument("Ошибка: количество городов не может быть отрицательным!");
    }
    if (num > 0) {
        const char** tempCities = new const char* [num];
        for (int i = 0; i < num; ++i) {
            std::cout << "Город " << (i + 1) << ": ";
            std::cin.ignore();
            std::cin.getline(buffer, 256);
            tempCities[i] = buffer;
        }
        setCities(tempCities, num);
        delete[] tempCities;
    }
    else {
        setCities(nullptr, 0);
    }
}

void Airplane::print() const {
    std::cout << "\n--- Самолёт ---" << std::endl;
    std::cout << "Наименование: " << getName() << std::endl;
    std::cout << "Объём груза: " << getCargoVolume() << " т" << std::endl;
    std::cout << "Тип: " << (type ? type : "Не указан") << std::endl;
    std::cout << "Габариты: " << (dimensions ? dimensions : "Не указаны") << std::endl;
    std::cout << "Города: ";
    if (cities && citiesCount > 0) {
        for (int i = 0; i < citiesCount; ++i) {
            std::cout << cities[i];
            if (i < citiesCount - 1) std::cout << ", ";
        }
    }
    else {
        std::cout << "Нет данных";
    }
    std::cout << std::endl;
}

Base* Airplane::clone() const {
    return new Airplane(*this);
}

const char* Airplane::getType() const {
    return "Самолёт";
}

// Геттеры и сеттеры 

const char* Airplane::getAirplaneType() const {
    return type ? type : "Не указан";
}

void Airplane::setAirplaneType(const char* newType) {
    delete[] type;
    if (newType) {
        type = new char[strlen(newType) + 1];
        std::strcpy(type, newType);
    }
    else {
        type = nullptr;
    }
}

const char* Airplane::getDimensions() const {
    return dimensions ? dimensions : "Не указаны";
}

void Airplane::setDimensions(const char* newDimensions) {
    delete[] dimensions;
    if (newDimensions) {
        dimensions = new char[strlen(newDimensions) + 1];
        std::strcpy(dimensions, newDimensions);
    }
    else {
        dimensions = nullptr;
    }
}

int Airplane::getCitiesCount() const {
    return citiesCount;
}

const char* Airplane::getCity(int index) const {
    if (index < 0 || index >= citiesCount) {
        throw std::out_of_range("Ошибка: индекс города вне диапазона!");
    }
    return cities[index] ? cities[index] : "Не указан";
}

void Airplane::setCities(const char** citiesList, int citiesNum) {
    for (int i = 0; i < citiesCount; ++i) {
        delete[] cities[i];
    }
    delete[] cities;

    if (citiesNum <= 0 || !citiesList) {
        cities = nullptr;
        citiesCount = 0;
        return;
    }

    citiesCount = citiesNum;
    cities = new char* [citiesCount];
    for (int i = 0; i < citiesCount; ++i) {
        if (citiesList[i]) {
            cities[i] = new char[strlen(citiesList[i]) + 1];
            std::strcpy(cities[i], citiesList[i]);
        }
        else {
            cities[i] = nullptr;
        }
    }
}

void Airplane::save(std::ostream& out) const {
    out << getName() << "\n" << getCargoVolume() << "\n"
        << getAirplaneType() << "\n" << getDimensions() << "\n"
        << getCitiesCount() << "\n";
    for (int i = 0; i < getCitiesCount(); ++i) {
        out << getCity(i) << "\n";
    }
}

void Airplane::load(std::istream& in) {
    char buffer[256];
    double vol;
    int count;

    in.ignore(); in.getline(buffer, 256); setName(buffer);
    in >> vol; setCargoVolume(vol);
    in.ignore(); in.getline(buffer, 256); setAirplaneType(buffer);
    in.ignore(); in.getline(buffer, 256); setDimensions(buffer);
    in >> count;

    if (count > 0) {
        const char** tempCities = new const char* [count];
        for (int i = 0; i < count; ++i) {
            in.ignore(); in.getline(buffer, 256);
            tempCities[i] = buffer;
        }
        setCities(tempCities, count);
        delete[] tempCities;
    }
    else {
        setCities(nullptr, 0);
    }
}