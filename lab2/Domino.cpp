#include "Domino.h"
#include <iostream>
#include <stdexcept>

using std::cin;
using std::cout;
using std::endl;
using std::uint8_t;

Domino::Domino(uint8_t l, uint8_t r) : left(l), right(r) {
    if (l < 0 || l > 6 || r < 0 || r > 6) {
        throw std::invalid_argument("Values should be between 0 and 6");
    }
}

Domino Domino::generateRandomDomino() {
    static std::mt19937 gen(static_cast<unsigned>(std::time(nullptr))); /**< Инициализация генератора времени */
    static std::uniform_int_distribution<> dist(0, 6); /**< Интервал от 0 до 6 */
    return {static_cast<uint8_t>(dist(gen)), static_cast<uint8_t>(dist(gen))};
}

uint8_t Domino::getLeft() const {
    return left;
}

uint8_t Domino::getRight() const {
    return right;
}

void Domino::setLeft(uint8_t l) {
    if (l < 0 || l > 6) {
        throw std::invalid_argument("Left value should be between 0 and 6");
    }
    left = l;
}

void Domino::setRight(uint8_t r) {
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
    int left, right;
    in >> left >> right;
    if (left < 0 || left > 6 || right < 0 || right > 6) {
        throw std::invalid_argument("Values should be between 0 and 6");
    }
    d.setLeft(static_cast<uint8_t>(left));
    d.setRight(static_cast<uint8_t>(right));
    return in;
}

std::ostream& operator<<(std::ostream& out, const Domino& d) {
    out << "(" << static_cast<int>(d.getLeft()) << "|" << static_cast<int>(d.getRight()) << ")";
    return out;
}

void Domino::printHalf(uint8_t value) {
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

void Domino::printLine(uint8_t value, int line) {
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

