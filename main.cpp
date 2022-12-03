// Project UID db1f506d06d84ab787baf250c265e24e

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>
#include <map>
#include <vector>
#include <sstream>
#include <string.h>

using namespace std;

class Classifier {
    private :
        int totalPosts;
        int uniqueWords;
        map<string, int> numPostsWithWord;
        map<string, int> numPostsWithLabel;
        map<pair<string, string>, int> numPostsWithLabelWithWord;
        
    public :
        Classifier() :
            totalPosts(0), uniqueWords(0) { }
        
        void countPosts(ifstream train) {
            string garbage;
            getline(train, garbage);
            train >> totalPosts;
        }

        void countWords(ifstream train) {
            string garbage;
            getline(train, garbage);
            map<string, bool> uniqueWord;
            string trash1, trash2, trash3;
            vector<string> words;
            for(int i = 0; i < totalPosts; i++) {
                train >> trash1 >> trash2 >> trash3;
                getline(train, words[i]);
            }
            for(int i = 0; i < totalPosts; i++) {
                string word;
                istringstream wordStream(words[i]);
                while(wordStream >> word) {
                    if(uniqueWord[word] == false) {
                    uniqueWords++;
                    uniqueWord[word] = true;
                    }
                }                
            }
        }

        void numPostsWord(ifstream train, string inputWord) {
            string garbage;
            getline(train, garbage);
            string trash1, trash2, trash3;
            vector<string> words;
            for(int i = 0; i < totalPosts; i++) {
                train >> trash1 >> trash2 >> trash3;
                getline(train, words[i]);
            }
            for(int i = 0; i < totalPosts; i++) {
                string word;
                istringstream wordStream(words[i]);
                while(wordStream >> word) {
                    if(inputWord == word) {
                        numPostsWithWord[inputWord]++;
                        continue;
                    }
                }
            }
        }

        void numPostsLabel(ifstream train, string inputLabel) {
            string garbage;
            getline(train, garbage);
            string trash1, trash2, trash3, label;
            for(int i = 0; i < totalPosts; i++) {
                train >> trash1 >> trash2 >> label >> trash3;
                if(inputLabel == label) {
                    numPostsWithLabel[inputLabel]++;
                }
            }
        }

        void numPostsWordLabel(ifstream train, string inputWord, string inputLabel) {
            string garbage;
            getline(train, garbage);
            string trash1, trash2, label, words, wordCheck;
            for(int i = 0; i < totalPosts; i++) {
                train >> trash1 >> trash2 >> label >> words;
                if(label == inputLabel) {
                    stringstream wordStream(words);
                    while(wordStream >> wordCheck) {
                        if(wordCheck == inputWord) {
                            numPostsWithLabelWithWord[{inputLabel, inputWord}]++;
                            continue;
                        }
                    }
                }
            }
        }
};

int main(int argc, char *argv[]) {

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

if(argc == 4){
    debugToggle = true;
}

string trainFileName = argv[1];
string testFileName = argv[2];

// read in input files
ifstream finTrain;
finTrain.open(trainFileName);

ifstream finTest;
finTest.open(testFileName);

// check for errors
if (!finTrain.is_open() || !finTest.is_open()) {
    cout << "Error opening file: " << trainFileName << endl;
    return 1;
}

//NOTES / Outline
//read posts from train file


//train the classifier and store information needed
//total number of posts - int
//number of unique words in all posts - int
//for each word the number of posts containing that word - map (key value pair)
//for each label the number of posts with that label -  map (key value pair)
//for each label and word, the number of posts with that label that contain that word 
// - map of pairs map<pair<string, string>, int > mapName;


//Classifier should compute the log-probability score of a post 
//given post X what is probability of label C
// ln(P(C)) = number of training posts with label C / number of training posts
// + log-likelihood (in specs)

//Read test file and predict a label using your classifier.


}
