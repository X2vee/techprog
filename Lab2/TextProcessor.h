#ifndef TEXT_PROCESSOR_H
#define TEXT_PROCESSOR_H

class TextProcessor {
private:
    char* filename; // Имя текстового файла

    static int countWords(const char* sentence);
    static bool isSentenceEnd(char ch);

public:
    // Конструкторы и деструктор
    TextProcessor();
    explicit TextProcessor(const char* newFilename);
    TextProcessor(const TextProcessor& other);
    ~TextProcessor();

    // Геттеры и сеттеры
    const char* getFilename() const;
    void setFilename(const char* newFilename);

    // Основной метод обработки файла
    void printSentencesByWordCount(int targetWords) const;

    // Переопределение операторов
    TextProcessor& operator=(const TextProcessor& other);
};

#endif#pragma once
