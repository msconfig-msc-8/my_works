#pragma once

#include "MarkovProgram.h"

#include <cstddef>
#include <iosfwd>
#include <optional>
#include <string>

/**
 * @file MarkovMachine.h
 * @brief Интерпретатор нормальных алгорифмов Маркова.
 */

struct MarkovAppliedRule {
    std::size_t ruleIndex = 0;
    MarkovRule rule;
    std::string before;
    std::string after;
};

/**
 * @brief Машина Маркова: хранит текущее слово и программу, умеет делать шаг и запускать интерпретацию.
 */
class MarkovMachine {
public:
    static constexpr std::size_t kDefaultMaxSteps = 10000;

    MarkovMachine() = default;
    MarkovMachine(MarkovProgram program, std::string word);

    [[nodiscard]] const std::string& word() const noexcept;
    void setWord(const std::string& word);

    [[nodiscard]] const MarkovProgram& program() const noexcept;
    void setProgram(const MarkovProgram& program);

    [[nodiscard]] bool isHalted() const noexcept;

    /**
     * @brief Делает один шаг. Применяет первое подходящее правило и заменяет самое левое вхождение.
     * @return информация о применённом правиле или std::nullopt, если правила не применимы.
     */
    std::optional<MarkovAppliedRule> step();

    /**
     * @brief Запускает интерпретацию до остановки.
     * @param maxSteps ограничение шагов, чтобы не зависнуть.
     * @param logStream если не nullptr, печатает лог после каждого шага.
     * @return количество выполненных шагов.
     */
    std::size_t run(std::size_t maxSteps = kDefaultMaxSteps, std::ostream* logStream = nullptr);

    // Шаг через оператор ++ (удобно как в задании)
    MarkovMachine& operator++();     // prefix
    MarkovMachine operator++(int);   // postfix

private:
    std::optional<MarkovAppliedRule> tryApplyFirstRule_();
    void logStep_(std::ostream& os, std::size_t stepNumber, const MarkovAppliedRule& applied) const;

    MarkovProgram program_;
    std::string word_;
    bool halted_ = false;
};
