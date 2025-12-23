#include "MarkovMachine.h"

#include <ostream>
#include <stdexcept>

MarkovMachine::MarkovMachine(MarkovProgram program, std::string word)
    : program_(std::move(program)), word_(std::move(word)) {}

const std::string& MarkovMachine::word() const noexcept { return word_; }

void MarkovMachine::setWord(const std::string& word) {
    word_ = word;
    halted_ = false;
}

const MarkovProgram& MarkovMachine::program() const noexcept { return program_; }

void MarkovMachine::setProgram(const MarkovProgram& program) {
    program_ = program;
    halted_ = false;
}

bool MarkovMachine::isHalted() const noexcept { return halted_; }

std::optional<MarkovAppliedRule> MarkovMachine::tryApplyFirstRule_() {
    for (std::size_t i = 0; i < program_.size(); ++i) {
        const MarkovRule& rule = program_.ruleAt(i);
        const std::size_t pos = word_.find(rule.left());
        if (pos == std::string::npos) {
            continue;
        }

        MarkovAppliedRule applied;
        applied.ruleIndex = i;
        applied.rule = rule;
        applied.before = word_;

        word_.replace(pos, rule.left().size(), rule.right());

        applied.after = word_;
        if (rule.isTerminal()) {
            halted_ = true;
        }
        return applied;
    }

    halted_ = true;
    return std::nullopt;
}

std::optional<MarkovAppliedRule> MarkovMachine::step() {
    if (halted_) {
        return std::nullopt;
    }
    return tryApplyFirstRule_();
}

void MarkovMachine::logStep_(std::ostream& os, std::size_t stepNumber, const MarkovAppliedRule& applied) const {
    os << "Step " << stepNumber << ": rule[" << applied.ruleIndex << "] "
       << applied.rule << '\n';
    os << "  before: \"" << applied.before << "\"\n";
    os << "  after : \"" << applied.after << "\"\n";
}

std::size_t MarkovMachine::run(std::size_t maxSteps, std::ostream* logStream) {
    if (maxSteps == 0) {
        throw std::invalid_argument("maxSteps must be > 0");
    }

    std::size_t stepsDone = 0;
    while (!halted_ && stepsDone < maxSteps) {
        const auto applied = step();
        if (!applied.has_value()) {
            break;
        }

        ++stepsDone;
        if (logStream != nullptr) {
            logStep_(*logStream, stepsDone, *applied);
        }
    }

    // если упёрлись в лимит — тоже считаем остановкой, чтобы не зависнуть
    if (!halted_ && stepsDone >= maxSteps) {
        halted_ = true;
    }

    return stepsDone;
}

MarkovMachine& MarkovMachine::operator++() {
    (void)step();
    return *this;
}

MarkovMachine MarkovMachine::operator++(int) {
    MarkovMachine copy = *this;
    (void)step();
    return copy;
}
