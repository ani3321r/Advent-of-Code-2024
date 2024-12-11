#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std;

vector<string> interchangeNumbers(const vector<string>& data) {
    vector<string> result;

    for (const string& line : data) {
        size_t delimiterPos = line.find('|');
        if (delimiterPos != string::npos) {
            string firstPart = line.substr(0, delimiterPos); 
            string secondPart = line.substr(delimiterPos + 1);
            result.push_back(secondPart + "|" + firstPart);
        } else {
            result.push_back(line);
        }
    }

    return result;
}

vector<string> filterCorrectLines(const vector<string>& below, const vector<string>& swappedLines) {
    vector<string> correct;

    for (const string& line : below) {
        vector<string> pages;
        stringstream ss(line);
        string page;
        while (getline(ss, page, ',')) {
            pages.push_back(page);
        }

        bool isValid = true;
        for (size_t i = 0; i < pages.size() - 1; i++) {
            string key = pages[i] + "|" + pages[i + 1];

            if (find(swappedLines.begin(), swappedLines.end(), key) != swappedLines.end()) {
                isValid = false;
                break;
            }
        }

        if (isValid) {
            correct.push_back(line);
        }
    }

    return correct;
}

int calculateMiddleSum(const vector<string>& correct) {
    int sum = 0;

    for (const string& line : correct) {
        vector<string> pages;
        stringstream ss(line);
        string page;
        while (getline(ss, page, ',')) {
            pages.push_back(page);
        }

        int middleIndex = static_cast<int>(std::floor(pages.size() / 2.0));
        sum += stoi(pages[middleIndex]);
    }

    return sum;
}

int main(){

    #ifndef ONLINE_JUDGE
    freopen("input.txt","r",stdin); 
    freopen("output.txt","w",stdout);
    #endif

    vector<string> lines;
    string input;

    while(getline(cin, input)){
        lines.push_back(input);
    }

    vector<string> rules;
    vector<string> seq_lines;

    bool empty_line = false;

    for(const string& line: lines){
        if(!empty_line && line.empty()){
            empty_line = true;
        } else if(!empty_line){
            rules.push_back(line);
        } else {
            seq_lines.push_back(line);
        }
    }

    vector<string> violated_rules = interchangeNumbers(rules);

    vector<string> correct = filterCorrectLines(seq_lines, violated_rules);

    int sum = calculateMiddleSum(correct);

    cout << sum;

    return 0;
}