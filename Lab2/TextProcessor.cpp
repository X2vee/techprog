#include "TextProcessor.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <cctype>
#include <stdexcept>

#pragma warning(disable: 4996)

// Конструкторы и деструктор

TextProcessor::TextProcessor() : filename(nullptr) {
    std::cout << "[TextProcessor] Вызван конструктор по умолчанию" << std::endl;
    setFilename("text.txt");
}

TextProcessor::TextProcessor(const char* newFilename) : filename(nullptr) {
    std::cout << "[TextProcessor] Вызван конструктор с параметрами" << std::endl;
    setFilename(newFilename);
}

TextProcessor::TextProcessor(const TextProcessor& other) : filename(nullptr) {
    std::cout << "[TextProcessor] Вызван конструктор копирования" << std::endl;
    if (other.filename) {
        filename = new char[strlen(other.filename) + 1];
        std::strcpy(filename, other.filename);
    }
}

TextProcessor::~TextProcessor() {
    std::cout << "[TextProcessor] Вызван деструктор" << std::endl;
    delete[] filename;
}

// Вспомогательные методы

bool TextProcessor::isSentenceEnd(char ch) {
    return ch == '.' || ch == '!' || ch == '?';
}

int TextProcessor::countWords(const char* sentence) {
    std::stringstream ss(sentence);
    char word[256];
    int wordCount = 0;

    while (ss >> word) {
        bool hasAlphaNum = false;
        for (int i = 0; word[i] != '\0'; ++i) {
            unsigned char uc = static_cast<unsigned char>(word[i]);
            if (std::isalnum(uc) || uc >= 128) {
                hasAlphaNum = true;
                break;
            }
        }
        if (hasAlphaNum) {
            wordCount++;
        }
    }
    return wordCount;
}

// Геттеры и сеттеры

const char* TextProcessor::getFilename() const {
    return filename ? filename : "Не указан";
}

void TextProcessor::setFilename(const char* newFilename) {
    if (!newFilename || strlen(newFilename) == 0) {
        throw std::invalid_argument("Ошибка: имя файла не может быть пустым!");
    }
    delete[] filename;
    filename = new char[strlen(newFilename) + 1];
    std::strcpy(filename, newFilename);
}

// Обработка файла

void TextProcessor::printSentencesByWordCount(int targetWords) const {
    if (targetWords <= 0) {
        throw std::invalid_argument("Ошибка: количество слов должно быть больше нуля!");
    }

    std::ifstream in(filename);
    if (!in.is_open()) {
        throw std::runtime_error("Ошибка: не удалось открыть указанный файл для чтения!");
    }

    std::stringstream fileStream;
    fileStream << in.rdbuf();
    in.close();

    int cap = 256;
    int len = 0;
    char* sentence = new char[cap];

    int found = 0;
    char ch;

    std::cout << "\n=== Предложения из " << targetWords << " слов(а) ===" << std::endl;

    while (fileStream.get(ch)) {
        if (len == 0 && std::isspace(static_cast<unsigned char>(ch))) {
            continue;
        }
        if (ch == '\n' || ch == '\r') {
            ch = ' ';
        }

        if (len + 2 >= cap) {
            int newCap = cap * 2;
            char* newBuf = new char[newCap];
            std::memcpy(newBuf, sentence, len);
            delete[] sentence;
            sentence = newBuf;
            cap = newCap;
        }

        sentence[len++] = ch;

        if (isSentenceEnd(ch)) {
            sentence[len] = '\0';
            if (countWords(sentence) == targetWords) {
                std::cout << ++found << ") " << sentence << std::endl;
            }
            len = 0;
        }
    }

    if (len > 0) {
        sentence[len] = '\0';
        if (countWords(sentence) == targetWords) {
            std::cout << ++found << ") " << sentence << std::endl;
        }
    }

    delete[] sentence;

    if (found == 0) {
        std::cout << "Предложений с заданным количеством слов не найдено." << std::endl;
    }
}

// Переопределение операторов

TextProcessor& TextProcessor::operator=(const TextProcessor& other) {
    if (this != &other) {
        delete[] filename;
        if (other.filename) {
            filename = new char[strlen(other.filename) + 1];
            std::strcpy(filename, other.filename);
        }
        else {
            filename = nullptr;
        }
    }
    return *this;
}