#include "Car.h"
#include <cstring>
#include <stdexcept>

#pragma warning(disable: 4996)

// Конструкторы 

Car::Car() : Base(), year(0), brand(nullptr), model(nullptr),
deliveries(nullptr), deliveryCount(0) {
    std::cout << "[Car] Вызван конструктор по умолчанию" << std::endl;
}

Car::Car(const char* name, double cargoVolume, int newYear,
    const char* newBrand, const char* newModel)
    : Base(name, cargoVolume), year(0), brand(nullptr), model(nullptr),
    deliveries(nullptr), deliveryCount(0) {
    std::cout << "[Car] Вызван конструктор с параметрами" << std::endl;
    setYear(newYear);
    setBrand(newBrand);
    setModel(newModel);
}

Car::Car(const Car& other)
    : Base(other), year(0), brand(nullptr), model(nullptr),
    deliveries(nullptr), deliveryCount(0) {
    std::cout << "[Car] Вызван конструктор копирования" << std::endl;

    year = other.year;

    // Глубокое копирование строк
    if (other.brand) {
        brand = new char[strlen(other.brand) + 1];
        std::strcpy(brand, other.brand);
    }
    if (other.model) {
        model = new char[strlen(other.model) + 1];
        std::strcpy(model, other.model);
    }

    // Глубокое копирование массива структур
    if (other.deliveries && other.deliveryCount > 0) {
        deliveryCount = other.deliveryCount;
        deliveries = new DeliveryInfo[deliveryCount];
        for (int i = 0; i < deliveryCount; ++i) {
            deliveries[i].hours = other.deliveries[i].hours;
            deliveries[i].volume = other.deliveries[i].volume;
            if (other.deliveries[i].city) {
                deliveries[i].city = new char[strlen(other.deliveries[i].city) + 1];
                std::strcpy(deliveries[i].city, other.deliveries[i].city);
            }
            else {
                deliveries[i].city = nullptr;
            }
        }
    }
}

// Деструктор

Car::~Car() {
    std::cout << "[Car] Вызван деструктор" << std::endl;
    delete[] brand;
    delete[] model;

    // Освобождение памяти для каждой структуры в массиве
    for (int i = 0; i < deliveryCount; ++i) {
        delete[] deliveries[i].city;
    }
    delete[] deliveries;
}

// Переопределение виртуальных функций

void Car::input() {
    std::cout << "\n=== Ввод данных об автомобиле ===" << std::endl;
    char buffer[256];

    // Наименование и объем груза (из базового класса)
    std::cout << "Наименование перевозчика: ";
    std::cin.ignore();
    std::cin.getline(buffer, 256);
    setName(buffer);

    double volume;
    std::cout << "Общий объем перевозимого груза (тонн): ";
    std::cin >> volume;
    setCargoVolume(volume);

    // Год выпуска
    int y;
    std::cout << "Год выпуска: ";
    std::cin >> y;
    setYear(y);

    // Марка
    std::cout << "Марка: ";
    std::cin.ignore();
    std::cin.getline(buffer, 256);
    setBrand(buffer);

    // Модель
    std::cout << "Модель: ";
    std::cin.getline(buffer, 256);
    setModel(buffer);

    // Информация о доставках
    int count;
    std::cout << "Количество городов доставки: ";
    std::cin >> count;

    if (count < 0) {
        throw std::invalid_argument("Ошибка: количество доставок не может быть отрицательным!");
    }

    if (count > 0) {
        DeliveryInfo* tempDeliveries = new DeliveryInfo[count];
        for (int i = 0; i < count; ++i) {
            std::cout << "\n--- Доставка " << (i + 1) << " ---" << std::endl;

            std::cout << "Город: ";
            std::cin.ignore();
            std::cin.getline(buffer, 256);
            tempDeliveries[i].city = new char[strlen(buffer) + 1];
            std::strcpy(tempDeliveries[i].city, buffer);

            std::cout << "Количество часов доставки: ";
            std::cin >> tempDeliveries[i].hours;
            if (tempDeliveries[i].hours <= 0) {
                throw std::invalid_argument("Ошибка: время доставки должно быть больше 0!");
            }

            std::cout << "Объем груза для этого города (тонн): ";
            std::cin >> tempDeliveries[i].volume;
            if (tempDeliveries[i].volume < 0) {
                throw std::invalid_argument("Ошибка: объем груза не может быть отрицательным!");
            }
        }
        setDeliveries(tempDeliveries, count);

        for (int i = 0; i < count; ++i) delete[] tempDeliveries[i].city;
        delete[] tempDeliveries;
    }
    else {
        setDeliveries(nullptr, 0);
    }
}

