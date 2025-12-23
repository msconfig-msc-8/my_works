


/**
 * @file fifteenpuzzle.h
 * @brief Класс головоломки "Пятнашки" (Fifteen Puzzle).
 *
 * Реализует поле NxN, перемешивание, ходы, проверку решения и доступ к клетке через operator[].
 */

#pragma once

#include <cstddef>
#include <cstdint>
#include <iosfwd>
#include <stdexcept>
#include <utility>
#include <vector>

namespace fifteen {

/**
 * @brief Направление хода пустой клетки.
 *
 * Направление относится к перемещению "пустой" клетки (0).
 */
enum class Direction {
    Up,    ///< Пустая клетка двигается вверх (меняется местами с клеткой снизу).
    Down,  ///< Пустая клетка двигается вниз (меняется местами с клеткой сверху).
    Left,  ///< Пустая клетка двигается влево (меняется местами с клеткой справа).
    Right  ///< Пустая клетка двигается вправо (меняется местами с клеткой слева).
};

/**
 * @brief Реализация игры-головоломки "Пятнашки" (NxN).
 *
 * В решённом состоянии элементы расположены так:
 * 1..(N*N-1), а 0 (пустая клетка) стоит в конце.
 *
 * Перемешивание делается последовательностью случайных корректных ходов,
 * поэтому полученное состояние всегда достижимо (решаемо).
 */
class FifteenPuzzle final {
public:
    /// @brief Размер поля по умолчанию (4x4).
    static constexpr std::size_t kDefaultSize = 4;

    /// @brief Количество случайных ходов при перемешивании по умолчанию.
    static constexpr std::size_t kDefaultShuffleSteps = 300;

    /**
     * @brief Создаёт поле размера size x size в решённом состоянии.
     * @param size Размер стороны поля (N). Должен быть >= 2.
     * @throw std::invalid_argument если size < 2.
     */
    explicit FifteenPuzzle(std::size_t size = kDefaultSize);

    FifteenPuzzle(const FifteenPuzzle&) = default;
    FifteenPuzzle& operator=(const FifteenPuzzle&) = default;
    ~FifteenPuzzle() = default;

    /**
     * @brief Возвращает размер стороны поля (N).
     * @return N.
     */
    std::size_t Size() const noexcept;

    /**
     * @brief Сбрасывает поле в решённое состояние.
     */
    void ResetSolved();

    /**
     * @brief Перемешивает поле случайными допустимыми ходами.
     * @param seed Зерно генератора случайных чисел (для повторяемости).
     * @param steps Сколько случайных ходов выполнить.
     */
    void Shuffle(std::uint32_t seed, std::size_t steps = kDefaultShuffleSteps);

    /**
     * @brief Проверяет, решена ли головоломка.
     * @return true если поле в решённом состоянии, иначе false.
     */
    bool IsSolved() const noexcept;

    /**
     * @brief Доступ к клетке по линейному индексу.
     *
     * Индекс считается слева направо, сверху вниз: 0..(N*N-1).
     *
     * @param index Линейный индекс.
     * @return Значение в клетке (0 означает пустую клетку).
     * @throw std::out_of_range если index вне диапазона.
     */
    int operator[](std::size_t index) const;

    /**
     * @brief Проверяет, можно ли сделать ход в данном направлении.
     * @param dir Направление хода.
     * @return true если ход возможен, иначе false.
     */
    bool CanMove(Direction dir) const noexcept;

    /**
     * @brief Делает ход (меняет местами пустую клетку с соседней).
     * @param dir Направление хода.
     * @return true если ход выполнен, иначе false.
     */
    bool Move(Direction dir) noexcept;

    /**
     * @brief Возвращает координаты пустой клетки.
     * @return Пара (row, col), где row и col начинаются с 0.
     */
    std::pair<std::size_t, std::size_t> EmptyPos() const noexcept;

    /**
     * @brief Сравнение двух состояний поля.
     * @return true если состояния идентичны.
     */
    friend bool operator==(const FifteenPuzzle& a, const FifteenPuzzle& b) noexcept;

    /**
     * @brief Сравнение на неравенство.
     * @return true если состояния различаются.
     */
    friend bool operator!=(const FifteenPuzzle& a, const FifteenPuzzle& b) noexcept;

    /**
     * @brief Печатает поле в поток вывода.
     * @param os Поток вывода.
     * @param p Игра.
     * @return os.
     */
    friend std::ostream& operator<<(std::ostream& os, const FifteenPuzzle& p);

    /**
     * @brief Считывает поле из потока ввода.
     *
     * Формат: N*N целых чисел подряд (0 — пустая клетка).
     *
     * @param is Поток ввода.
     * @param p Игра, в которую записывается состояние.
     * @return is.
     * @throw std::runtime_error если данные некорректны (не перестановка 0..N*N-1).
     */
    friend std::istream& operator>>(std::istream& is, FifteenPuzzle& p);

private:
    std::size_t size_{};
    std::vector<int> cells_;
    std::size_t emptyIndex_{};

    /// @brief Перевод координат (row,col) в линейный индекс.
    std::size_t Index(std::size_t row, std::size_t col) const noexcept;

    /// @brief Перевод линейного индекса в координаты (row,col).
    std::pair<std::size_t, std::size_t> Pos(std::size_t index) const noexcept;

    /// @brief Возвращает список возможных ходов из текущего состояния.
    std::vector<Direction> AvailableMoves() const;

    /// @brief Проверяет, что cells_ — корректная перестановка 0..N*N-1.
    bool IsValidPermutation_() const;
};

} // namespace fifteen
