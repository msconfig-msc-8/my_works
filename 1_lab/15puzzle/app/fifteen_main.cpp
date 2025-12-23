#include "fifteen/fifteenpuzzle.h"

#include <cstdint>
#include <iostream>
#include <limits>
#include <string>
#include <random>

using fifteen::Direction;
using fifteen::FifteenPuzzle;

static void PrintHelp() {
    std::cout
        << "Команды:\n"
        << "  n  - новая игра (shuffle)\n"
        << "  w  - вверх\n"
        << "  s  - вниз\n"
        << "  a  - влево\n"
        << "  d  - вправо\n"
        << "  p  - печать поля\n"
        << "  c  - проверить решено ли\n"
        << "  q  - выход\n";
}

static bool TryMoveByChar(FifteenPuzzle& puzzle, char ch) {
    switch (ch) {
        case 'w': return puzzle.Move(Direction::Up);
        case 's': return puzzle.Move(Direction::Down);
        case 'a': return puzzle.Move(Direction::Left);
        case 'd': return puzzle.Move(Direction::Right);
        default: return false;
    }
}

int main() {
    FifteenPuzzle puzzle;

    std::cout << "Пятнашки (" << puzzle.Size() << "x" << puzzle.Size() << ")\n";
    PrintHelp();

    puzzle.Shuffle(12345);
    std::cout << puzzle << '\n';

    while (true) {
        std::cout << "> ";
        std::string cmd;
        if (!(std::cin >> cmd)) {
            return 0;
        }

        if (cmd == "q") {
            break;
        }
        if (cmd == "h") {
            PrintHelp();
            continue;
        }
        if (cmd == "n") {
            puzzle.Shuffle( static_cast<std::uint32_t>(std::random_device{}()) );
            std::cout << puzzle << '\n';
            continue;
        }
        if (cmd == "p") {
            std::cout << puzzle << '\n';
            continue;
        }
        if (cmd == "c") {
            std::cout << (puzzle.IsSolved() ? "РЕШЕНО\n" : "ЕЩЁ НЕТ\n");
            continue;
        }
        if (cmd.size() == 1) {
            const bool moved = TryMoveByChar(puzzle, cmd[0]);
            if (!moved) {
                std::cout << "Ход невозможен.\n";
            }
            std::cout << puzzle << '\n';
            if (puzzle.IsSolved()) {
                std::cout << "Поздравляю! Ты собрал(а) пятнашки.\n";
            }
            continue;
        }

        std::cout << "Неизвестная команда. Введи h для помощи.\n";
    }

    return 0;
}
