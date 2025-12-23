#include "MarkovProgram.h"

#include <algorithm>
#include <cctype>
#include <istream>
#include <ostream>
#include <stdexcept>

namespace {

bool isCommentOrEmpty(const std::string& line) {
    auto it = std::find_if_not(line.begin(), line.end(),
                               [](unsigned char ch) { return std::isspace(ch); });
    if (it == line.end()) {
        return true;
    }

    if (*it == '#') {
        return true;
    }

    // поддержим // комментарии
    if ((line.end() - it) >= 2 && it[0] == '/' && it[1] == '/') {
        return true;
    }

    return false;
}

} // namespace

std::size_t MarkovProgram::size() const noexcept { return rules_.size(); }
bool MarkovProgram::empty() const noexcept { return rules_.empty(); }

const MarkovRule& MarkovProgram::ruleAt(std::size_t index) const {
    if (index >= rules_.size()) {
        throw std::out_of_range("Rule index out of range");
    }
    return rules_[index];
}

void MarkovProgram::addRule(const MarkovRule& rule) { rules_.push_back(rule); }

void MarkovProgram::removeRule(std::size_t index) {
    if (index >= rules_.size()) {
        throw std::out_of_range("Rule index out of range");
    }
    rules_.erase(rules_.begin() + static_cast<std::ptrdiff_t>(index));
}

void MarkovProgram::clear() noexcept { rules_.clear(); }

void MarkovProgram::loadFromStream(std::istream& is) {
    std::string line;
    while (std::getline(is, line)) {
        if (isCommentOrEmpty(line)) {
            continue;
        }
        rules_.push_back(MarkovRule::parse(line));
    }
}

std::ostream& operator<<(std::ostream& os, const MarkovProgram& program) {
    for (std::size_t i = 0; i < program.rules_.size(); ++i) {
        os << program.rules_[i];
        if (i + 1 < program.rules_.size()) {
            os << '\n';
        }
    }
    return os;
}

std::istream& operator>>(std::istream& is, MarkovProgram& program) {
    program.clear();
    program.loadFromStream(is);
    return is;
}
