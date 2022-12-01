#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

class Classifier {
    private :


    public :


};

int main(int argc, char *argv[]) {

//error checking
if (argc != 3 || argc != 4){
    cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
}

if( argc == 4){
    if (argv[3] != "--debug"){
        cout << "Usage: main.exe TRAIN_FILE TEST_FILE [--debug]" << endl;
    }
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
