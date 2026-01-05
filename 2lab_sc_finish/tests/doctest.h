// doctest.h - single header testing framework
// Version: 2.4.11
// https://github.com/doctest/doctest
//
// This is a minimal header-only testing framework for C++11 and later.

#ifndef DOCTEST_LIBRARY_INCLUDED
#define DOCTEST_LIBRARY_INCLUDED

#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define DOCTEST_VERSION_MAJOR 2
#define DOCTEST_VERSION_MINOR 4
#define DOCTEST_VERSION_PATCH 11

namespace doctest {

struct TestCase {
    const char* name;
    const char* file;
    int line;
    void (*func)();
};

class Context {
private:
    std::vector<TestCase>& getTests() {
        static std::vector<TestCase> tests;
        return tests;
    }
    
    int passed = 0;
    int failed = 0;
    
public:
    static Context& getInstance() {
        static Context instance;
        return instance;
    }
    
    void addTest(const char* name, const char* file, int line, void (*func)()) {
        getTests().push_back({name, file, line, func});
    }
    
    int run() {
        std::cout << "[doctest] Running " << getTests().size() << " test cases\n";
        std::cout << std::string(70, '=') << "\n";
        
        for (const auto& test : getTests()) {
            try {
                test.func();
                passed++;
                std::cout << "[PASSED] " << test.name << "\n";
            } catch (const std::exception& e) {
                failed++;
                std::cout << "[FAILED] " << test.name << "\n";
                std::cout << "         " << e.what() << "\n";
                std::cout << "         " << test.file << ":" << test.line << "\n";
            } catch (...) {
                failed++;
                std::cout << "[FAILED] " << test.name << " (unknown exception)\n";
            }
        }
        
        std::cout << std::string(70, '=') << "\n";
        std::cout << "[doctest] Test cases: " << (passed + failed) 
                  << " | Passed: " << passed 
                  << " | Failed: " << failed << "\n";
        
        return failed > 0 ? 1 : 0;
    }
    
    void check(bool condition, const char* expr, const char* file, int line) {
        if (!condition) {
            std::ostringstream oss;
            oss << "CHECK(" << expr << ") failed at " << file << ":" << line;
            throw std::runtime_error(oss.str());
        }
    }
};

struct TestRegistrar {
    TestRegistrar(const char* name, const char* file, int line, void (*func)()) {
        Context::getInstance().addTest(name, file, line, func);
    }
};

} // namespace doctest

#define DOCTEST_UNIQUE_NAME_LINE2(name, line) name##line
#define DOCTEST_UNIQUE_NAME_LINE(name, line) DOCTEST_UNIQUE_NAME_LINE2(name, line)
#define DOCTEST_UNIQUE_NAME(name) DOCTEST_UNIQUE_NAME_LINE(name, __LINE__)

#define TEST_CASE(name) \
    static void DOCTEST_UNIQUE_NAME(DOCTEST_ANON_FUNC_)(); \
    static doctest::TestRegistrar DOCTEST_UNIQUE_NAME(DOCTEST_ANON_VAR_)( \
        name, __FILE__, __LINE__, &DOCTEST_UNIQUE_NAME(DOCTEST_ANON_FUNC_)); \
    static void DOCTEST_UNIQUE_NAME(DOCTEST_ANON_FUNC_)()

#define CHECK(expr) \
    doctest::Context::getInstance().check((expr), #expr, __FILE__, __LINE__)

#define CHECK_THROWS_AS(expr, extype) \
    do { \
        bool thrown = false; \
        try { expr; } \
        catch (const extype&) { thrown = true; } \
        catch (...) { } \
        doctest::Context::getInstance().check(thrown, #expr " throws " #extype, __FILE__, __LINE__); \
    } while (false)

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN \
    int main() { \
        return doctest::Context::getInstance().run(); \
    }

#endif // DOCTEST_LIBRARY_INCLUDED
