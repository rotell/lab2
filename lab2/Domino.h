#ifndef DOMINO_H
#define DOMINO_H

#include <iostream>
#include <stdexcept>
#include <cstdint>
#include <random>
#include <ctime>


/**
 * @class Domino
 * @brief Класс, представляющий домино с двумя сторонами.
 *
 * Класс Domino содержит две стороны с числами от 0 до 6. Обеспечивает методы для
 * получения и установки значений, генерации случайных домино, сравнения и переворачивания.
 */
class Domino {
private:
    std::uint8_t left;  /**< Левая сторона домино. Значение от 0 до 6. */
    std::uint8_t right; /**< Правая сторона домино. Значение от 0 до 6. */

public:
    /**
     * @brief Конструктор домино с двумя значениями.
     * @param l Левая сторона (значение от 0 до 6, по умолчанию 0).
     * @param r Правая сторона (значение от 0 до 6, по умолчанию 0).
     * @throws std::invalid_argument Если значения не находятся в пределах от 0 до 6.
     */
    Domino(std::uint8_t l = 0, std::uint8_t r = 0);

    /**
     * @brief Генерирует случайный объект домино.
     * @return Случайно сгенерированный объект домино.
     */
    static Domino generateRandomDomino();

    /**
     * @brief Получает значение левой стороны домино.
     * @return Значение левой стороны.
     */
    std::uint8_t getLeft() const;
    /**
     * @brief Получает значение правой стороны домино.
     * @return Значение правой стороны.
     */
    std::uint8_t getRight() const;

    /**
     * @brief Устанавливает значение левой стороны домино.
     * @param l Новое значение для левой стороны.
     * @throws std::invalid_argument Если значение не находится в пределах от 0 до 6.
     */
    void setLeft(std::uint8_t l);
    /**
     * @brief Устанавливает значение левой стороны домино.
     * @param r Новое значение для правой стороны.
     * @throws std::invalid_argument Если значение не находится в пределах от 0 до 6.
     */
    void setRight(std::uint8_t r);

    /**
     * @brief Переворачивает домино, меняя левую и правую стороны местами.
     * @return Новый объект домино с перевернутыми сторонами.
     */
    Domino operator~() const;

    /**
     * @brief Сравнивает два домино.
     * @param domino Объект домино для сравнения.
     * @return true, если домино равны (не имеет значения, на какой стороне какое число).
     * @return false, если домино не равны.
     */
    bool operator==(const Domino &domino) const;

    /**
     * @brief Оператор присваивания для домино.
     * @param other Объект домино для копирования.
     * @return Ссылка на текущий объект после присваивания.
     */
    Domino& operator=(const Domino& other);

    /**
     * @brief Перегруженный оператор ввода для домино.
     * @param in Входной поток.
     * @param d Объект домино для заполнения.
     * @return Входной поток.
     */
    friend std::istream& operator>>(std::istream& in, Domino& d);

    /**
     * @brief Перегруженный оператор вывода для домино.
     * @param out Выходной поток.
     * @param d Объект домино для вывода.
     * @return Выходной поток.
     */
    friend std::ostream& operator<<(std::ostream& out, const Domino& d);

    /**
     * @brief Выводит изображение домино на консоль.
     */
    void print() const;

private:
    /**
     * @brief Выводит одну сторону домино.
     * @param value Значение стороны (от 0 до 6).
     */
    static void printHalf(std::uint8_t value);

    /**
     * @brief Выводит одну строку изображения домино для заданного значения.
     * @param value Значение стороны (от 0 до 6).
     * @param line Номер строки для вывода (1, 2 или 3).
     */
    static void printLine(std::uint8_t value, int line);
};

#endif
