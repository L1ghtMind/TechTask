#pragma once
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class ZGMLParser
{
public:
    ZGMLParser(const std::string& doc, const vector<string>& queries) :
        document(doc),
        pos(0),
        last(static_cast<int>(doc.size()))
    {
        for (const auto& q : queries) {
            this->queries.push_back(make_pair(q, ""));
        }
    }

    void parse();

private:
    const std::string document;
    int pos;
    const int last;
    vector<string> path;
    vector<pair<string, string>> queries;

    bool isNext(char c) { return document[pos + 1] == c; }
    bool isChar(char c) { return document[pos] == c; }
    char ch() { return document[pos]; }
    void whiteSpace() {
        while (isspace(document[pos]))
            increment();
    }

    void parseOpenTag();

    void parseAttributes();

    string pathName();

    void parseClosingTag();

    void increment() {
        pos++;

        if (pos == last)
            throw "Syntax error, EOF reached";
    }

};

