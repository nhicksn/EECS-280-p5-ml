// Project UID db1f506d06d84ab787baf250c265e24e

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <map>
#include <vector>
#include <sstream>
#include <string.h>
#include "csvstream.h"
#include <set>
#include <cmath>

using namespace std;

set<string> unique_words(const string &str) {
    istringstream source(str);
    set<string> words;
    string word;
    while (source >> word) {
        words.insert(word);
    }
    return words;
}

class Classifier {
    private :
        bool debugToggle;
        string trainFile;
        string testFile;
        int totalPosts;
        int uniqueWords;
        map<string, int> numPostsWithWord;
        map<string, int> numPostsWithLabel;
        map<pair<string, string>, int> numPostsWithLabelWithWord;
        
    public :
        Classifier(string inTrain, string inTest, bool debugIn) :
            debugToggle(debugIn), trainFile(inTrain), testFile(inTest), totalPosts(0), 
            uniqueWords(0) {}
        
        void countPosts() {
            csvstream csvin(trainFile);
            map<string, string> row;
            csvin >> row;
            totalPosts = stoi(row["n"]);
            cout << "trained on " << totalPosts << " examples" << endl;
        }

        void countWords() {
            csvstream csvin(trainFile);
            map<string, string> row;
            string allWords;
            while(csvin >> row) {
                allWords += row["content"] + " ";
            }
            uniqueWords = unique_words(allWords).size();
            if(debugToggle) {
                cout << "vocabulary size = " << uniqueWords << endl;
            }
            cout << endl;
        }

        void numPostsWord(const string &inputWord) {
            csvstream csvin(trainFile);
            map<string, string> row;
            while(csvin >> row) {
                set<string> unique = unique_words(row["content"]);
                if(unique.find(inputWord) != unique.end()) {
                    numPostsWithWord[inputWord]++;
                }
            }
        }

        void numPostsLabel(const string &inputLabel) {
            csvstream csvin(trainFile);
            map<string, string> row;
            while(csvin >> row) {
                if(inputLabel == row["tag"]) {
                    numPostsWithLabel[inputLabel]++;
                }
            }
        }

        void numPostsWordLabel(const string &inputWord, const string &inputLabel) {
            csvstream csvin(trainFile);
            map<string, string> row;
            while(csvin >> row) {
                if(inputLabel == row["tag"]) {
                    set<string> content = unique_words(row["content"]);
                    if(content.find(inputWord) != content.end()) {
                        numPostsWithLabelWithWord[{inputLabel, inputWord}]++;
                    }
                }
            }
        }

        void printFirstDebug() const {
            csvstream csvin(trainFile);
            map<string, string> row;
            cout << "training data:" << endl;
            while(csvin >> row) {
                cout << "  label = " << row["tag"] << ", content = " << row["content"] 
                    << endl;
            }
        }

        void printSecondDebug() {
            cout << "classes: " << endl;
            for(auto iter: numPostsWithLabel) {
                string label = iter.first;
                int numPosts = numPostsWithLabel[label];
                cout << label << ", " << numPosts << " examples, log-prior = " 
                << log(1.0*numPosts/totalPosts) << endl;
            }
        }
    
        // EFFECTS: Takes in a string of words and label and calculates the probability
        // that this string of words is associated with that label
        double calcProb(const string &inputWords, const string &inputLabel) {
            set<string> content = unique_words(inputWords);
            double prob = 0;
            prob += log(numPostsWithLabel[inputLabel]/totalPosts);
            for(auto word: content) {
                if(numPostsWithWord.find(word) == numPostsWithWord.end()) {
                    prob += log(1/totalPosts);
                }
                else if(numPostsWithLabelWithWord.find({word, inputLabel}) 
                        == numPostsWithLabelWithWord.end()) {
                    prob += log(numPostsWithWord[word]/totalPosts);
                }
                else {
                    prob += log(numPostsWithLabelWithWord[{word, inputLabel}]
                                /numPostsWithLabel[inputLabel]);
                }
            }
            return prob;
        }
};

int main(int argc, char *argv[]) {
    cout.precision(3);

    //error checking
    if (argc != 3 && argc != 4){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 1;
    }

    if( argc == 4){
        if (!strcmp(argv[3], " --debug")){
            cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
            return 1;
        }   
    }

    //Debugger/Output Toggle
    bool debugToggle = false;
    if(argc == 4){
        debugToggle = true;
    }

    string trainFileName = argv[1];
    string testFileName = argv[2];

    Classifier classi(trainFileName, testFileName, debugToggle);

    // make sure that both input files open correctly
    try {
        csvstream csvin(trainFileName);
    }
    catch(const csvstream_exception &e) {
        cout << "Error opening file: " << trainFileName << endl;
        return 1;
    }
    try {
        csvstream csvin(testFileName);
    }
    catch(const csvstream_exception &e) {
        cout << "Error opening file: " << testFileName << endl;
        return 1;
    }

    if(debugToggle) {
        classi.printFirstDebug();
    }

    classi.countPosts();
    classi.countWords();
    csvstream csvinTrain(trainFileName);
    set<string> content, labels;
    string allWords, allLabels;
    map<string, string> row;

    while(csvinTrain >> row) {
        allWords += row["content"] + " ";
        allLabels += row["tag"] + " ";
    }

    content = unique_words(allWords);
    labels = unique_words(allLabels);

    for(auto iter: content) {
        classi.numPostsWord(iter);
    }

    for(auto iter: labels) {
        classi.numPostsLabel(iter);
    }

    for(auto tag: labels) {
        for(auto word: content) {
            classi.numPostsWordLabel(word, tag);
        }
    }

    if(debugToggle) {
        classi.printSecondDebug();
    }

    csvstream csvinTest(testFileName);
    double prob, maxProb;
    string maxTag, allTags;
    map<string, string> row2, contentToTag; // maps the content to the most likely tag

    // get all the unique tags from the test file
    while(csvinTest >> row2) {
        allTags += row2["tag"] + " ";
    }
    set<string> tags = unique_words(allTags);

    // calculate the most likely tag for each post
    while(csvinTest >> row2) {
        for(auto tag: tags) {
            prob = classi.calcProb(row2["content"], tag);
            if(prob > maxProb) {
                maxTag = tag;
                maxProb = prob;
            }
        }
        contentToTag[row2["content"]] = maxTag;
    }
}