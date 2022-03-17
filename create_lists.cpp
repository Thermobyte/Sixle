#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>

#define MIN_FREQ 1296

// structure denoting a word occurence
// contains the string of the word and an integer representing its frequency
struct word_occ {
    std::string word;
    int occurence;
};

// vector containing all words, filled out in the main method. Will be whittled down by methods below.
std::vector<word_occ> words_vector;

/*
no real english words lack vowels entirely, this function will remove all instances of words in the list that contain zero vowels.
this is designed to remove things like acronyms from the dataset
*/
void remove_vowelless() {
    word_occ ptr;

    // catalogue starting data for analysis purposes
    std::cout << "Removing voweless." << '\n';
    std::cout << "Starting list size is: " << words_vector.size() << '\n';
    int start = words_vector.size();

    // go through each word in the vector
    for (std::vector<word_occ>::iterator it = words_vector.begin(); it != words_vector.end(); ++it) {
        ptr = *it;

        // convert strings into c-strings to check individual characters within them
        const char* wordc = ptr.word.c_str();
        int vowel_check = 0;

        // check for the presence of a vowel
        // if found, stop searching and move on
        for (int i = 0; i < strlen(wordc); i++) {
            if (wordc[i] == 'a' || wordc[i] == 'e' || wordc[i] == 'i' || wordc[i] == 'o' || wordc[i] == 'u' || wordc[i] == 'y') {
                vowel_check = 1;
                break;
            }
        }

        // if no vowels were found, remove that word from the vector, and continue to the next word
        if (vowel_check == 0) {
            words_vector.erase(it);
        } 
    }


    // output how many words remain and the amount of words removed for analysis purposes
    std::cout << "Size after removing vowelless is: " << words_vector.size() << '\n';
    int diff = start - words_vector.size();
    std::cout << "---Removed " << diff << " entries" << '\n' << "==========================================================" << '\n' << '\n';
}

/*
very few, if not zero words in the english language contain instances of the same letter 3 times in a row.
despite that, the dataset contains many instances of just that. Be it in the form of jibberish words like 'aaaaah' or in roman numerals like 'xxxiii',
these words must be removed.
*/
void remove_triple_letters() {
    word_occ ptr;

    // catalogue starting data for analysis purposes
    std::cout << "Removing triple letter occurences." << '\n';
    std::cout << "Starting list size is: " << words_vector.size() << '\n';
    int start = words_vector.size();

    // go through each word in the vector
    for (std::vector<word_occ>::iterator it = words_vector.begin(); it != words_vector.end(); ++it) {
        ptr = *it;

        // convert strings into c-strings to check individual characters within them
        const char* wordc = ptr.word.c_str();

        // create trackers for consecutive letters. One to keep track of the last letter, and a count of the current streak of consecutive letters
        int consecutive_letters = 1;
        char check_letter;
        for (int i = 0; i < strlen(wordc); i++) {
            // if the current letter matches the previous one, increase the count
            if (wordc[i] == check_letter) {
                consecutive_letters++;
                // if that count exceeds three, remove the word and break from the loop
                if (consecutive_letters >= 3) {
                    words_vector.erase(it);
                    break;
                }
            } else { // if the current letter does not match the last one, reset the count
                consecutive_letters = 1;
            }
            // update the previous letter
            check_letter = wordc[i];
        }
    }

    // output how many words remain and the amount of words removed for analysis purposes
    std::cout << "Size after removing words with 3 or more consecutive letters is: " << words_vector.size() << '\n';
    int diff = start - words_vector.size();
    std::cout << "---Removed " << diff << " entries" << '\n' << "==========================================================" << '\n' << '\n';
}

int main() {
    // open txt file containing all words
    std::ifstream all_words_list;
    all_words_list.open("sorted6letters-freq-alph.txt");
    
    std::string line;

    std::string line_word;
    int line_occurence;

    word_occ this_line;

    // parse txt file and put the pieces into a vector of word_occ types
    while (getline(all_words_list, line)) {
        std::istringstream ss(line);
        ss >> line_word;
        ss >> line_occurence;

        // if a word occurs less than MIN_FREQ times, don't add it to the list. This portion will do the vast majority of the list's size reduction
        // MIN_FREQ can be changed to be any number
        // it is set at 1296 because that is the lowest number in which I saw a word that I recognized in the list, but it can otherwise be anything
        // the higher MIN_FREQ is, the fewer words will be in the final list, and a higher percentage of words will be commonly recognized
        if (line_occurence > MIN_FREQ) {
            this_line.word = line_word;
            this_line.occurence = line_occurence;
            words_vector.push_back(this_line);
        }
    }

    // original txt file no longer needed, close it
    all_words_list.close();
    
    // run the other removal methods, this can be added onto if more methods are written
    remove_vowelless();
    remove_triple_letters();

    // output the final list into a new txt file containing only the words separated by newlines
    std::ofstream newfile;
    newfile.open("updated_words_list.txt");
    for (int i = 0; i < words_vector.size(); i++) {
        newfile << words_vector[i].word;
        newfile << "\n";
    }

    // this file is no longer needed, close it
    newfile.close();

    return 0;
}

