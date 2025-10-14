#include "../../include/Parser.hpp"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

map<string, vector<string>> DSCommands {
    {"ARRAY", {"AINSERT", "APUSHBACK", "AGETELM", "ADELELM", "AREPLACE", "AGETSIZE", "APRINT"}},                                                                                // ARRAY
    {"FORWARDLIST", {"FPUSHHEAD", "FPUSHTAIL", "FINSERTAFTER", "FINSERTBEFORE", "FPRINT", "FPRINTREV", "FDELHEAD", "FDELTAIL", "FDELBEFORE", "FDELAFTER", "FDELELM", "FFIND"}}, // FORWARDLIST
    {"LINKEDLIST", {"LPUSHHEAD", "LPUSHTAIL", "LINSERTAFTER", "LINSERTBEFORE", "LPRINT", "LPRINTREV", "LDELHEAD", "LDELTAIL", "LDELBEFORE", "LDELAFTER", "LDELELM", "LFIND"}},  // LINKEDLIST
    {"QUEUE", {"QPUSH", "QPOP", "QPRINT"}},                                                                                                                                     // QUEUE
    {"STACK", {"SPUSH", "SPOP", "SPRINT"}},                                                                                                                                     // STACK
    {"TREEAVL", {"TPUSH", "TFIND", "TDELELM", "TDFS", "TBFS"}}                                                                                                                  // AVLTREE
};

vector<string> parseString(string line) {
    vector<string> words;
    string currentWord;
    for (auto& symb : line) {
        if (symb == ' ' || symb == '\t' || symb == '\n') {
            words.push_back(currentWord);
            currentWord.clear();
        } else {
            currentWord += symb;
        }
    }
    
    if (!currentWord.empty()) {
        words.push_back(currentWord);
    }

    return words;
}

ProgramOptions parseProgramOptions(int argc, char* argv[]) {
    ProgramOptions opts;

    for (int i = 1; i < argc; i++) {
        string arg = static_cast<string>(argv[i]);

        if (arg == "--file") {
            if (i + 1 >= argc) {
                throw invalid_argument("Missing argument for --file");
            }
            opts.fileName = argv[++i];
        } else if (arg == "--query") {
            if (i + 1 >= argc) {
                throw invalid_argument("Missing argument for --query");
            }
            opts.query = argv[++i];
        } else {
            throw invalid_argument("Unknown argument: " + arg);
        }
    }

    if (opts.fileName.empty()) {
        throw invalid_argument("Missing required option: --file");
    }

    if (opts.query.empty()) {
        throw invalid_argument("Missing required option: --query");
    }

    return opts;
}

ParsedCommand parseQuery(string query) {
    ParsedCommand cmd;
    string currentParam;
    
    vector<string> params = parseString(query);
    for (auto& param : params) {
        if (cmd.command.empty()) {
            cmd.command = param;
        } else if (cmd.userStructName.empty()) {
            cmd.userStructName = param;
        } else {
            cmd.args.push_back(param);
        }
    }

    if (!currentParam.empty()) {
        cmd.args.push_back(currentParam);
    }

    if (cmd.command.empty()) {
        throw invalid_argument("Missing required argument of query: command");
    }

    if (cmd.userStructName.empty()) {
        throw invalid_argument("Missing required argument of query: structure name");
    }

    bool matchStruct = false;
    int structureNumber = 0;
    for (auto& [structName, commands] : DSCommands) {
        if (structName[0] == cmd.command[0]) {
            if (find(commands.begin(), commands.end(), cmd.command) != commands.end()) {
                matchStruct = true;
                cmd.structName = static_cast<Structures>(structureNumber);
                break;
            }
        }
        structureNumber++;
    }
    
    if (!matchStruct) {
        throw invalid_argument("Unknown argument: " + cmd.command);
    }

    return cmd;
}