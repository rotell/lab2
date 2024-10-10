#include "DominoGroup.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

    DominoGroup DominoGroup::createRandomGroup(int size) {
        DominoGroup group;
        group.dominoes.reserve(size);
        for (int i = 0; i < size; ++i) {
            group.dominoes.push_back(Domino::generateRandomDomino());
        }
        return group;
    }

    DominoGroup DominoGroup::generateFullSet(int repeat) {
        DominoGroup group;
        for (int i = 0; i <= 6; ++i) {
            for (int j = i; j <= 6; ++j) {
                for (int k = 0; k < repeat; ++k) {
                    group.dominoes.emplace_back(i, j);
                }
            }
        }
        return group;
    }

    DominoGroup& DominoGroup::operator+=(const Domino& domino) {
        dominoes.push_back(domino);
        return *this;
    }

    void DominoGroup::addRandomDomino() {
        dominoes.push_back(Domino::generateRandomDomino());
    }

    Domino DominoGroup::getRandomDomino() {
        if (dominoes.empty()) throw std::runtime_error("Group is empty");

        int index = rand() % dominoes.size();
        Domino removedDomino = dominoes[index];
        dominoes.erase(dominoes.begin() + index);
        return removedDomino;
    }

    Domino DominoGroup::getDomino(int left, int right) {
        auto it = std::find_if(dominoes.begin(), dominoes.end(), [left, right](const Domino& d) {
            return (d.getLeft() == left && d.getRight() == right) ||
                   (d.getLeft() == right && d.getRight() == left);
        });

        if (it != dominoes.end()) {
            Domino removedDomino = *it;
            dominoes.erase(it);
            return removedDomino;
        }

        throw std::invalid_argument("Specified domino not found");
    }

    Domino& DominoGroup::operator[](int index) {
        if (index < 0 || index >= dominoes.size()) {
            throw std::out_of_range("Invalid index");
        }
        return dominoes[index];
    }

    Domino DominoGroup::getByIndex(int index) {
        if (index < 0 || index >= dominoes.size()) {
            throw std::out_of_range("Invalid index");
        }

        Domino removedDomino = dominoes[index];
        dominoes.erase(dominoes.begin() + index);
        return removedDomino;
    }

    void DominoGroup::sortDominoes() {
        std::sort(dominoes.begin(), dominoes.end(), [](const Domino& a, const Domino& b) {
            int sumA = a.getLeft() + a.getRight();
            int sumB = b.getLeft() + b.getRight();
            return sumA < sumB;
        });
    }

    DominoGroup DominoGroup::getSubGroup(int value) {
        DominoGroup subgroup;
        auto it = std::remove_if(dominoes.begin(), dominoes.end(),[&](const Domino& domino) {
            if (domino.getLeft() == value || domino.getRight() == value) {
                subgroup.dominoes.push_back(domino);
                return true;
            }
            return false;
        });
        dominoes.erase(it, dominoes.end());
        return subgroup;
    }

    void DominoGroup::printGroup() const {
        for (const Domino& d : dominoes) {
            d.print();
        }
        cout << endl;
    }

    [[maybe_unused]]int DominoGroup::size() const {
        return dominoes.size();
    }

    DominoGroup& DominoGroup::operator=(const DominoGroup& other) {
        if (this == &other) return *this;
        dominoes = other.dominoes;
        return *this;
    }

    std::istream& operator>>(std::istream& in, DominoGroup& group) {
        int size;
        in >> size;
        group.dominoes.clear();
        group.dominoes.reserve(size);
        for (int i = 0; i < size; ++i) {
            Domino d;
            in >> d;
            group.dominoes.push_back(d);
        }
        return in;
    }

    std::ostream& operator<<(std::ostream& out, const DominoGroup& group) {
        for(const Domino& d : group.dominoes) {
            out << d << " ";
        }
        return out;
    }
