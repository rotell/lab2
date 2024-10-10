#ifndef DOMINOGROUP_H
#define DOMINOGROUP_H

#include <vector>
#include "Domino.h"

class DominoGroup {
private:
    std::vector<Domino> dominoes;

public:
    DominoGroup() = default;

    static DominoGroup createRandomGroup(int size);
    static DominoGroup generateFullSet(int repeat);

    DominoGroup& operator+=(const Domino& domino);

    void addRandomDomino();

    Domino getRandomDomino();
    Domino getDomino(int left, int right);

    Domino& operator[](int index);
    Domino getByIndex(int index);

    void sortDominoes();

    DominoGroup getSubGroup(int value);

    void printGroup() const;

    int size() const;

    DominoGroup& operator=(const DominoGroup& other);

    friend std::istream& operator>>(std::istream& in, DominoGroup& group);
    friend std::ostream& operator<<(std::ostream& out, const DominoGroup& group);
};

#endif
