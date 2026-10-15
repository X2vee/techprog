#ifndef TRAIN_H
#define TRAIN_H

#include "Base.h"

class Train : public Base {
private:
    int year; // Год выпуска
    char* route; // Маршрут 
    int wagonsCount; // Количество вагонов

public:
    // Конструкторы
    Train();
    Train(const char* name, double cargoVolume, int year, const char* route, int wagonsCount);
    Train(const Train& other); 

    // Деструктор 
    ~Train() override;

    // Переопределение виртуальных функций Base
    void input() override;
    void print() const override;
    Base* clone() const override;
    const char* getType() const override;

    void save(std::ostream& out) const override;
    void load(std::istream& in) override;

    // Геттеры и сеттеры
    int getYear() const;
    void setYear(int year);

    const char* getRoute() const;
    void setRoute(const char* route);

    int getWagonsCount() const;
    void setWagonsCount(int count);
};

#endif