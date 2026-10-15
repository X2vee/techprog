#include "Keeper.h"
#include <iostream>

// Конструкторы и деструктор 

Keeper::Keeper() : items(nullptr), count(0), capacity(0) {
    std::cout << "[Keeper] Вызван конструктор по умолчанию" << std::endl;
}

Keeper::Keeper(const Keeper& other) : items(nullptr), count(0), capacity(0) {
    std::cout << "[Keeper] Вызван конструктор копирования" << std::endl;
    for (int i = 0; i < other.count; ++i) {
        addItem(other.items[i]->clone());
    }
}

Keeper::~Keeper() {
    std::cout << "[Keeper] Вызван деструктор" << std::endl;
    clear();
}

// Вспомогательные методы 

void Keeper::resize() {
    if (count >= capacity) {
        capacity = (capacity == 0) ? 2 : capacity * 2;
        Base** newItems = new Base * [capacity];
        for (int i = 0; i < count; ++i) {
            newItems[i] = items[i];
        }
        delete[] items;
        items = newItems;
    }
}

void Keeper::clear() {
    for (int i = 0; i < count; ++i) {
        delete items[i]; 
    }
    delete[] items;      
    items = nullptr;
    count = 0;
    capacity = 0;
}

// Методы управления 

void Keeper::addItem(Base* item) {
    if (!item) throw std::invalid_argument("Ошибка: попытка добавить пустой указатель!");
    resize();
    items[count++] = item; 
}

void Keeper::removeItem(int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Ошибка: индекс элемента вне диапазона!");
    }
    delete items[index]; // Удаляем объект
    // Сдвигаем элементы влево
    for (int i = index; i < count - 1; ++i) {
        items[i] = items[i + 1];
    }
    count--;
}

void Keeper::printAll() const {
    if (count == 0) {
        std::cout << "\nСписок перевозчиков пуст." << std::endl;
        return;
    }
    std::cout << "\n=== Список всех перевозчиков (" << count << " шт.) ===" << std::endl;
    for (int i = 0; i < count; ++i) {
        std::cout << "[" << (i + 1) << "] ";
        items[i]->print();
    }
}

Base* Keeper::getItem(int index) const {
    if (index < 0 || index >= count) {
        throw std::out_of_range("Ошибка: индекс элемента вне диапазона!");
    }
    return items[index];
}

int Keeper::getCount() const {
    return count;
}

// Работа с файлами

void Keeper::saveToFile(const char* filename) const {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw std::runtime_error("Ошибка: не удалось открыть файл для записи!");
    }

    out << count << std::endl; // Сохраняем количество

    for (int i = 0; i < count; ++i) {
        // Сохраняем тип объекта (1 - Самолет, 2 - Поезд, 3 - Автомобиль)
        const char* type = items[i]->getType();
        if (std::strcmp(type, "Самолёт") == 0) out << 1 << std::endl;
        else if (std::strcmp(type, "Поезд") == 0) out << 2 << std::endl;
        else if (std::strcmp(type, "Автомобиль") == 0) out << 3 << std::endl;

        // Вызываем виртуальный метод сохранения самого объекта
        items[i]->save(out);
    }
    out.close();
    std::cout << "Данные успешно сохранены в файл " << filename << std::endl;
}

void Keeper::loadFromFile(const char* filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::runtime_error("Ошибка: не удалось открыть файл для чтения!");
    }

    clear(); // Очищаем текущие данные перед загрузкой

    int n;
    in >> n;

    for (int i = 0; i < n; ++i) {
        int type;
        in >> type;

        if (type == 1) {
            Airplane* a = new Airplane();
            a->load(in);
            addItem(a);
        }
        else if (type == 2) {
            Train* t = new Train();
            t->load(in);
            addItem(t);
        }
        else if (type == 3) {
            Car* c = new Car();
            c->load(in);
            addItem(c);
        }
    }
    in.close();
    std::cout << "Данные успешно загружены из файла " << filename << std::endl;
}

// --- Переопределение операторов ---

Keeper& Keeper::operator=(const Keeper& other) {
    if (this != &other) {
        clear();
        for (int i = 0; i < other.count; ++i) {
            addItem(other.items[i]->clone());
        }
    }
    return *this;
}

bool Keeper::operator==(const Keeper& other) const {
    return count == other.count;
}