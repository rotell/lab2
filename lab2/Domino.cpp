#include "Domino.h"
#include <iostream>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;

Domino::Domino(int l, int r) : left(l), right(r) {
    if (l < 0 || l > 6 || r < 0 || r > 6) {
        throw std::invalid_argument("Values should be between 0 and 6");
    }
}

Domino Domino::generateRandomDomino() {
    return {rand() % 7, rand() % 7};
}

int Domino::getLeft() const {
    return left;
}

int Domino::getRight() const {
    return right;
}

void Domino::setLeft(int l) {
    if (l < 0 || l > 6) {
        throw std::invalid_argument("Left value should be between 0 and 6");
    }
    left = l;
}

void Domino::setRight(int r) {
    if (r < 0 || r > 6) {
        throw std::invalid_argument("Right value should be between 0 and 6");
    }
    right = r;
}

Domino Domino::operator~() const {
    return {right, left};
}

bool Domino::operator==(const Domino &domino) const {
    return (left == domino.left && right == domino.right) || (left == domino.right && right == domino.left);
}

void Domino::print() const {
    printHalf(left);
    cout << "|-------|" << endl;
    printHalf(right);
    cout << endl;
}

Domino& Domino::operator=(const Domino& other) {
    if (this != &other) {
        left = other.left;
        right = other.right;
    }
    return *this;
}

std::istream& operator>>(std::istream& in, Domino& d) {
    in >> d.left >> d.right;
    if (d.left < 0 || d.left > 6 || d.right < 0 || d.right > 6) {
        throw std::invalid_argument("Values should be between 0 and 6");
    }
    return in;
}

std::ostream& operator<<(std::ostream& out, const Domino& d) {
    out << "(" << d.left << "|" << d.right << ")";
    return out;
}

void Domino::printHalf(int value) {
    cout << "| ";
    printLine(value, 1);
    cout << " |" << endl;

    cout << "| ";
    printLine(value, 2);
    cout << " |" << endl;

    cout << "| ";
    printLine(value, 3);
    cout << " |" << endl;
}

void Domino::printLine(int value, int line) {
    switch (value) {
        case 0:
            cout << "     ";
            break;
        case 1:
            if (line == 2) cout << "  o  ";
            else cout << "     ";
            break;
        case 2:
            if (line == 1) cout << "  o  ";
            else if (line == 3) cout << "  o  ";
            else cout << "     ";
            break;
        case 3:
            if (line == 1) cout << "o    ";
            else if (line == 2) cout << "  o  ";
            else cout << "    o";
            break;
        case 4:
            if (line == 1 || line == 3) cout << "o   o";
            else std::cout << "     ";
            break;
        case 5:
            if (line == 1) cout << "o   o";
            else if (line == 2) cout << "  o  ";
            else cout << "o   o";
            break;
        case 6:
            cout << "o   o";
            break;
        default:
            throw std::runtime_error("Error");
    }
}

