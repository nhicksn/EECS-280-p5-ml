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
    int totalPosts;
    set<string> uniqueWords;
    map<string, int> numPostsWithWord;
    map<string, int> numPostsWithLabel;
    map<pair<string, string>, int> numPostsWithLabelWithWord;
        
public :
    Classifier() :
        totalPosts(0) { }

    void countPosts() {
        totalPosts++;
    }

    void countWords(const string &content) {
        set<string> uniqueContent = unique_words(content);
        for(auto &word: uniqueContent) {
            uniqueWords.insert(word);
        }
    }

    void numPostsWord(const string &content) {
        set<string> uniqueContent = unique_words(content);
        for(auto &word: uniqueWords) {
            if(uniqueContent.find(word) != uniqueContent.end()) {
                numPostsWithWord[word]++;
            }
        }
    }

    void numPostsLabel(const string &label) {
        numPostsWithLabel[label]++;
    }

    void numPostsWordLabel(const string &content, const string &label) {
        set<string> unique = unique_words(content);
        for(auto &word: unique) {
            numPostsWithLabelWithWord[{word, label}]++;
        }
    }

    void train(string filename, bool debugToggle) {
        csvstream csvin(filename);
        map<string, string> row;
        while(csvin >> row) {
            countPosts();
            countWords(row["content"]);
            numPostsWord(row["content"]);
            numPostsLabel(row["tag"]);
            numPostsWordLabel(row["content"], row["tag"]);
            if(debugToggle) {
                printFirstDebug(row["content"], row["tag"]);
            }
        }
    }

    void printFirstDebug(const string &content, const string &label) const {
        cout << "  label = " << label << ", content = " << content << endl;
    }

    void printSecondDebug() {
        cout << "classes:" << endl;
        for(auto &iter: numPostsWithLabel) {
            string label = iter.first;
            int numPosts = numPostsWithLabel[label];
            cout << "  " << label << ", " << numPosts << " examples, log-prior = " 
            << log(1.0*numPosts/totalPosts) << endl;
        }
    }

    void printThirdDebug() {
        cout << "classifier parameters:" << endl;
        for(auto &iter: numPostsWithLabel) {
            string label = iter.first;
            for(auto &word: uniqueWords) {
                if(numPostsWithLabelWithWord.count({word, label})) {
                    int count = numPostsWithLabelWithWord.at({word, label});
                    cout << "  " << label << ":" << word << ", count = " << count
                    << ", log-likelihood = " 
                    << log(1.0*count/numPostsWithLabel[label]) << endl;
                }
            }
        }
        cout << endl;
    }

    void printNumPosts() {
        cout << "trained on " << totalPosts << " examples" << endl;
    }

    void printNumWords() {
        cout << "vocabulary size = " << uniqueWords.size() << endl;
    }

    pair<string, double> calcProb(const string &allContent) {
        set<string> content = unique_words(allContent);
        double maxProb = -1000000;
        string maxLabel;
        for(auto &iter: numPostsWithLabel) {
            double prob = 0;
            string label = iter.first;
            prob += log(1.0*numPostsWithLabel[label]/totalPosts);
            for(auto &word: content) {
                if(!numPostsWithWord.count(word)) {
                    prob += log(1.0/totalPosts);
                }
                else if(!numPostsWithLabelWithWord.count({word, label})) {
                    prob += log(1.0*numPostsWithWord[word]/totalPosts);
                }
                else {
                    prob += log(1.0*numPostsWithLabelWithWord[{word, label}]
                                /numPostsWithLabel[label]);
                }
            }
            if(prob > maxProb) {
                maxProb = prob;
                maxLabel = label;
            }
        }
        return {maxLabel, maxProb};
    }

    void test(string filename) {
        csvstream csvin(filename);
        int numCorrect = 0; int totalNum = 0;
    
        map<string, string> row;
        // run the classifier on the data
        while(csvin >> row) {
            if(row["tag"] == calcProb(row["content"]).first) {
                numCorrect++;
            }
            totalNum++;
            cout << "  correct = " << row["tag"] << ", predicted = " << 
            calcProb(row["content"]).first << ", log-probability score = " <<
            calcProb(row["content"]).second << endl;
            cout << "  content = " << row["content"] << endl;
        }

        cout << endl << "performance: " << numCorrect << " / " << totalNum << 
        " posts predicted correctly" << endl;
    }
};

int main(int argc, char *argv[]) {
    cout.precision(3);

    //error checking
    if (argc != 3 && argc != 4) {
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        return 1;
    }

    if(argc == 4) {
        if (!strcmp(argv[3], " --debug")){
            cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
            return 1;
        }   
    }

    //Debugger/Output Toggle
    bool debugToggle = false;
    if(argc == 4) { debugToggle = true; }

    string trainFileName = argv[1]; string testFileName = argv[2]; Classifier classi;

    // make sure that both input files open correctly
    try { csvstream csvin(trainFileName); }
    catch(const csvstream_exception &e) {
        cout << "Error opening file: " << trainFileName << endl; return 1;
    }

    try { csvstream csvin(testFileName); }
    catch(const csvstream_exception &e) {
        cout << "Error opening file: " << testFileName << endl; return 1;
    }

    if(debugToggle) { cout << "training data:" << endl; }

    // train the classifier
    classi.train(trainFileName, debugToggle);
    
    // print the trained data
    classi.printNumPosts();
    if(debugToggle) { classi.printNumWords(); }; cout << endl;
    if(debugToggle) { classi.printSecondDebug(); classi.printThirdDebug(); }

    cout << "test data:" << endl;

    classi.test(testFileName);
}