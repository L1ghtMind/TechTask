#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include "ZGMLParser.h"
using namespace std;

int main() {
    string line;
    ifstream dataFile;
    int N, Q;
    stringstream document;
    string temp;
    vector<string> queries;

    dataFile.open("data.zgml", ios::in);
    if(dataFile.is_open())
    {
        dataFile >> N >> Q;
        dataFile.ignore();

        for (int i = 0; i < N; i++) {
            getline(dataFile, temp);
            document << temp;
        }

        for (int i = 0; i < Q; i++) {
            getline(dataFile, temp);
            queries.push_back(temp);
        }
    }
    
    unique_ptr<ZGMLParser> zgmlParser(new ZGMLParser(document.str(), queries));

    try {
        zgmlParser->parse();
    }
    catch (const char* message) {
        cout << "Parsing error: " << message << endl;
    }
    
    return 0;
}