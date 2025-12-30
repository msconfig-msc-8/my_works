#include "ConsoleMenu.hpp"
#include "sn/sn.hpp"
#include <limits>

namespace sn::cli {

void ConsoleMenu::run() {
  while (true) {
    std::cout << "\n=== Social Network (Lab 2) ===\n";
    std::cout << "Version: " << sn::version() << "\n\n";
    std::cout << "1) Show placeholder info\n";
    std::cout << "0) Exit\n";
    std::cout << "Select: ";

    int choice = -1;
    if (!(std::cin >> choice)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid input.\n";
      continue;
    }

    if (choice == 0) {
      std::cout << "Bye!\n";
      return;
    }

    if (choice == 1) {
      std::cout << "Project scaffold is ready. Next step: add domain/services/storage.\n";
      continue;
    }

    std::cout << "Unknown option.\n";
  }
}

} // namespace sn::cli
