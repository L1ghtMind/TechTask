#include "ZGMLParser.h"
#include <iostream>
using namespace std;

void ZGMLParser::parse()
{
    whiteSpace();
    while (pos < last) {
        if (isChar('<')) {
            if (!isNext('/'))
                parseOpenTag();
            else
                parseClosingTag();
        }
        else {
            pos++;
        }
    }

    for (const auto& q : queries) {
        if (q.second.size() > 0) {
            cout << q.second << endl;
        }
        else {
            cout << "Not Found!" << endl;
        }
    }
}

void ZGMLParser::parseOpenTag()
{
    whiteSpace(); 

    int nameStart = pos + 1;
    string name;

    while (!isChar(' ') && !isChar('>'))
        increment();

    name = document.substr(nameStart, pos - nameStart);

    path.push_back(name);

    parseAttributes();
}

void ZGMLParser::parseAttributes()
{
    whiteSpace();

    int start = pos;
    string currentPath = pathName();
    string fullName;
    while (!isChar('>')) {
        while (!isChar(' ') && !isChar('='))
            increment();

        increment(); whiteSpace();

        fullName = currentPath + document.substr(start, pos - start - 1);
        
        while (!isChar('"')) increment();

        increment();
        start = pos;

        while (!isChar('"'))
            increment();

        for (auto& q : queries) {
            if (q.first == fullName) {
                q.second = document.substr(start, pos - start);
                break;
            }
        }

        while (!isalnum(ch()) && !isChar('>'))
            increment();

        start = pos;
    }
}

string ZGMLParser::pathName()
{
    stringstream res;

    for (int i = 0; i < path.size(); i++) {
        res << path[i];
        if (i < path.size() - 1)
            res << ".";
        else
            res << "~";
    }

    return res.str();
}

void ZGMLParser::parseClosingTag()
{
    increment(); increment();
    int start = pos;
    while (!isChar('>')) {
        increment();
    }

    auto name = document.substr(start, pos - start);

    if (path.back() == name) {
        path.pop_back();
    }
    else
        throw "Syntax error, wrong closing tag";
}
