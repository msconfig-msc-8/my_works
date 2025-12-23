#include "fifteen/fifteenpuzzle.h"
#include <UnitTest++/UnitTest++.h>

#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using fifteen::Direction;
using fifteen::FifteenPuzzle;

static std::vector<int> Dump(const FifteenPuzzle& p) {
    std::vector<int> v;
    v.reserve(p.Size() * p.Size());
    for (std::size_t i = 0; i < p.Size() * p.Size(); ++i) {
        v.push_back(p[i]);
    }
    return v;
}

static bool IsPermutation0toNminus1(const FifteenPuzzle& p) {
    const std::size_t total = p.Size() * p.Size();
    auto v = Dump(p);
    std::sort(v.begin(), v.end());
    if (v.size() != total) return false;
    for (std::size_t i = 0; i < total; ++i) {
        if (v[i] != static_cast<int>(i)) return false;
    }
    return true;
}

SUITE(FifteenPuzzleTests) {

TEST(Ctor_DefaultSolved) {
    FifteenPuzzle p;
    CHECK(p.IsSolved());
}

TEST(Ctor_SizeGetter) {
    FifteenPuzzle p(4);
    CHECK_EQUAL(4u, p.Size());
}

TEST(Ctor_SizeTooSmallThrows) {
    CHECK_THROW(FifteenPuzzle(1), std::invalid_argument);
}

TEST(SolvedLayout_FirstAndLastCells) {
    FifteenPuzzle p(4);
    CHECK_EQUAL(1, p[0]);
    CHECK_EQUAL(15, p[14]);
    CHECK_EQUAL(0, p[15]);
}

TEST(OperatorIndex_OutOfRangeThrows) {
    FifteenPuzzle p(4);
    CHECK_THROW(p[999], std::out_of_range);
}

TEST(EmptyPos_InSolvedIsLastCell) {
    FifteenPuzzle p(4);
    const auto [r, c] = p.EmptyPos();
    CHECK_EQUAL(3u, r);
    CHECK_EQUAL(3u, c);
}

TEST(CanMove_FromSolvedCorner_DetectsBorders) {
    // В твоей реализации направления могут быть "неинтуитивные",
    // но главное: с нижнего правого угла две стороны недоступны, две доступны.
    FifteenPuzzle p(4); // пустая в (3,3)
    CHECK(!p.CanMove(Direction::Up));
    CHECK(!p.CanMove(Direction::Left));
    CHECK(p.CanMove(Direction::Down));
    CHECK(p.CanMove(Direction::Right));
}

TEST(Move_WhenImpossible_ReturnsFalseAndDoesNotChange) {
    FifteenPuzzle p(4);
    auto before = Dump(p);
    CHECK(!p.Move(Direction::Up));   // из угла нельзя
    auto after = Dump(p);
    CHECK(before == after);
}

TEST(Move_RightFromSolved_Swaps15AndZero) {
    FifteenPuzzle p(4);
    CHECK(p.Move(Direction::Right));
    CHECK_EQUAL(0, p[14]);
    CHECK_EQUAL(15, p[15]);
    CHECK(IsPermutation0toNminus1(p));
}

TEST(Move_DownFromSolved_Swaps12AndZero) {
    FifteenPuzzle p(4);
    CHECK(p.Move(Direction::Down));
    CHECK_EQUAL(0, p[11]);   // (2,3) индекс 11
    CHECK_EQUAL(12, p[15]);  // 12 ушёл вниз в правый нижний
    CHECK(IsPermutation0toNminus1(p));
}

TEST(IsSolved_FalseAfterMove) {
    FifteenPuzzle p(4);
    CHECK(p.Move(Direction::Right));
    CHECK(!p.IsSolved());
}

TEST(ResetSolved_AfterShuffleBecomesSolved) {
    FifteenPuzzle p(4);
    p.Shuffle(123, 50);
    CHECK(!p.IsSolved());
    p.ResetSolved();
    CHECK(p.IsSolved());
}

TEST(Shuffle_PreservesPermutation) {
    FifteenPuzzle p(4);
    p.Shuffle(42, 200);
    CHECK(IsPermutation0toNminus1(p));
}

TEST(Shuffle_UsuallyNotSolved) {
    FifteenPuzzle p(4);
    p.Shuffle(1, 50);
    CHECK(!p.IsSolved());
}

TEST(Equality_SameState) {
    FifteenPuzzle a(4);
    FifteenPuzzle b(4);
    CHECK(a == b);
    CHECK(!(a != b));
}

TEST(Inequality_AfterMove) {
    FifteenPuzzle a(4);
    FifteenPuzzle b(4);
    CHECK(b.Move(Direction::Right));
    CHECK(a != b);
}

TEST(StreamInput_Valid) {
    FifteenPuzzle p(3);
    std::stringstream ss;
    ss << "1 2 3 4 5 6 7 0 8";
    ss >> p;
    CHECK_EQUAL(0, p[7]);
    CHECK_EQUAL(8, p[8]);
    CHECK(IsPermutation0toNminus1(p));
}

TEST(StreamInput_DuplicateThrows) {
    FifteenPuzzle p(3);
    std::stringstream ss;
    ss << "1 2 3 4 5 6 7 7 0"; // повтор 7
    CHECK_THROW(ss >> p, std::runtime_error);
}

TEST(StreamInput_OutOfRangeThrows) {
    FifteenPuzzle p(3);
    std::stringstream ss;
    ss << "1 2 3 4 5 6 7 0 99"; // 99 вне диапазона
    CHECK_THROW(ss >> p, std::runtime_error);
}

TEST(StreamOutput_HasCorrectLineCount) {
    FifteenPuzzle p(4);
    std::stringstream ss;
    ss << p;

    int lines = 0;
    std::string line;
    while (std::getline(ss, line)) {
        ++lines;
    }
    CHECK_EQUAL(4, lines);
}


    TEST(Shuffle_WithSameSeedAndSteps_GivesSameState) {
    FifteenPuzzle a(4);
    FifteenPuzzle b(4);

    a.Shuffle(777, 200);
    b.Shuffle(777, 200);

    CHECK(a == b);
}

TEST(Shuffle_WithDifferentSeed_UsuallyDifferentState) {
    FifteenPuzzle a(4);
    FifteenPuzzle b(4);

    a.Shuffle(1, 200);
    b.Shuffle(2, 200);

    CHECK(a != b);
}

TEST(EmptyPos_ChangesAfterMove) {
    FifteenPuzzle p(4);
    auto before = p.EmptyPos();
    CHECK(p.Move(Direction::Right)); // из solved это возможно
    auto after = p.EmptyPos();
    CHECK(before != after);
}

TEST(TwoMoves_BackAndForth_ReturnsToSolved) {
    FifteenPuzzle p(4);
    CHECK(p.Move(Direction::Right));
    CHECK(p.Move(Direction::Left));  // обратный ход
    CHECK(p.IsSolved());
}

TEST(MoveSequence_KeepsPermutation) {
    FifteenPuzzle p(4);
    p.Shuffle(123, 50);

    // Сделаем несколько ходов, если возможно
    if (p.CanMove(Direction::Right)) p.Move(Direction::Right);
    if (p.CanMove(Direction::Down))  p.Move(Direction::Down);
    if (p.CanMove(Direction::Left))  p.Move(Direction::Left);
    if (p.CanMove(Direction::Up))    p.Move(Direction::Up);

    CHECK(IsPermutation0toNminus1(p));
}

TEST(OperatorEquality_Reflexive) {
    FifteenPuzzle p(4);
    CHECK(p == p);
    CHECK(!(p != p));
}

TEST(SolvedIsSolvedFor3x3) {
    FifteenPuzzle p(3);
    CHECK(p.IsSolved());
    CHECK_EQUAL(1, p[0]);
    CHECK_EQUAL(0, p[8]);
}

TEST(MoveOn3x3_RightFromSolved_Swaps8AndZero) {
    FifteenPuzzle p(3);
    CHECK(p.Move(Direction::Right));
    CHECK_EQUAL(0, p[7]);
    CHECK_EQUAL(8, p[8]);
}

TEST(StreamInputAndOutput_DoesNotThrowOnSolved) {
    FifteenPuzzle p(4);
    std::stringstream ss;
    ss << p; // просто проверяем что выводится
    CHECK(ss.str().size() > 0);
}

TEST(StreamInput_InvalidReadThrows) {
    FifteenPuzzle p(4);
    std::stringstream ss;
    ss << "1 2 3"; // мало чисел
    CHECK_THROW(ss >> p, std::runtime_error);
}

TEST(CopyConstructor_CopiesState) {
    FifteenPuzzle a(4);
    a.Shuffle(55, 100);

    FifteenPuzzle b = a;
    CHECK(a == b);
}

TEST(AssignmentOperator_CopiesState) {
    FifteenPuzzle a(4);
    a.Shuffle(99, 100);

    FifteenPuzzle b(4);
    b = a;
    CHECK(a == b);
}

}

 // SUITE

int main() {
    return UnitTest::RunAllTests();
}
