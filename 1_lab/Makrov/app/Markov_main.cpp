// #include "MarkovMachine.h"

// #include <fstream>
// #include <iostream>
// #include <string>
// #include <vector>

// namespace {

// bool isLogEnabled(const std::vector<std::string>& args) {
//     for (const auto& a : args) {
//         if (a == "-log") {
//             return true;
//         }
//     }
//     return false;
// }

// bool isCommentOrEmpty(const std::string& line) {
//     std::size_t i = 0;
//     while (i < line.size() && std::isspace(static_cast<unsigned char>(line[i]))) {
//         ++i;
//     }
//     if (i >= line.size()) {
//         return true;
//     }
//     if (line[i] == '#') {
//         return true;
//     }
//     if (i + 1 < line.size() && line[i] == '/' && line[i + 1] == '/') {
//         return true;
//     }
//     return false;
// }

// std::string readInitialWord(std::istream& is) {
//     std::string line;
//     while (std::getline(is, line)) {
//         if (isCommentOrEmpty(line)) {
//             continue;
//         }
//         return line; // начальное слово = первая непустая некомментарийная строка
//     }
//     return {};
// }

// MarkovProgram readProgram(std::istream& is) {
//     MarkovProgram program;
//     program.loadFromStream(is);
//     return program;
// }

// } // namespace

// int main(int argc, char* argv[]) {
//     std::vector<std::string> args;
//     args.reserve(static_cast<std::size_t>(argc));
//     for (int i = 0; i < argc; ++i) {
//         args.emplace_back(argv[i]);
//     }

//     if (argc < 2) {
//         std::cerr << "Usage: " << args[0] << " <path_to_file> [-log]\n";
//         return 1;
//     }

//     const std::string filePath = args[1];
//     const bool logEnabled = isLogEnabled(args);

//     std::ifstream fin(filePath);
//     if (!fin) {
//         std::cerr << "Error: cannot open file: " << filePath << "\n";
//         return 2;
//     }

//     const std::string initialWord = readInitialWord(fin);
//     if (initialWord.empty()) {
//         std::cerr << "Error: file does not contain initial word\n";
//         return 3;
//     }

//     MarkovProgram program = readProgram(fin);
//     if (program.empty()) {
//         std::cerr << "Error: program has no rules\n";
//         return 4;
//     }

//     MarkovMachine machine(std::move(program), initialWord);
//     machine.run(MarkovMachine::kDefaultMaxSteps, logEnabled ? &std::cout : nullptr);

//     std::cout << "Result: \"" << machine.word() << "\"\n";
//     return 0;
// }





#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <filesystem>
#include <limits>

#include "MarkovMachine.h"
#include "MarkovProgram.h"
#include "MarkovRule.h"

namespace fs = std::filesystem;

static fs::path detectProjectRoot() {
    // Хотим писать файлы в корень проекта, даже если запуск из build/
    fs::path cwd = fs::current_path();

    auto looksLikeRoot = [](const fs::path& p) {
        return fs::exists(p / "include") && fs::exists(p / "src");
    };

    if (looksLikeRoot(cwd)) return cwd;
    if (cwd.has_parent_path() && looksLikeRoot(cwd.parent_path())) return cwd.parent_path();
    return cwd; // fallback
}

static void printMenu() {
    std::cout << "\n=== Markov CLI ===\n"
              << "1) Ввести правила\n"
              << "2) Ввести слово\n"
              << "3) Запустить\n"
              << "4) Показать текущее\n"
              << "0) Выход\n"
              << "Выбор: ";
}

static void inputRules(MarkovProgram& program) {
    program = MarkovProgram{}; // сброс
    std::cout << "\nВводи правила (по одному на строку).\n"
              << "Формат:  a -> ab\n"
              << "Терминальное: b ->. a   (останавливает)\n"
              << "Пустая строка = закончить ввод правил.\n\n";

    std::string line;
    while (true) {
        std::cout << "rule> ";
        if (!std::getline(std::cin, line)) break;

        if (line.empty()) {
            break;
        }

        try {
            program.addRule(MarkovRule::parse(line));
        } catch (const std::exception& e) {
            std::cout << "  [ошибка] " << e.what() << "\n";
        }
    }

    std::cout << "Готово. Правил: " << program.size() << "\n";
}

static void inputWord(std::string& word) {
    std::cout << "\nВведи начальное слово (одной строкой):\nword> ";
    std::getline(std::cin, word);
    std::cout << "Ок. Слово: \"" << word << "\"\n";
}

struct RunOutcome {
    enum class Status { Halted, LoopDetected, StepLimit };
    Status status{};
    std::size_t stepsDone{};
    std::string finalWord;
    std::size_t loopAtStep{}; // если loop
};

