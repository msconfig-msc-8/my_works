#include "MarkovRule.h"

#include <algorithm>
#include <cctype>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdexcept>

namespace {

std::string trimCopy(const std::string& s) {
    auto first = std::find_if_not(s.begin(), s.end(),
                                 [](unsigned char ch) { return std::isspace(ch); });
    auto last = std::find_if_not(s.rbegin(), s.rend(),
                                [](unsigned char ch) { return std::isspace(ch); }).base();
    if (first >= last) {
        return {};
    }
    return std::string(first, last);
}

} // namespace

MarkovRule::MarkovRule(std::string left, std::string right, bool terminal)
    : left_(std::move(left)), right_(std::move(right)), terminal_(terminal) {}

const std::string& MarkovRule::left() const noexcept { return left_; }
const std::string& MarkovRule::right() const noexcept { return right_; }
bool MarkovRule::isTerminal() const noexcept { return terminal_; }

MarkovRule MarkovRule::parse(const std::string& line) {
    const std::string cleanLine = trimCopy(line);
    if (cleanLine.empty()) {
        throw std::invalid_argument("Empty rule line");
    }

    // Сначала ищем терминальную стрелку, чтобы не перепутать с обычной "->"
    const std::string terminalArrow = "->.";
    const std::string normalArrow = "->";

    bool terminal = false;
    std::size_t arrowPos = cleanLine.find(terminalArrow);
    std::size_t arrowLen = 0;

    if (arrowPos != std::string::npos) {
        terminal = true;
        arrowLen = terminalArrow.size();
    } else {
        arrowPos = cleanLine.find(normalArrow);
        if (arrowPos == std::string::npos) {
            throw std::invalid_argument("Rule must contain '->' or '->.'");
        }
        arrowLen = normalArrow.size();
    }

    const std::string leftPart = trimCopy(cleanLine.substr(0, arrowPos));
    const std::string rightPart = trimCopy(cleanLine.substr(arrowPos + arrowLen));

    if (leftPart.empty()) {
        // Пустая левая часть теоретически возможна, но в учебной реализации это почти гарантированный бесконечный цикл.
        throw std::invalid_argument("Left side must be non-empty");
    }

    return MarkovRule(leftPart, rightPart, terminal);
}

bool operator==(const MarkovRule& a, const MarkovRule& b) noexcept {
    return a.left_ == b.left_ && a.right_ == b.right_ && a.terminal_ == b.terminal_;
}

bool operator!=(const MarkovRule& a, const MarkovRule& b) noexcept {
    return !(a == b);
}

std::ostream& operator<<(std::ostream& os, const MarkovRule& rule) {
    os << rule.left_;
    os << (rule.terminal_ ? " ->. " : " -> ");
    os << rule.right_;
    return os;
}

std::istream& operator>>(std::istream& is, MarkovRule& rule) {
    // Оператор >> читает ОДНУ строку-правило
    std::string line;
    if (!std::getline(is, line)) {
        return is;
    }

    try {
        rule = MarkovRule::parse(line);
    } catch (...) {
        is.setstate(std::ios::failbit);
    }

    return is;
}
