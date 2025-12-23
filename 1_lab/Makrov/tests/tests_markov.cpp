#include "MarkovMachine.h"
#include "MarkovProgram.h"
#include "MarkovRule.h"

#include <UnitTest++/UnitTest++.h>

#include <sstream>
#include <stdexcept>

namespace {

MarkovProgram programFromText(const std::string& text) {
    std::istringstream iss(text);
    MarkovProgram p;
    p.loadFromStream(iss);
    return p;
}

} // namespace

// ---------- Rule parsing ----------
TEST(ParseNormalRuleWithSpaces) {
    const auto r = MarkovRule::parse("ab -> ba");
    CHECK_EQUAL("ab", r.left());
    CHECK_EQUAL("ba", r.right());
    CHECK(!r.isTerminal());
}

TEST(ParseTerminalRuleWithSpaces) {
    const auto r = MarkovRule::parse("ab ->. ba");
    CHECK_EQUAL("ab", r.left());
    CHECK_EQUAL("ba", r.right());
    CHECK(r.isTerminal());
}

TEST(ParseNoSpacesNormal) {
    const auto r = MarkovRule::parse("a->b");
    CHECK_EQUAL("a", r.left());
    CHECK_EQUAL("b", r.right());
    CHECK(!r.isTerminal());
}

TEST(ParseNoSpacesTerminal) {
    const auto r = MarkovRule::parse("a->.b");
    CHECK_EQUAL("a", r.left());
    CHECK_EQUAL("b", r.right());
    CHECK(r.isTerminal());
}

TEST(ParseTrimsLeftRight) {
    const auto r = MarkovRule::parse("   a   ->   b   ");
    CHECK_EQUAL("a", r.left());
    CHECK_EQUAL("b", r.right());
}

TEST(ParseRightCanBeEmpty) {
    const auto r = MarkovRule::parse("a -> ");
    CHECK_EQUAL("a", r.left());
    CHECK_EQUAL("", r.right());
}

TEST(ParseFailsWithoutArrow) {
    CHECK_THROW(MarkovRule::parse("abc"), std::invalid_argument);
}

TEST(ParseFailsEmptyLine) {
    CHECK_THROW(MarkovRule::parse("   "), std::invalid_argument);
}

TEST(ParseFailsEmptyLeft) {
    CHECK_THROW(MarkovRule::parse(" -> x"), std::invalid_argument);
}

TEST(StreamOutputNormalRule) {
    const MarkovRule r("a", "b", false);
    std::ostringstream oss;
    oss << r;
    CHECK_EQUAL("a -> b", oss.str());
}

TEST(StreamOutputTerminalRule) {
    const MarkovRule r("a", "b", true);
    std::ostringstream oss;
    oss << r;
    CHECK_EQUAL("a ->. b", oss.str());
}

TEST(StreamInputRuleOk) {
    std::istringstream iss("ab -> ba\n");
    MarkovRule r;
    iss >> r;
    CHECK(iss.good());
    CHECK_EQUAL("ab", r.left());
    CHECK_EQUAL("ba", r.right());
}

TEST(EqualityOperators) {
    const MarkovRule a("x", "y", false);
    const MarkovRule b("x", "y", false);
    const MarkovRule c("x", "y", true);
    CHECK(a == b);
    CHECK(a != c);
}

// ---------- Program ----------
TEST(ProgramLoadIgnoresEmptyLines) {
    const auto p = programFromText("\n\nab -> ba\n\n");
    CHECK_EQUAL(1u, p.size());
}

TEST(ProgramLoadIgnoresHashComments) {
    const auto p = programFromText("# comment\nab -> ba\n");
    CHECK_EQUAL(1u, p.size());
}

TEST(ProgramLoadIgnoresSlashComments) {
    const auto p = programFromText("// comment\nab -> ba\n");
    CHECK_EQUAL(1u, p.size());
}

TEST(ProgramAddRemove) {
    MarkovProgram p;
    p.addRule(MarkovRule("a", "b", false));
    p.addRule(MarkovRule("b", "c", false));
    CHECK_EQUAL(2u, p.size());

    p.removeRule(0);
    CHECK_EQUAL(1u, p.size());
    CHECK_EQUAL("b", p.ruleAt(0).left());
}

TEST(ProgramRemoveOutOfRangeThrows) {
    MarkovProgram p;
    CHECK_THROW(p.removeRule(0), std::out_of_range);
}

TEST(ProgramRuleAtOutOfRangeThrows) {
    MarkovProgram p;
    p.addRule(MarkovRule("a", "b", false));
    CHECK_THROW((void)p.ruleAt(1), std::out_of_range);

}

TEST(ProgramStreamOutput) {
    MarkovProgram p;
    p.addRule(MarkovRule("a", "b", false));
    p.addRule(MarkovRule("b", "c", true));
    std::ostringstream oss;
    oss << p;
    CHECK_EQUAL("a -> b\nb ->. c", oss.str());
}

// ---------- Machine step semantics ----------
TEST(StepAppliesFirstMatchingRule) {
    MarkovProgram p;
    p.addRule(MarkovRule("a", "x", false));
    p.addRule(MarkovRule("ab", "y", false));

    MarkovMachine m(p, "ab");
    const auto applied = m.step();
    CHECK(applied.has_value());
    CHECK_EQUAL("xb", m.word()); // применилось правило 0 ("a" -> "x")
}

