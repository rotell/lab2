#ifndef DOMINO_H
#define DOMINO_H

#include <iostream>
#include <stdexcept>

class Domino {
private:
    int left;
    int right;

public:
    Domino(int l = 0, int r = 0);

    static Domino generateRandomDomino();

    int getLeft() const;
    int getRight() const;

    void setLeft(int l);
    void setRight(int r);

    Domino operator~() const;

    bool operator==(const Domino &domino) const;

    Domino& operator=(const Domino& other);

    friend std::istream& operator>>(std::istream& in, Domino& d);
    friend std::ostream& operator<<(std::ostream& out, const Domino& d);

    void print() const;

private:
    static void printHalf(int value);
    static void printLine(int value, int line);
};

#endif
