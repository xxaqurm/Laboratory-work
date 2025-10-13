#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

extern map<string, vector<string>> DSCommands;

enum class Structures {
    ARRAY,
    FORWARDLIST,
    LINKEDLIST,
    QUEUE,
    STACK,
    TREEAVL
};

struct ParsedCommand {
    string command;
    string userStructName;
    Structures structName;
    vector<string> args;
};

struct ProgramOptions {
    string fileName;
    string query;
};

vector<string> parseString(string line);

ProgramOptions parseProgramOptions(int argc, char* argv[]);
ParsedCommand parseQuery(string query);