TEST(StepReplacesLeftmostOccurrenceOnly) {
    MarkovProgram p;
    p.addRule(MarkovRule("aa", "b", false));
    MarkovMachine m(p, "aaaa");
    (void)m.step();
    CHECK_EQUAL("baa", m.word()); // "aaaa" -> "baa", а не "bb"
}

TEST(StepSetsHaltWhenNoRuleApplicable) {
    MarkovProgram p;
    p.addRule(MarkovRule("x", "y", false));
    MarkovMachine m(p, "abc");
    const auto applied = m.step();
    CHECK(!applied.has_value());
    CHECK(m.isHalted());
}

TEST(TerminalRuleHaltsAfterApply) {
    MarkovProgram p;
    p.addRule(MarkovRule("a", "b", true));
    MarkovMachine m(p, "a");
    const auto applied = m.step();
    CHECK(applied.has_value());
    CHECK_EQUAL("b", m.word());
    CHECK(m.isHalted());
}

TEST(PrefixIncrementDoesStep) {
    MarkovProgram p;
    p.addRule(MarkovRule("a", "b", false));
    MarkovMachine m(p, "a");
    ++m;
    CHECK_EQUAL("b", m.word());
}

TEST(PostfixIncrementReturnsOldCopy) {
    MarkovProgram p;
    p.addRule(MarkovRule("a", "b", false));
    MarkovMachine m(p, "a");
    const MarkovMachine old = m++;
    CHECK_EQUAL("a", old.word());
    CHECK_EQUAL("b", m.word());
}

// ---------- Machine run ----------
TEST(RunStopsWhenNoRuleApplies) {
    MarkovProgram p;
    p.addRule(MarkovRule("a", "b", false));
    MarkovMachine m(p, "a");
    const std::size_t steps = m.run(100, nullptr);
    CHECK_EQUAL(1u, steps);
    CHECK_EQUAL("b", m.word());
    CHECK(m.isHalted());
}

TEST(RunStopsOnTerminalRule) {
    MarkovProgram p;
    p.addRule(MarkovRule("a", "b", true));
    p.addRule(MarkovRule("b", "c", false));
    MarkovMachine m(p, "a");
    const std::size_t steps = m.run(100, nullptr);
    CHECK_EQUAL(1u, steps);
    CHECK_EQUAL("b", m.word());
}

TEST(RunRespectsMaxSteps) {
    MarkovProgram p;
    p.addRule(MarkovRule("a", "aa", false)); // бесконечно растёт
    MarkovMachine m(p, "a");
    const std::size_t steps = m.run(5, nullptr);
    CHECK_EQUAL(5u, steps);
    CHECK(m.isHalted());
}

TEST(RunThrowsOnZeroMaxSteps) {
    MarkovProgram p;
    p.addRule(MarkovRule("a", "b", false));
    MarkovMachine m(p, "a");
    CHECK_THROW(m.run(0, nullptr), std::invalid_argument);
}

TEST(RunProducesLog) {
    MarkovProgram p;
    p.addRule(MarkovRule("ab", "ba", false));
    MarkovMachine m(p, "ab");
    std::ostringstream log;
    (void)m.run(10, &log);
    CHECK(log.str().find("Step 1:") != std::string::npos);
    CHECK(log.str().find("before: \"ab\"") != std::string::npos);
    CHECK(log.str().find("after : \"ba\"") != std::string::npos);
}

// Еще несколько тестов, чтобы точно было 30+
TEST(MultipleStepsSequence) {
    MarkovProgram p;
    p.addRule(MarkovRule("ab", "ba", false));
    p.addRule(MarkovRule("aa", "a", false));
    MarkovMachine m(p, "ababa");
    (void)m.run(100, nullptr);
    CHECK(m.isHalted());
}

TEST(SetWordResetsHalt) {
    MarkovProgram p;
    p.addRule(MarkovRule("x", "y", false));
    MarkovMachine m(p, "abc");
    (void)m.step();
    CHECK(m.isHalted());
    m.setWord("x");
    CHECK(!m.isHalted());
}

TEST(SetProgramResetsHalt) {
    MarkovProgram p1;
    p1.addRule(MarkovRule("x", "y", false));
    MarkovProgram p2;
    p2.addRule(MarkovRule("a", "b", false));

    MarkovMachine m(p1, "nope");
    (void)m.step();
    CHECK(m.isHalted());
    m.setProgram(p2);
    CHECK(!m.isHalted());
}

TEST(StepReturnsAppliedInfo) {
    MarkovProgram p;
    p.addRule(MarkovRule("ab", "x", false));
    MarkovMachine m(p, "ab");
    const auto applied = m.step();
    CHECK(applied.has_value());
    CHECK_EQUAL(0u, applied->ruleIndex);
    CHECK_EQUAL("ab", applied->before);
    CHECK_EQUAL("x", applied->after);
}

TEST(ProgramClear) {
    MarkovProgram p;
    p.addRule(MarkovRule("a", "b", false));
    p.clear();
    CHECK(p.empty());
}

int main() {
    return UnitTest::RunAllTests();
}

