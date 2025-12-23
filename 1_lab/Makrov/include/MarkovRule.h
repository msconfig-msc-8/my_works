#pragma once

#include <iosfwd>
#include <string>

/**
 * @file MarkovRule.h
 * @brief Класс правила нормального алгорифма Маркова.
 */

/**
 * @brief Одно правило Маркова: left -> right или терминальное left ->. right.
 */
class MarkovRule {
public:
    MarkovRule() = default;
    MarkovRule(std::string left, std::string right, bool terminal);

    [[nodiscard]] const std::string& left() const noexcept;
    [[nodiscard]] const std::string& right() const noexcept;
    [[nodiscard]] bool isTerminal() const noexcept;

    /**
     * @brief Парсит правило из одной строки.
     * @param line строка правила.
     * @return распарсенное правило.
     * @throws std::invalid_argument если формат неверный.
     */
    static MarkovRule parse(const std::string& line);

    friend bool operator==(const MarkovRule& a, const MarkovRule& b) noexcept;
    friend bool operator!=(const MarkovRule& a, const MarkovRule& b) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const MarkovRule& rule);
    friend std::istream& operator>>(std::istream& is, MarkovRule& rule);

private:
    std::string left_;
    std::string right_;
    bool terminal_ = false;
};
