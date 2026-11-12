#ifndef TRAIN_H
#define TRAIN_H

#include "Base.h"
#include <iostream>

class TRAIN : public Base {
private:
    char* destination; // Название пункта назначения
    int trainNumber;   // Номер поезда
    int depHour;       // Час отправления
    int depMinute;     // Минута отправления

public:
    // Конструкторы
    TRAIN();
    TRAIN(const char* newDestination, int newTrainNumber, int newHour, int newMinute, const char* newCarrier = "РЖД");
    TRAIN(const TRAIN& other);

    // Деструктор
    ~TRAIN() override;

    // Переопределение виртуальных функций Base
    void print() const override;
    Base* clone() const override;
    const char* getType() const override;

    // Геттеры и сеттеры
    const char* getDestination() const;
    void setDestination(const char* newDestination);

    int getTrainNumber() const;
    void setTrainNumber(int newTrainNumber);

    int getDepHour() const;
    int getDepMinute() const;
    void setDepartureTime(int newHour, int newMinute);

    // Переопределение операторов
    TRAIN& operator=(const TRAIN& other);
    friend std::istream& operator>>(std::istream& in, TRAIN& train);
    friend std::ostream& operator<<(std::ostream& out, const TRAIN& train);
};

#endif