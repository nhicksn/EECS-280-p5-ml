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

}
