#ifndef AIRPLANE_H
#define AIRPLANE_H

#include "Base.h"

class Airplane : public Base {
private:
    char* type; // Модель самолета
    char* dimensions; // Габариты 
    char** cities; // Динамический массив городов
    int citiesCount; // Количество городов

public:
    //Конструкторы
    Airplane();
    Airplane(const char* name, double cargoVolume, const char* type,
        const char* dimensions, const char** citiesList, int citiesNum);
    Airplane(const Airplane& other); 

    //Деструктор
    ~Airplane() override;

    //Переопределение виртуальных функций Base
    void input() override;
    void print() const override;
    Base* clone() const override;
    const char* getType() const override;

    void save(std::ostream& out) const override;
    void load(std::istream& in) override;

    //Геттеры и сеттеры
    const char* getAirplaneType() const;
    void setAirplaneType(const char* newType);

    const char* getDimensions() const;
    void setDimensions(const char* newDimensions);

    int getCitiesCount() const;
    const char* getCity(int index) const;
    void setCities(const char** citiesList, int citiesNum);
};

#endif 