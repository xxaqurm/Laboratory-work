#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <map>

#include "../../include/set.hpp"

using namespace std;

void parseLine(vector<string>& queryParts, const string query) {
    string currentPhrase;
    for (int i = 0; i < query.length(); i++) {
        if (query[i] == ' ' && !currentPhrase.empty()) {
            queryParts.push_back(currentPhrase);
            currentPhrase.clear();
        } else if (query[i] != ' ') {
            currentPhrase += query[i];
        }
    }

    if (!currentPhrase.empty()) {
        queryParts.push_back(currentPhrase);
    }
}

void interactionWithSet(int argc, char* argv[]) {
    if (static_cast<string>(argv[1]) != "--file") {
        throw invalid_argument("[ ERROR ] Unknown argument " + static_cast<string>(argv[1]));
    } else if (static_cast<string>(argv[3]) != "--query") {
        throw invalid_argument("[ ERROR ] Unknown argument " + static_cast<string>(argv[3]));
    }

    fstream fcheck(static_cast<string>(argv[2]), ios::in);
    if (!fcheck.is_open()) {
        ofstream createFile(static_cast<string>(argv[2]));
        createFile.close();
    }

    ifstream inFile(static_cast<string>(argv[2]));
    map<string, vector<string>> fileData;
    string line;
    while (getline(inFile, line)) {
        vector<string> temp;
        parseLine(temp, line);
        fileData[temp[0]] = vector<string>(temp.begin() + 1, temp.end());
    }

    vector<string> queryPart;
    parseLine(queryPart, static_cast<string>(argv[4]));

    if (queryPart.size() != 3) {
        throw runtime_error("[ ERROR ] Incorrect number of arguments!");
    }

    Set st;
    for (auto& [key, value] : fileData) {
        if (key == queryPart[1]) {
            for (auto& elm : value) {
                st.add(elm);
            }
            break;
        }
    }

    if (queryPart[0] == "SETADD") {
        st.add(queryPart[2]);
    } else if (queryPart[0] == "SETDEL") {
        st.remove(queryPart[2]);
    } else if (queryPart[0] == "SET_AT") {
        if (st.contains(queryPart[2])) {
            cout << "Элемент присутствует в множестве" << endl;
        } else {
            cout << "Элемент отсутствует в множестве" << endl;
        }
    } else {
        throw runtime_error("[ ERROR ] Unknown command!");
    }

    vector<string> elms;
    st.getElms(elms);
    fileData[queryPart[1]] = elms;

    ofstream outFile(static_cast<string>(argv[2]), ios::trunc);
    for (auto& entry : fileData) {
        outFile << entry.first;
        for (auto& elm : entry.second) {
            outFile << " " << elm;
        }
        outFile << "\n";
    }
    outFile.close();
}