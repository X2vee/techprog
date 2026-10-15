#ifndef CAR_H
#define CAR_H

#include "Base.h"

// Структура для хранения информации о доставке в конкретный город
struct DeliveryInfo {
    char* city; // Название города
    int hours; // Количество часов доставки
    double volume; // Объем груза для этого города
};

class Car : public Base {
private:
    int year; // Год выпуска
    char* brand; // Марка автомобиля
    char* model; // Модель автомобиля
    DeliveryInfo* deliveries; // Динамический массив структур с информацией о доставках
    int deliveryCount; // Количество записей о доставках

public:
    // Конструкторы
    Car();
    Car(const char* name, double cargoVolume, int year, const char* brand, const char* model);
    Car(const Car& other); 

    // Деструктор 
    ~Car() override;

    // Переопределение виртуальных функций Base 
    void input() override;
    void print() const override;
    Base* clone() const override;
    const char* getType() const override;

    // Оператор сравнения двух автомобилей по марке и модели
    bool operator==(const Car& other) const;

    // Геттеры и сеттеры 
    int getYear() const;
    void setYear(int year);

    const char* getBrand() const;
    void setBrand(const char* brand);

    const char* getModel() const;
    void setModel(const char* model);

    int getDeliveryCount() const;
    void setDeliveries(const DeliveryInfo* newDeliveries, int count);

    void save(std::ostream& out) const override;
    void load(std::istream& in) override;

    // Метод для получения конкретной доставки
    const DeliveryInfo& getDelivery(int index) const;
};

#endif