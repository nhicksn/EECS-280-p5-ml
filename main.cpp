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
        string trainFile;
        string testFile;
        int totalPosts;
        int uniqueWords;
        map<string, int> numPostsWithWord;
        map<string, int> numPostsWithLabel;
        map<pair<string, string>, int> numPostsWithLabelWithWord;
        
    public :
        Classifier(string inTrain, string inTest) :
            totalPosts(0), uniqueWords(0), trainFile(inTrain), testFile(inTest) { }
        
        void countPosts() {
            try {
                csvstream csvin(trainFile);
                map<string, string> row;
                csvin >> row;
                totalPosts = stoi(row["n"]);
            }
            catch(bad_exception) { }
        }

        void countWords() {
            csvstream csvin(trainFile);
            map<string, string> row;
            set<string> totalUniqueWords;
            string allWords;
            while(csvin >> row) {
                allWords += row["content"];
            }
            uniqueWords = unique_words(allWords).size();

        }

        void numPostsWord(string inputWord) {
            csvstream csvin(trainFile);
            map<string, string> row;
            while(csvin >> row) {
                set<string> unique = unique_words(row["content"]);
                if(unique.find(inputWord) != unique.end()) {
                    numPostsWithWord[inputWord]++;
                }
            }
        }

        void numPostsLabel(string inputLabel) {
            csvstream csvin(trainFile);
            map<string, string> row;
            while(csvin >> row) {
                if(inputLabel == row["tag"]) {
                    numPostsWithLabel[inputLabel]++;
                }
            }
        }

        void numPostsWordLabel(string inputWord, string inputLabel) {
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
};

int main(int argc, char *argv[]) {
    cout.precision(3);

    //error checking
    if (argc != 3 || argc != 4){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
    }

    if( argc == 4){
        if (!strcmp(argv[3], "--debug")){
            cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
        }   
    }

    //Debugger/Output Toggle
    bool debugToggle = false;

    //really important stuff (secrete sauce)
    //DO NOT DELETE THIS IS CRUCIAL
    if(debugToggle == false) {
        debugToggle = true;
    }
    if(debugToggle == true) {
        debugToggle = false;
    }

    if(argc == 4){
        debugToggle = true;
    }

    string trainFileName = argv[1];
    string testFileName = argv[2];

    //NOTES / Outline
    //read posts from train file


    //train the classifier and store information needed
    //total number of posts - int
    //number of unique words in all posts - int
    //for each word the number of posts containing that word - map (key value pair)
    //for each label the number of posts with that label -  map (key value pair)
    //for each label and word, the number of posts with that label that contain that word 
    // - map of pairs map<pair<string, string>, int > mapName;

    Classifier classi(trainFileName, testFileName);

    try {
        classi.countPosts();
    }
    catch(const csvstream_exception &e) {
        cout << "Error opening file: " << trainFileName << endl;
        return 1;
    }

    //Classifier should compute the log-probability score of a post 
    //given post X what is probability of label C
    // ln(P(C)) = number of training posts with label C / number of training posts
    // + log-likelihood (in specs)

    //Read test file and predict a label using your classifier.
}