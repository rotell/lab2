#include <gtest/gtest.h>
#include "Domino.h"
#include "DominoGroup.h"

TEST(DominoTest, DefaultConstructor) {
    Domino d;
    EXPECT_EQ(d.getLeft(), 0);
    EXPECT_EQ(d.getRight(), 0);
}

TEST(DominoTest, ParameterizedConstructor) {
    Domino d(3, 4);
    EXPECT_EQ(d.getLeft(), 3);
    EXPECT_EQ(d.getRight(), 4);
}

TEST(DominoTest, InvalidConstructor) {
    EXPECT_THROW(Domino(-1, 7), std::invalid_argument);
}

TEST(DominoTest, SettersAndGetters) {
    Domino d;
    d.setLeft(2);
    d.setRight(5);
    EXPECT_EQ(d.getLeft(), 2);
    EXPECT_EQ(d.getRight(), 5);
}

TEST(DominoTest, FlipOperator) {
    Domino d(2, 5);
    Domino flipped = ~d;
    EXPECT_EQ(flipped.getLeft(), 5);
    EXPECT_EQ(flipped.getRight(), 2);
}

TEST(DominoTest, EqualityOperator) {
    Domino d1(3, 6);
    Domino d2(6, 3);
    EXPECT_TRUE(d1 == d2);

    Domino d3(4, 5);
    EXPECT_FALSE(d1 == d3);
}

TEST(DominoTest, OutputOperator) {
    Domino d(3, 6);
    std::stringstream out;
    out << d;
    EXPECT_EQ(out.str(), "(3|6)") << "Expected output is (3|6), but got: " << out.str();
}

TEST(DominoTest, InputOperator) {
    Domino d;
    std::stringstream input("4 2");
    input >> d;
    EXPECT_EQ(d.getLeft(), 4) << "Expected left value to be 4, but got: " << d.getLeft();
    EXPECT_EQ(d.getRight(), 2) << "Expected right value to be 2, but got: " << d.getRight();
}

TEST(DominoGroupTest, CreateRandomGroup) {
    DominoGroup group = DominoGroup::createRandomGroup(5);
    EXPECT_EQ(group.size(), 5);
}

TEST(DominoGroupTest, GenerateFullSet) {
    DominoGroup fullSet = DominoGroup::generateFullSet();

    EXPECT_EQ(fullSet.size(), 28);

    for (size_t i = 0; i < fullSet.size(); i++) {
        for (size_t j = i + 1; j < fullSet.size(); j++) {
            const Domino& d1 = fullSet[i];
            const Domino& d2 = fullSet[j];
            EXPECT_FALSE(d1 == d2) << "Duplicate domino found: (" << d1.getLeft() << "|" << d1.getRight() << ")";
        }
    }
}


TEST(DominoGroupTest, AddDomino) {
    DominoGroup group;
    group += Domino(1, 2);
    EXPECT_EQ(group.size(), 1);
    EXPECT_EQ(group[0].getLeft(), 1);
    EXPECT_EQ(group[0].getRight(), 2);
}

TEST(DominoGroupTest, GetRandomDomino) {
    DominoGroup group = DominoGroup::createRandomGroup(5);
    Domino d = group.getRandomDomino();
    EXPECT_EQ(group.size(), 4);
}

TEST(DominoGroupTest, GetSpecificDomino) {
    DominoGroup group;
    group += Domino(2, 3);
    group += Domino(4, 5);

    Domino d = group.getDomino(4, 5);
    EXPECT_EQ(d.getLeft(), 4);
    EXPECT_EQ(d.getRight(), 5);
    EXPECT_EQ(group.size(), 1);
}

TEST(DominoGroupTest, GetDominoByIndex) {
    DominoGroup group;
    group += Domino(3, 5);
    group += Domino(2, 4);

    Domino d = group.getByIndex(1);
    EXPECT_EQ(d.getLeft(), 2);
    EXPECT_EQ(d.getRight(), 4);
    EXPECT_EQ(group.size(), 1);
}

TEST(DominoGroupTest, SortDominoes) {
    DominoGroup group;
    group += Domino(5, 6);
    group += Domino(1, 1);
    group += Domino(3, 2);

    group.sortDominoes();

    EXPECT_EQ(group[0].getLeft(), 1);
    EXPECT_EQ(group[0].getRight(), 1);
    EXPECT_EQ(group[1].getLeft(), 3);
    EXPECT_EQ(group[1].getRight(), 2);
    EXPECT_EQ(group[2].getLeft(), 5);
    EXPECT_EQ(group[2].getRight(), 6);
}

TEST(DominoGroupTest, GetSubGroup) {
    DominoGroup group;
    group += Domino(5, 6);
    group += Domino(1, 1);
    group += Domino(3, 2);

    DominoGroup subgroup = group.getSubGroup(1);

    EXPECT_EQ(subgroup.size(), 1);
    EXPECT_EQ(subgroup[0].getLeft(), 1);
    EXPECT_EQ(subgroup[0].getRight(), 1);
    EXPECT_EQ(group.size(), 2);
}

TEST(DominoGroupTest, AssignmentOperator) {
    DominoGroup group1 = DominoGroup::createRandomGroup(3);
    DominoGroup group2;

    group2 = group1;
    EXPECT_EQ(group1.size(), group2.size());
    EXPECT_EQ(group1[0].getLeft(), group2[0].getLeft());
}

TEST(DominoGroupTest, OutputOperator) {
    DominoGroup group;
    group += Domino(1, 2);
    group += Domino(3, 4);

    std::stringstream out;
    out << group;

    EXPECT_EQ(out.str(), "(1|2) (3|4) ");
}

TEST(DominoGroupTest, InputOperator) {
    DominoGroup group;
    std::stringstream input("2 2 3 4 5");

    input >> group;
    EXPECT_EQ(group.size(), 2);
    EXPECT_EQ(group[0].getLeft(), 2);
    EXPECT_EQ(group[0].getRight(), 3);
    EXPECT_EQ(group[1].getLeft(), 4);
    EXPECT_EQ(group[1].getRight(), 5);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