void Car::print() const {
    std::cout << "\n--- Автомобиль ---" << std::endl;
    std::cout << "Наименование: " << getName() << std::endl;
    std::cout << "Общий объем груза: " << getCargoVolume() << " т" << std::endl;
    std::cout << "Год выпуска: " << year << std::endl;
    std::cout << "Марка: " << (brand ? brand : "Не указана") << std::endl;
    std::cout << "Модель: " << (model ? model : "Не указана") << std::endl;

    std::cout << "Информация о доставках:" << std::endl;
    if (deliveries && deliveryCount > 0) {
        for (int i = 0; i < deliveryCount; ++i) {
            std::cout << "  -> Город: " << (deliveries[i].city ? deliveries[i].city : "Неизвестно")
                << ", Часы: " << deliveries[i].hours
                << ", Объем: " << deliveries[i].volume << " т" << std::endl;
        }
    }
    else {
        std::cout << "  -> Доставки не настроены." << std::endl;
    }
}

Base* Car::clone() const {
    return new Car(*this);
}

const char* Car::getType() const {
    return "Автомобиль";
}

// Переопределение операторор
bool Car::operator==(const Car& other) const {
    bool brandMatch = (brand == other.brand) || (brand && other.brand && std::strcmp(brand, other.brand) == 0);
    bool modelMatch = (model == other.model) || (model && other.model && std::strcmp(model, other.model) == 0);
    return brandMatch && modelMatch;
}

// Геттеры и сеттеры
int Car::getYear() const { return year; }

void Car::setYear(int newYear) {
    if (newYear < 1886 || newYear > 2026) {
        throw std::invalid_argument("Ошибка: Некорректный год выпуска автомобиля!");
    }
    year = newYear;
}

const char* Car::getBrand() const { return brand ? brand : "Не указана"; }

void Car::setBrand(const char* newBrand) {
    delete[] brand;
    if (newBrand) {
        brand = new char[strlen(newBrand) + 1];
        std::strcpy(brand, newBrand);
    }
    else {
        brand = nullptr;
    }
}

const char* Car::getModel() const { return model ? model : "Не указана"; }

void Car::setModel(const char* newModel) {
    delete[] model;
    if (newModel) {
        model = new char[strlen(newModel) + 1];
        std::strcpy(model, newModel);
    }
    else {
        model = nullptr;
    }
}

int Car::getDeliveryCount() const { return deliveryCount; }

const DeliveryInfo& Car::getDelivery(int index) const {
    if (index < 0 || index >= deliveryCount) {
        throw std::out_of_range("Ошибка: индекс доставки вне диапазона!");
    }
    return deliveries[index];
}

void Car::setDeliveries(const DeliveryInfo* newDeliveries, int count) {
    for (int i = 0; i < deliveryCount; ++i) {
        delete[] deliveries[i].city;
    }
    delete[] deliveries;

    if (count <= 0 || !newDeliveries) {
        deliveries = nullptr;
        deliveryCount = 0;
        return;
    }

    deliveryCount = count;
    deliveries = new DeliveryInfo[deliveryCount];
    for (int i = 0; i < deliveryCount; ++i) {
        deliveries[i].hours = newDeliveries[i].hours;
        deliveries[i].volume = newDeliveries[i].volume;
        if (newDeliveries[i].city) {
            deliveries[i].city = new char[strlen(newDeliveries[i].city) + 1];
            std::strcpy(deliveries[i].city, newDeliveries[i].city);
        }
        else {
            deliveries[i].city = nullptr;
        }
    }
}

void Car::save(std::ostream& out) const {
    out << getName() << "\n" << getCargoVolume() << "\n"
        << getYear() << "\n" << getBrand() << "\n" << getModel() << "\n"
        << getDeliveryCount() << "\n";
    for (int i = 0; i < getDeliveryCount(); ++i) {
        const DeliveryInfo& info = getDelivery(i);
        out << info.city << "\n" << info.hours << "\n" << info.volume << "\n";
    }
}

void Car::load(std::istream& in) {
    char buffer[256];
    double vol; int y, count;

    in.ignore(); in.getline(buffer, 256); setName(buffer);
    in >> vol; setCargoVolume(vol);
    in >> y; setYear(y);
    in.ignore(); in.getline(buffer, 256); setBrand(buffer);
    in.ignore(); in.getline(buffer, 256); setModel(buffer);
    in >> count;

    if (count > 0) {
        DeliveryInfo* tempDeliveries = new DeliveryInfo[count];
        for (int i = 0; i < count; ++i) {
            in.ignore(); in.getline(buffer, 256);
            tempDeliveries[i].city = new char[strlen(buffer) + 1];
            strcpy(tempDeliveries[i].city, buffer);
            in >> tempDeliveries[i].hours >> tempDeliveries[i].volume;
        }
        setDeliveries(tempDeliveries, count);
        for (int i = 0; i < count; ++i) delete[] tempDeliveries[i].city;
        delete[] tempDeliveries;
    }
    else {
        setDeliveries(nullptr, 0);
    }
}