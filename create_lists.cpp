#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// structure denoting a word occurence
// contains the string of the word and an integer representing its frequency
struct word_occ {
    string word;
    int occurence;
};

vector<word_occ> words_vector;

// since the list contains all combinations of 6 letters, some combinations are acronyms
// this method will attempt to remove a large portion of those acronyms by removing words that lack vowels
void remove_vowelless() {
    word_occ ptr;
    cout << "Removing voweless." << endl;
    cout << "Starting list size is: " << words_vector.size() << endl;
    int start = words_vector.size();

    for (vector<word_occ>::iterator it = words_vector.begin(); it != words_vector.end(); ++it) {
        ptr = *it;
        const char* wordc = ptr.word.c_str();
        int vowel_check = 0;
        for (int i = 0; i < strlen(wordc); i++) {
            if (wordc[i] == 'a' || wordc[i] == 'e' || wordc[i] == 'i' || wordc[i] == 'o' || wordc[i] == 'u' || wordc[i] == 'y') {
                vowel_check = 1;
            }
        }
        if (vowel_check == 0) {
            words_vector.erase(it);
        } 
    }

    cout << "Size after removing vowelless is: " << words_vector.size() << endl;
    int diff = start - words_vector.size();
    cout << "---Removed " << diff << " entries" << endl << "==========================================================" << endl << endl;
}

void remove_triple_letters() {
    word_occ ptr;
    cout << "Removing triple letter occurences." << endl;
    cout << "Starting list size is: " << words_vector.size() << endl;
    int start = words_vector.size();

    for (vector<word_occ>::iterator it = words_vector.begin(); it != words_vector.end(); ++it) {
        ptr = *it;
        const char* wordc = ptr.word.c_str();
        int consecutive_letters = 1;
        char check_letter;
        for (int i = 0; i < strlen(wordc); i++) {
            if (wordc[i] == check_letter) {
                consecutive_letters++;
                if (consecutive_letters >= 3) {
                    words_vector.erase(it);
                    break;
                }
            } else {
                consecutive_letters = 1;
            }
            check_letter = wordc[i];
        }
    }

    cout << "Size after removing words with 3 or more consecutive letters is: " << words_vector.size() << endl;
    int diff = start - words_vector.size();
    cout << "---Removed " << diff << " entries" << endl << "==========================================================" << endl << endl;
}

int main() {
    /*
    File is a .txt file that has the following format:
    word1 #####
    word2 #####

    where word is the word from the english 1-grams from google books
    and ##### is the number of occurences.
    The word is separated from it's occurences by a tab (\t) and other words by a newline (\n).
    All words are entirely lowercase, and all numbers are integers lower than 20,000,000
    */

    ifstream all_words_list;
    all_words_list.open("sorted6letters-freq-alph.txt");
    
    string line;

    string line_word;
    int line_occurence;

    word_occ this_line;

    while (getline(all_words_list, line)) {
        istringstream ss(line);
        ss >> line_word;
        ss >> line_occurence;

        if (line_occurence > 1296) {
            this_line.word = line_word;
            this_line.occurence = line_occurence;
            words_vector.push_back(this_line);
        }
    }

    
    // COMMMENTED OUT SECTIONS BELOW ARE FOR TESTING PURPOSES
    
    remove_vowelless();
    remove_triple_letters();

    ofstream newfile;
    newfile.open("updated_words_list.txt");
    for (int i = 0; i < words_vector.size(); i++) {
        newfile << words_vector[i].word;
        newfile << "\n";
    }

    newfile.close();

    // for (int i = 0; i < 200; i++) {
    //     getline(all_words_list, line);
    //     istringstream ss(line);
    //     ss >> line_word;
    //     ss >> line_occurence;

    //     this_line.word = line_word;
    //     this_line.occurence = line_occurence;
    //     words_vector.push_back(this_line);
    // }

    // while (!words_vector.empty()) {
    //     cout << words_vector.back().word << " " << words_vector.back().occurence << endl;
    //     words_vector.pop_back();
    // }
    return 0;
}

