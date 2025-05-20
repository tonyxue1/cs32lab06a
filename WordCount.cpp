#include "WordCount.h"
#include <cctype>
#include <algorithm>

using namespace std;

WordCount::WordCount() {
    // No special initialization needed; table is statically defined
}

// Hash function — do not modify
size_t WordCount::hash(string word) const {
    size_t accumulator = 0;
    for (size_t i = 0; i < word.size(); i++) {
        accumulator += word.at(i);
    }
    return accumulator % CAPACITY;
}


int WordCount::getTotalWords() const {
    int total = 0;
    for (size_t i = 0; i < CAPACITY; ++i) {
        for (const auto& entry : table[i]) {
            total += entry.second;
        }
    }
    return total;
}


int WordCount::getNumUniqueWords() const {
    int count = 0;
    for (size_t i = 0; i < CAPACITY; ++i) {
        count += table[i].size();
    }
    return count;
}

int WordCount::getWordCount(string word) const {
    word = makeValidWord(word);
    if (word.empty()) return 0;

    size_t index = hash(word);
    const auto& bucket = table[index];
    for (const auto& entry : bucket) {
        if (entry.first == word) {
            return entry.second;
        }
    }
    return 0;
}


int WordCount::incrWordCount(string word) {
    word = makeValidWord(word);
    if (word.empty()) return 0;

    size_t index = hash(word);
    auto& bucket = table[index];
    for (auto& entry : bucket) {
        if (entry.first == word) {
            ++entry.second;
            return entry.second;
        }
    }

    bucket.push_back(make_pair(word, 1));
    return 1;
}


int WordCount::decrWordCount(string word) {
    word = makeValidWord(word);
    if (word.empty()) return -1;

    size_t index = hash(word);
    auto& bucket = table[index];
    for (auto it = bucket.begin(); it != bucket.end(); ++it) {
        if (it->first == word) {
            if (it->second > 1) {
                --(it->second);
                return it->second;
            } else {
                bucket.erase(it);
                return 0;
            }
        }
    }
    return -1;
}


bool WordCount::isWordChar(char c) {
    return isalpha(static_cast<unsigned char>(c));
}


string WordCount::makeValidWord(string word) {
    string result;
    for (char c : word) {
        if (isalpha(static_cast<unsigned char>(c)) || c == '-' || c == '\'') {
            result += tolower(static_cast<unsigned char>(c));
        }
    }

    
    while (!result.empty() && !isalpha(result.front()))
        result.erase(result.begin());
    while (!result.empty() && !isalpha(result.back()))
        result.pop_back();

    return result;
}
