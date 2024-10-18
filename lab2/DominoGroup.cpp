#include "DominoGroup.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


    DominoGroup::DominoGroup() noexcept : dominoes(nullptr), count(0), capacity(0) {}

    void DominoGroup::reserve(size_t newCapacity) {
        if (newCapacity > capacity) {
            Domino* newDominoes = new Domino[newCapacity];
            for (size_t i = 0; i < count; ++i) {
                newDominoes[i] = dominoes[i];
            }
            delete[] dominoes;
            dominoes = newDominoes;
            capacity = newCapacity;
        }
    }

    DominoGroup::~DominoGroup() {
    delete[] dominoes;
}

    DominoGroup DominoGroup::createRandomGroup(size_t size) {
        DominoGroup group;
        group.reserve(size);
        for (int i = 0; i < size; ++i) {
            group.dominoes[group.count++] = Domino::generateRandomDomino();
        }
        return group;
    }

    DominoGroup DominoGroup::generateFullSet(int repeat) {
        DominoGroup group;
        group.reserve(28 * repeat); // Максимум 28 домино в полном наборе
        for (int i = 0; i <= 6; i++) {
            for (int j = i; j <= 6; j++) {
                for (int k = 0; k < repeat; ++k) {
                    group.dominoes[group.count++] = Domino(i, j);
                }
            }
        }
        return group;
    }

DominoGroup& DominoGroup::operator+=(const Domino& domino) {
    if (count == capacity) {
        reserve(capacity == 0 ? 1 : capacity * 2);
    }
    dominoes[count++] = domino;
    return *this;
}

    void DominoGroup::addRandomDomino() {
        if (count == capacity) {
            reserve(capacity == 0 ? 1 : capacity * 2);
        }
        dominoes[count++] = Domino::generateRandomDomino();
    }

    Domino DominoGroup::getRandomDomino() {
        if (count == 0) throw std::runtime_error("Group is empty");

        int index = rand() % count;
        Domino removedDomino = dominoes[index];
        --count;
        for (int i = index; i < count; i++) {
            dominoes[i] = dominoes[i + 1];
        }
        return removedDomino;
    }

    Domino DominoGroup::getDomino(int left, int right) {
        for (size_t i = 0; i < count; i++) {
            if ((dominoes[i].getLeft() == left && dominoes[i].getRight() == right) || (dominoes[i].getLeft() == right && dominoes[i].getRight() == left)) {
                Domino removedDomino = dominoes[i];
                for (size_t j = i; j < count - 1; j++) {
                    dominoes[j] = dominoes[j + 1];
                }
                --count;
                return removedDomino;
            }
        }
        throw std::invalid_argument("Specified domino not found");
    }

    Domino& DominoGroup::operator[](int index) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Invalid index");
        }
        return dominoes[index];
    }

    const Domino& DominoGroup::operator[](int index) const {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Invalid index");
        }
        return dominoes[index];
    }

    Domino DominoGroup::getByIndex(int index) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Invalid index");
        }

        Domino removedDomino = dominoes[index];
        for (int i = index; i < count - 1; i++) {
            dominoes[i] = dominoes[i + 1];
        }
        --count;
        return removedDomino;
    }

    void DominoGroup::sortDominoes() {
        std::sort(dominoes, dominoes + count, [](const Domino& a, const Domino& b) {
            int sumA = a.getLeft() + a.getRight();
            int sumB = b.getLeft() + b.getRight();
            return sumA < sumB;
        });
    }

    DominoGroup DominoGroup::getSubGroup(int value) {
        DominoGroup subgroup;
        for (size_t i = 0; i < count; ) {
            if (dominoes[i].getLeft() == value || dominoes[i].getRight() == value) {
                if (subgroup.count == subgroup.capacity) {
                    subgroup.reserve(subgroup.capacity == 0 ? 1 : subgroup.capacity * 2);
                }
                subgroup.dominoes[subgroup.count++] = dominoes[i];
                --count;
                for (size_t j = i; j < count; j++) {
                    dominoes[j] = dominoes[j + 1];
                }
            } else {
                i++;
            }
        }
        return subgroup;
    }

    void DominoGroup::printGroup() const {
        for (size_t i = 0; i < count; i++) {
            dominoes[i].print();
        }
        cout << endl;
    }

    size_t DominoGroup::size() const {
        return count;
    }


DominoGroup& DominoGroup::operator=(const DominoGroup& other) {
    if (this == &other) return *this;
    delete[] dominoes;
    count = other.count;
    capacity = other.capacity;
    dominoes = new Domino[capacity];
    for (size_t i = 0; i < count; i++) {
        dominoes[i] = other.dominoes[i];
    }
    return *this;
}

    std::istream& operator>>(std::istream& in, DominoGroup& group) {
        int size;
        in >> size;
        group.reserve(size);
        group.count = size;
        for (int i = 0; i < size; i++) {
            in >> group.dominoes[i];
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DominoGroup& group) {
        for (size_t i = 0; i < group.count; i++) {
            out << group.dominoes[i] << " ";
        }
        return out;
    }
