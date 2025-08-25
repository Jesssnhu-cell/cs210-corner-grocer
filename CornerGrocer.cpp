// Corner Grocer – CS210 Project 3
// Single-file version that compiles without precompiled headers.

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits>
#include <stdexcept>

class ItemTracker {
private:
    std::map<std::string, int> freq_;
    std::string inputFile_;

public:
    explicit ItemTracker(const std::string& inputFile) : inputFile_(inputFile) {}

    void Load() {
        std::ifstream in(inputFile_);
        if (!in.is_open()) {
            throw std::runtime_error("Unable to open input file: " + inputFile_);
        }
        std::string word;
        while (in >> word) {
            ++freq_[word];
        }
        in.close();
    }

    void WriteFrequencyFile(const std::string& outFile = "frequency.dat") const {
        std::ofstream out(outFile);
        if (!out.is_open()) {
            throw std::runtime_error("Unable to create output file: " + outFile);
        }
        for (const auto& p : freq_) {
            out << p.first << ' ' << p.second << '\n';
        }
        out.close();
    }

    int CountOf(const std::string& item) const {
        auto it = freq_.find(item);
        return (it == freq_.end()) ? 0 : it->second;
    }

    void PrintAll(std::ostream& os) const {
        if (freq_.empty()) {
            os << "No items found in input file.\n";
            return;
        }
        for (const auto& p : freq_) {
            os << p.first << ' ' << p.second << '\n';
        }
    }

    void PrintHistogram(std::ostream& os, char symbol = '*') const {
        if (freq_.empty()) {
            os << "No items found in input file.\n";
            return;
        }
        for (const auto& p : freq_) {
            os << p.first << ' ' << std::string(p.second, symbol) << '\n';
        }
    }
};

int GetMenuChoice() {
    int choice;
    while (true) {
        std::cout << "\n======= Corner Grocer Menu =======\n";
        std::cout << "1. Look up frequency for a specific item\n";
        std::cout << "2. Print all items with frequencies\n";
        std::cout << "3. Print histogram\n";
        std::cout << "4. Exit\n";
        std::cout << "Select an option (1-4): ";

        if (std::cin >> choice && choice >= 1 && choice <= 4) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return choice;
        }
        std::cout << "Invalid selection. Please enter 1, 2, 3, or 4.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    const std::string kInputFile = "CS210_Project_Three_Input_File.txt";

    try {
        ItemTracker tracker(kInputFile);
        tracker.Load();
        tracker.WriteFrequencyFile();

        while (true) {
            int choice = GetMenuChoice();

            if (choice == 1) {
                std::cout << "Enter the item name to search: ";
                std::string item;
                std::getline(std::cin, item);
                if (item.empty()) {
                    std::cout << "No item entered. Try again.\n";
                    continue;
                }
                int count = tracker.CountOf(item);
                std::cout << item << " " << count << '\n';
            }
            else if (choice == 2) {
                tracker.PrintAll(std::cout);
            }
            else if (choice == 3) {
                tracker.PrintHistogram(std::cout, '*');
            }
            else if (choice == 4) {
                std::cout << "Goodbye!\n";
                break;
            }
        }
    }
    catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << '\n';
        std::cerr << "Tip: Ensure '" << kInputFile
            << "' is in the working directory (Project folder) and not open in another program.\n";
        return 1;
    }

    return 0;
}
