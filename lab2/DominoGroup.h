#ifndef DOMINOGROUP_H
#define DOMINOGROUP_H

#include <vector>
#include "Domino.h"

/**
 * @class DominoGroup
 * @brief Класс, представляющий группу домино.
 *
 * DominoGroup предоставляет возможность создавать наборы домино, добавлять и удалять домино, сортировать и выводить их.
 */
class DominoGroup {
private:
    Domino* dominoes;   /**< Указатель на динамически выделенный массив домино. */
    size_t count;       /**< Текущее количество домино в группе. */
    size_t capacity;    /**< Текущая вместимость группы (размер выделенной памяти). */

    /**
     * @brief Расширяет внутренний массив домино, если текущее количество домино равно вместимости.
     * @param newCapacity Новая вместимость массива домино.
     */
    void reserve(size_t newCapacity);
public:
    /**
     * @brief Конструктор по умолчанию, создающий пустую группу домино.
     */
    DominoGroup() noexcept;
    /**
   * @brief Деструктор, освобождающий динамически выделенную память.
   */
    ~DominoGroup();

    /**
     * @brief Конструктор, принимающий список инициализации.
     * @param initList Список домино для инициализации группы.
     */
    DominoGroup(std::initializer_list<Domino> initList) : dominoes(nullptr), count(0), capacity(0) {
        count = initList.size();
        capacity = count;

        if (count > 0) {
            dominoes = new Domino[count];

            int index = 0;
            for (const auto& d : initList) {
                dominoes[index++] = d;
            }
        }
    }


    /**
     * @brief Создает группу случайных домино указанного размера.
     * @param size Количество домино в группе.
     * @return Группа случайных домино.
     */
    static DominoGroup createRandomGroup(size_t size);
    /**
     * @brief Генерирует полный набор домино, с указанным количеством повторений для каждой комбинации.
     * @param repeat Количество повторений каждой домино комбинации (по умолчанию 1).
     * @return Полный набор домино.
     */
    static DominoGroup generateFullSet(int repeat = 1);

    /**
     * @brief Добавляет домино в группу.
     * @param domino Домино, которое нужно добавить.
     * @return Ссылка на текущий объект после добавления.
     */
    DominoGroup& operator+=(const Domino& domino);

    /**
     * @brief Добавляет случайное домино в группу.
     */
    void addRandomDomino();

    /**
     * @brief Удаляет и возвращает случайное домино из группы.
     * @return Случайно выбранное домино.
     * @throws std::runtime_error Если группа пуста.
     */
    Domino getRandomDomino();
    /**
    * @brief Удаляет и возвращает конкретное домино по значениям сторон.
    * @param left Левая сторона домино.
    * @param right Правая сторона домино.
    * @return Найденное и удаленное домино.
    * @throws std::invalid_argument Если указанного домино не существует.
    */
    Domino getDomino(int left, int right);

    /**
     * @brief Возвращает домино по индексу в группе.
     * @param index Индекс домино в группе.
     * @return Ссылка на домино по заданному индексу.
     * @throws std::out_of_range Если индекс выходит за пределы допустимого диапазона.
     */
    Domino& operator[](int index);

    /**
    * @brief Константная версия оператора доступа по индексу.
     * @param index Индекс домино в группе.
    * @return Константная ссылка на домино.
     * @throws std::out_of_range Если индекс выходит за пределы допустимого диапазона.
    */
    const Domino& operator[](int index) const;

    /**
     * @brief Удаляет и возвращает домино по индексу.
     * @param index Индекс домино в группе.
     * @return Домино по заданному индексу.
     * @throws std::out_of_range Если индекс выходит за пределы допустимого диапазона.
     */
    Domino getByIndex(int index);

    /**
     * @brief Сортирует домино в группе по возрастанию суммы значений сторон.
     */
    void sortDominoes();

    /**
     * @brief Возвращает подгруппу домино с одной из сторон, равной указанному значению.
     * @param value Значение для фильтрации домино.
     * @return Группа домино, у которых одна из сторон равна value.
     */
    DominoGroup getSubGroup(int value);

    /**
     * @brief Выводит информацию о группе домино в консоль.
     */
    void printGroup() const;

    /**
     * @brief Возвращает количество домино в группе.
     * @return Количество домино.
     */
    size_t size() const;

    /**
     * @brief Оператор присваивания для копирования группы домино.
     * @param other Другая группа домино.
     * @return Ссылка на текущий объект.
     */
    DominoGroup& operator=(const DominoGroup& other);

    /**
     * @brief Перегруженный оператор ввода группы домино из потока.
     * @param in Входной поток.
     * @param group Группа домино.
     * @return Входной поток.
     */
    friend std::istream& operator>>(std::istream& in, DominoGroup& group);
    /**
     * @brief Перегруженный оператор вывода группы домино в поток.
     * @param out Выходной поток.
     * @param group Группа домино.
     * @return Выходной поток.
     */
    friend std::ostream& operator<<(std::ostream& out, const DominoGroup& group);
};

#endif