static RunOutcome runWithLogAndLoopDetect(MarkovMachine& machine,
                                         std::size_t maxSteps,
                                         std::ostream& log) {
    RunOutcome out{};
    std::unordered_set<std::string> seen;
    seen.reserve(1024);

    std::size_t stepNumber = 0;

    while (!machine.isHalted() && stepNumber < maxSteps) {
        // Детекция детерминированного цикла: слово повторилось -> дальше будет бесконечно
        const std::string& current = machine.word();
        if (!seen.insert(current).second) {
            out.status = RunOutcome::Status::LoopDetected;
            out.stepsDone = stepNumber;
            out.finalWord = current;
            out.loopAtStep = stepNumber;
            log << "LOOP DETECTED at step " << stepNumber
                << " (word repeated): \"" << current << "\"\n";
            return out;
        }

        auto applied = machine.step();
        if (!applied.has_value()) {
            break;
        }

        ++stepNumber;

        // Лог как у тебя раньше (-log)
        log << "Step " << stepNumber << ": rule[" << applied->ruleIndex << "] "
            << applied->rule << '\n';
        log << "  before: \"" << applied->before << "\"\n";
        log << "  after : \"" << applied->after << "\"\n";

        // чтобы файл обновлялся даже если ты прервёшь процесс
        if ((stepNumber % 50) == 0) {
            log.flush();
        }
    }

    out.stepsDone = stepNumber;
    out.finalWord = machine.word();

    if (!machine.isHalted() && stepNumber >= maxSteps) {
        out.status = RunOutcome::Status::StepLimit;
        log << "STEP LIMIT reached: " << maxSteps << "\n";
    } else {
        out.status = RunOutcome::Status::Halted;
    }

    return out;
}

static void showCurrent(const MarkovProgram& program, const std::string& word) {
    std::cout << "\n--- Текущее ---\n";
    std::cout << "Правил: " << program.size() << "\n";
    for (std::size_t i = 0; i < program.size(); ++i) {
        std::cout << "  [" << i << "] " << program.ruleAt(i) << "\n";
    }
    std::cout << "Слово: \"" << word << "\"\n";
}

int main() {
    MarkovProgram program;
    std::string word;

    while (true) {
        printMenu();

        int choice = -1;
        if (!(std::cin >> choice)) {
            return 0;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 0) {
            std::cout << "Выход.\n";
            return 0;
        }

        if (choice == 1) {
            inputRules(program);
        } else if (choice == 2) {
            inputWord(word);
        } else if (choice == 4) {
            showCurrent(program, word);
        } else if (choice == 3) {
            if (program.size() == 0) {
                std::cout << "Сначала введи правила (пункт 1).\n";
                continue;
            }
            if (word.empty()) {
                std::cout << "Сначала введи слово (пункт 2).\n";
                continue;
            }

            std::size_t maxSteps = 10000;
            std::cout << "Лимит шагов (enter = 10000): ";
            std::string s;
            std::getline(std::cin, s);
            if (!s.empty()) {
                try {
                    maxSteps = static_cast<std::size_t>(std::stoull(s));
                    if (maxSteps == 0) maxSteps = 10000;
                } catch (...) {
                    std::cout << "Ок, оставляю 10000.\n";
                    maxSteps = 10000;
                }
            }

            fs::path root = detectProjectRoot();
            fs::path logPath = root / "log.txt";
            fs::path resultPath = root / "result.txt";

            std::ofstream logFile(logPath, std::ios::out | std::ios::trunc);
            if (!logFile) {
                std::cout << "Не могу создать log.txt по пути: " << logPath.string() << "\n";
                continue;
            }

            MarkovMachine machine(program, word);

            std::cout << "Запуск... лог -> " << logPath.string()
                      << ", результат -> " << resultPath.string() << "\n";

            RunOutcome out = runWithLogAndLoopDetect(machine, maxSteps, logFile);

            std::ofstream resFile(resultPath, std::ios::out | std::ios::trunc);
            if (resFile) {
                resFile << "Initial: \"" << word << "\"\n";
                resFile << "Steps: " << out.stepsDone << "\n";
                resFile << "Final: \"" << out.finalWord << "\"\n";
                if (out.status == RunOutcome::Status::Halted) {
                    resFile << "Status: HALTED\n";
                } else if (out.status == RunOutcome::Status::LoopDetected) {
                    resFile << "Status: LOOP DETECTED\n";
                } else {
                    resFile << "Status: STEP LIMIT\n";
                }
            }

            if (out.status == RunOutcome::Status::Halted) {
                std::cout << "Готово. Остановилось нормально. Итог: \"" << out.finalWord << "\"\n";
            } else if (out.status == RunOutcome::Status::LoopDetected) {
                std::cout << "ВНИМАНИЕ: цикл (слово повторилось). Итог на момент детекта: \""
                          << out.finalWord << "\"\n";
            } else {
                std::cout << "ВНИМАНИЕ: достигнут лимит шагов " << maxSteps
                          << ". Итог: \"" << out.finalWord << "\"\n";
            }
        } else {
            std::cout << "Неизвестный пункт.\n";
        }
    }
}
