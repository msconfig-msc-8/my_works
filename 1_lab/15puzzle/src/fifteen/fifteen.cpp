#include "fifteen/fifteenpuzzle.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <random>
#include <sstream>
#include <unordered_set>

namespace fifteen {

FifteenPuzzle::FifteenPuzzle(std::size_t size) : size_(size) {
    if (size_ < 2) {
        throw std::invalid_argument("Size must be >= 2");
    }
    ResetSolved();
}

std::size_t FifteenPuzzle::Size() const noexcept {
    return size_;
}

void FifteenPuzzle::ResetSolved() {
    const std::size_t total = size_ * size_;
    cells_.assign(total, 0);

    // Решённое: 1..(N*N-1), 0 в конце
    for (std::size_t i = 0; i + 1 < total; ++i) {
        cells_[i] = static_cast<int>(i + 1);
    }
    cells_[total - 1] = 0;
    emptyIndex_ = total - 1;
}

std::size_t FifteenPuzzle::Index(std::size_t row, std::size_t col) const noexcept {
    return row * size_ + col;
}

std::pair<std::size_t, std::size_t> FifteenPuzzle::Pos(std::size_t index) const noexcept {
    return {index / size_, index % size_};
}

std::pair<std::size_t, std::size_t> FifteenPuzzle::EmptyPos() const noexcept {
    return Pos(emptyIndex_);
}

int FifteenPuzzle::operator[](std::size_t index) const {
    if (index >= cells_.size()) {
        throw std::out_of_range("FifteenPuzzle::operator[] index out of range");
    }
    return cells_[index];
}

bool FifteenPuzzle::IsSolved() const noexcept {
    const std::size_t total = size_ * size_;
    for (std::size_t i = 0; i + 1 < total; ++i) {
        if (cells_[i] != static_cast<int>(i + 1)) {
            return false;
        }
    }
    return cells_[total - 1] == 0;
}

bool FifteenPuzzle::CanMove(Direction dir) const noexcept {
    const auto [r, c] = EmptyPos();
    switch (dir) {
        case Direction::Up:    return r + 1 < size_;
        case Direction::Down:  return r > 0;
        case Direction::Left:  return c + 1 < size_;
        case Direction::Right: return c > 0;
    }
    return false;
}

bool FifteenPuzzle::Move(Direction dir) noexcept {
    if (!CanMove(dir)) {
        return false;
    }

    auto [r, c] = EmptyPos();
    std::size_t nr = r;
    std::size_t nc = c;

    switch (dir) {
        case Direction::Up:    nr = r + 1; break;
        case Direction::Down:  nr = r - 1; break;
        case Direction::Left:  nc = c + 1; break;
        case Direction::Right: nc = c - 1; break;
    }

    const std::size_t neighborIndex = Index(nr, nc);
    std::swap(cells_[emptyIndex_], cells_[neighborIndex]);
    emptyIndex_ = neighborIndex;
    return true;
}

std::vector<Direction> FifteenPuzzle::AvailableMoves() const {
    std::vector<Direction> moves;
    moves.reserve(4);

    if (CanMove(Direction::Up)) moves.push_back(Direction::Up);
    if (CanMove(Direction::Down)) moves.push_back(Direction::Down);
    if (CanMove(Direction::Left)) moves.push_back(Direction::Left);
    if (CanMove(Direction::Right)) moves.push_back(Direction::Right);

    return moves;
}

void FifteenPuzzle::Shuffle(std::uint32_t seed, std::size_t steps) {
    ResetSolved();

    std::mt19937 rng(seed);
    for (std::size_t i = 0; i < steps; ++i) {
        const auto moves = AvailableMoves();
        std::uniform_int_distribution<std::size_t> dist(0, moves.size() - 1);
        Move(moves[dist(rng)]);
    }

    // Чтобы не начать "случайно" решённым после shuffle (редко, но возможно)
    if (IsSolved() && steps > 0) {
        const auto moves = AvailableMoves();
        Move(moves.front());
    }
}

bool FifteenPuzzle::IsValidPermutation_() const {
    const std::size_t total = size_ * size_;
    if (cells_.size() != total) {
        return false;
    }

    std::unordered_set<int> seen;
    seen.reserve(total);

    for (int v : cells_) {
        if (v < 0 || v >= static_cast<int>(total)) {
            return false;
        }
        if (!seen.insert(v).second) {
            return false;
        }
    }
    return seen.size() == total;
}

bool operator==(const FifteenPuzzle& a, const FifteenPuzzle& b) noexcept {
    return a.size_ == b.size_ && a.cells_ == b.cells_;
}

bool operator!=(const FifteenPuzzle& a, const FifteenPuzzle& b) noexcept {
    return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const FifteenPuzzle& p) {
    const std::size_t total = p.size_ * p.size_;
    const int maxValue = static_cast<int>(total - 1);
    const int width = static_cast<int>(std::to_string(maxValue).size());

    for (std::size_t r = 0; r < p.size_; ++r) {
        for (std::size_t c = 0; c < p.size_; ++c) {
            const int v = p.cells_[p.Index(r, c)];
            if (v == 0) {
                os << std::setw(width) << ' ' << ' ';
            } else {
                os << std::setw(width) << v << ' ';
            }
        }
        os << '\n';
    }
    return os;
}

std::istream& operator>>(std::istream& is, FifteenPuzzle& p) {
    const std::size_t total = p.size_ * p.size_;
    std::vector<int> buf(total);

    for (std::size_t i = 0; i < total; ++i) {
        if (!(is >> buf[i])) {
            throw std::runtime_error("Failed to read puzzle cells");
        }
    }

    p.cells_ = std::move(buf);
    if (!p.IsValidPermutation_()) {
        throw std::runtime_error("Invalid puzzle permutation");
    }

    auto it = std::find(p.cells_.begin(), p.cells_.end(), 0);
    p.emptyIndex_ = static_cast<std::size_t>(std::distance(p.cells_.begin(), it));
    return is;
}

} // namespace fifteen
