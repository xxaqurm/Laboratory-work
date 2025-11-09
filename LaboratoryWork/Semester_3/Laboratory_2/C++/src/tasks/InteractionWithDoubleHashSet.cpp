#include "../../include/InteractionWithDoubleHashSet.hpp"

void parseLine(DynamicArray<string>& queryParts, const string query) {
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
    Map<string, DynamicArray<string>> fileData;
    string line;
    while (getline(inFile, line)) {
        DynamicArray<string> temp;
        parseLine(temp, line);
        fileData[temp[0]] = DynamicArray<string>(temp.begin() + 1, temp.end());
    }

    DynamicArray<string> queryPart;
    parseLine(queryPart, static_cast<string>(argv[4]));

    if (queryPart.size() != 3) {
        throw runtime_error("[ ERROR ] Incorrect number of arguments!");
    }

    Set<string> st;
    for (size_t i = 0; i < fileData.size(); i++) {
        if (fileData.contains(queryPart[1])) {
            DynamicArray<string>& vals = fileData[queryPart[1]];
            for (size_t j = 0; j < vals.size(); j++)
                st.add(vals[j]);
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

    DynamicArray<string> elms;
    st.getElms(elms);
    fileData[queryPart[1]] = elms;

    DynamicArray<string> keys = fileData.keys();
    ofstream outFile(static_cast<string>(argv[2]), ios::trunc);

    for (size_t i = 0; i < keys.size(); i++) {
        string key = keys[i];
        DynamicArray<string>& values = fileData[key];

        outFile << key;
        for (size_t j = 0; j < values.size(); j++) {
            outFile << " " << values[j];
        }
        outFile << "\n";
    }

    outFile.close();
}