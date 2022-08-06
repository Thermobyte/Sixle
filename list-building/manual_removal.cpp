#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>

std::vector<std::string> words_list;
std::vector<std::string> rejected_words;

int display_word(int cur_index) {
    std::string cur_word;
    cur_word = words_list[cur_index];
    std::string input;

    std::cout << "WORD IS:\n" << cur_word << "\nKeep? (y/n)\n";
    std::cin >> input;
    std::cout << "\n";
    if (input == "y") {
        std::cout << "Word kept\n";
        return 0; // 0 denotes a word's allowance
    } else if (input == "n") {
        std::cout << "Word dismissed\n";
        return 1; // 1 denotes a word's removal
    } else if (input == "q") {
        std::cout << "Exit Program, saving progress...\n";
        return 2;
    } else {
        std::cout << "Unrecognized input: " << input << "please try again\n";
        return display_word(cur_index);
    }
}

int main() {
    // be sure to set index before calling display_word
    // initialize words_list and rejected_words with corresponding text files before starting
    std::ifstream allowed_words;
    allowed_words.open("updated_words_list.txt");
    std::string line, clean_line;

    while (getline(allowed_words, line)) {
        std::istringstream ss(line);
        ss >> clean_line;

        words_list.push_back(clean_line);
    }

    allowed_words.close();
    
    // open previous session's removed words list, empty its contents into a vector, and delete it to be overwritten later
    std::ifstream removed_words;
    removed_words.open("removed_words_list.txt");
    std::string rem_line, rem_clean_line;

    while (getline(removed_words, rem_line)) {
        std::istringstream rem_ss(rem_line);
        rem_ss >> rem_clean_line;

        rejected_words.push_back(clean_line);
    }

    removed_words.close();
    remove("removed_words_list.txt");

    // TODO: remember to delete line_number and then update it upon quitting
    std::ifstream num_file;
    num_file.open("line_number.tmp");
    int line_number;
    num_file >> line_number;
    remove("line_number.tmp");


    while(line_number < words_list.size()) {
        int rejection = display_word(line_number);
        if (rejection == 1) {
            rejected_words.push_back(words_list[line_number]);
        } else if (rejection == 2) {
            // add rejected words back to list and update line counter
            std::ofstream reject_newfile;
            reject_newfile.open("removed_words_list.txt");
            for (int i = 0; i < rejected_words.size(); ++i) {
                reject_newfile << rejected_words[i];
                reject_newfile << "\n";
            }

            std::ofstream new_line_number;
            new_line_number.open("line_number.tmp");
            new_line_number << line_number;
            new_line_number.close();
            std::cout << "Program state saved, closing\n";
            break;
        }
        line_number++;
    }

    return 0;
}