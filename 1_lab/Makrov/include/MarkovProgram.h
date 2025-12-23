#pragma once

#include "MarkovRule.h"

#include <iosfwd>
#include <string>
#include <vector>

/**
 * @file MarkovProgram.h
 * @brief Программа (набор правил) для нормального алгорифма Маркова.
 */

class MarkovProgram {
public:
    MarkovProgram() = default;

    [[nodiscard]] std::size_t size() const noexcept;
    [[nodiscard]] bool empty() const noexcept;

    [[nodiscard]] const MarkovRule& ruleAt(std::size_t index) const;

    void addRule(const MarkovRule& rule);
    void removeRule(std::size_t index);
    void clear() noexcept;

    /**
     * @brief Загружает правила из потока (по строкам до EOF).
     *        Пустые строки и строки-комментарии игнорируются.
     * @param is входной поток.
     */
    void loadFromStream(std::istream& is);

    friend std::ostream& operator<<(std::ostream& os, const MarkovProgram& program);
    friend std::istream& operator>>(std::istream& is, MarkovProgram& program);

private:
    std::vector<MarkovRule> rules_;
};
