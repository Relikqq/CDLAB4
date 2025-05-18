#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>

using namespace std;

// Проверка, можно ли составить слово из букв базового слова
bool canFormWord(const string& word, const unordered_map<char, int>& baseFreq) {
    unordered_map<char, int> wordFreq = getLetterFreq(word);
    for (const auto& pair : wordFreq) {
        char ch = pair.first;
        int count = pair.second;
        if (baseFreq.find(ch) == baseFreq.end() || count > baseFreq.at(ch)) {
            return false;
        }
    }

    return true;
}

// Частота букв в слове
unordered_map<char, int> getLetterFreq(const string& word) {
    unordered_map<char, int> freq;
    for (char ch : word) {
        if (isalpha((unsigned char)ch)) {
            freq[ch]++;
        }
    }
    return freq;
}


int main() {
    string dictFile = "nouns.txt";
    ifstream file(dictFile);
    if (!file.is_open()) {
        cerr << "The dictionary file could not be opened." << endl;
        return 1;
    }

    // Считывание словаря
    vector<string> dictionary;
    string word;
    while (getline(file, word)) {
        dictionary.push_back(word);
    }
    file.close();

    // Основной цикл: пользователь вводит слово
    string text;
    cout << "Enter the word: ";
    cin >> text;

    auto start = chrono::steady_clock::now();

    unordered_map<char, int> inputFreq = getLetterFreq(text);
    vector<string> result;

    for (const string& dictWord : dictionary) {
        if (canFormWord(dictWord, inputFreq)) {
            result.push_back(dictWord);
        }
    }

    // Сортировка по убыванию длины
    sort(result.begin(), result.end(), [](const string& a, const string& b) {
        return a.length() > b.length();
        });

    auto end = chrono::steady_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << "Result (found " << result.size() << " words):\n";
    for (const string& w : result) {
        cout << w << endl;
    }

    cerr << "Processing took " << elapsed.count() << " seconds.\n";
    return 0;
}
