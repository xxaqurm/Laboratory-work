#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include "./include/AVLTree.hpp"
#include "./include/DynamicArray.hpp"
#include "./include/ForwardList.hpp"
#include "./include/LinkedList.hpp"
#include "./include/Queue.hpp"
#include "./include/Stack.hpp"
#include "./include/Parser.hpp"

using namespace std;

int main(int argc, char* argv[]) {
    try {
        ProgramOptions opts = parseProgramOptions(argc, argv);
        ParsedCommand cmd = parseQuery(opts.query);

        {
            fstream fcheck(opts.fileName, ios::in);
            if (!fcheck.is_open()) {
                ofstream createFile(opts.fileName);
                createFile.close();
            }
        }

        map<string, vector<string>> fileData;
        ifstream inFile(opts.fileName);
        string line;
        bool userStructExists = false;

        while (getline(inFile, line)) {
            vector<string> lineData = parseString(line);
            if (lineData.empty()) continue;

            if (lineData[0] == cmd.userStructName) {
                userStructExists = true;
            }

            fileData[lineData[0]] = {};
            for (size_t i = 1; i < lineData.size(); i++) {
                fileData[lineData[0]].push_back(lineData[i]);
            }
        }
        inFile.close();

        if (!userStructExists) {
            fileData[cmd.userStructName] = {};
        }
        
        switch (cmd.structName) {
            case Structures::ARRAY: {
                DynamicArray dymArr;
                for (auto& elm : fileData[cmd.userStructName]) {
                    dymArr.PushBack(elm);
                }

                if (cmd.command == DSCommands["ARRAY"][0]) {           // INSERT
                    dymArr.Insert(cmd.args[1], stoi(cmd.args[0]));
                } else if (cmd.command == DSCommands["ARRAY"][1]) {    // PUSHBACK
                    dymArr.PushBack(cmd.args[0]);
                } else if (cmd.command == DSCommands["ARRAY"][2]) {    // GETELM
                    cout << dymArr.GetElm(stoi(cmd.args[0])) << endl;
                } else if (cmd.command == DSCommands["ARRAY"][3]) {    // DEL
                    dymArr.DelElm(stoi(cmd.args[0]));
                } else if (cmd.command == DSCommands["ARRAY"][4]) {    // REPLACE
                    dymArr.Replace(cmd.args[1], stoi(cmd.args[0]));
                } else if (cmd.command == DSCommands["ARRAY"][5]) {    // SIZE
                    cout << dymArr.GetSize() << endl;
                } else if (cmd.command == DSCommands["ARRAY"][6]) {    // PRINT
                    dymArr.Print();
                }

                fileData[cmd.userStructName].clear();
                for (size_t i = 0; i < dymArr.GetSize(); i++) {
                    fileData[cmd.userStructName].push_back(dymArr.GetElm(i));
                }

                break;
            }
            case Structures::FORWARDLIST: {
                ForwardList fl;
                for (auto& elm : fileData[cmd.userStructName]) {
                    fl.PushTail(elm);
                }
                
                if (cmd.command == DSCommands["FORWARDLIST"][0]) {           // PUSHHEAD
                    fl.PushHead(cmd.args[0]);
                } else if (cmd.command == DSCommands["FORWARDLIST"][1]) {    // PUSHTAIL
                    fl.PushTail(cmd.args[0]);
                } else if (cmd.command == DSCommands["FORWARDLIST"][2]) {    // INSERTAFTER
                    fl.InsertAfter(cmd.args[1], stoi(cmd.args[0]));
                } else if (cmd.command == DSCommands["FORWARDLIST"][3]) {    // INSERTBEFORE
                    fl.InsertBefore(cmd.args[1], stoi(cmd.args[0]));
                } else if (cmd.command == DSCommands["FORWARDLIST"][4]) {    // PRINT
                    fl.Print();
                } else if (cmd.command == DSCommands["FORWARDLIST"][5]) {    // PRINTREV
                    fl.PrintReverse(fl.head);
                    cout << endl;
                } else if (cmd.command == DSCommands["FORWARDLIST"][6]) {    // DELELM
                    fl.DelElm(cmd.args[0]);
                } else if (cmd.command == DSCommands["FORWARDLIST"][7]) {    // FIND
                    cout << fl.Find(cmd.args[0]) << endl;
                }

                fileData[cmd.userStructName].clear();
                for (size_t i = 0; i < fl.GetSize(); i++) {
                    fileData[cmd.userStructName].push_back(fl.GetElm(i));
                }

                break;
            }
            case Structures::LINKEDLIST: {
                LinkedList ll;
                for (auto& elm : fileData[cmd.userStructName]) {
                    ll.PushTail(elm);
                }
                
                if (cmd.command == DSCommands["LINKEDLIST"][0]) {           // PUSHHEAD
                    ll.PushHead(cmd.args[0]);
                } else if (cmd.command == DSCommands["LINKEDLIST"][1]) {    // PUSHTAIL
                    ll.PushTail(cmd.args[0]);
                } else if (cmd.command == DSCommands["LINKEDLIST"][2]) {    // INSERTAFTER
                    ll.InsertAfter(cmd.args[1], stoi(cmd.args[0]));
                } else if (cmd.command == DSCommands["LINKEDLIST"][3]) {    // INSERTBEFORE
                    ll.InsertBefore(cmd.args[1], stoi(cmd.args[0]));
                } else if (cmd.command == DSCommands["LINKEDLIST"][4]) {    // PRINT
                    ll.Print();
                } else if (cmd.command == DSCommands["LINKEDLIST"][5]) {    // PRINTREV
                    ll.PrintReverse();
                } else if (cmd.command == DSCommands["LINKEDLIST"][6]) {    // DELELM
                    ll.DelElm(cmd.args[0]);
                } else if (cmd.command == DSCommands["LINKEDLIST"][7]) {    // FIND
                    cout << ll.Find(cmd.args[0]) << endl;
                }

                fileData[cmd.userStructName].clear();
                for (size_t i = 0; i < ll.GetSize(); i++) {
                    fileData[cmd.userStructName].push_back(ll.GetElm(i));
                }

                break;
            }
            case Structures::QUEUE: {
                Queue q;
                for (auto& elm : fileData[cmd.userStructName]) {
                    q.Push(elm);
                }
                
                if (cmd.command == DSCommands["QUEUE"][0]) {           // PUSH
                    q.Push(cmd.args[0]);
                } else if (cmd.command == DSCommands["QUEUE"][1]) {    // POP
                    cout << q.Pop() << endl;
                } else if (cmd.command == DSCommands["QUEUE"][2]) {    // PRINT
                    q.Print();
                }

                fileData[cmd.userStructName].clear();
                for (size_t i = 0; i < q.GetSize(); i++) {
                    fileData[cmd.userStructName].push_back(q.GetElm(i));
                }

                break;
            }
            case Structures::STACK: {
                Stack st;
                for (auto& elm : fileData[cmd.userStructName]) {
                    st.Push(elm);
                }
                
                if (cmd.command == DSCommands["STACK"][0]) {           // PUSH
                    st.Push(cmd.args[0]);
                } else if (cmd.command == DSCommands["STACK"][1]) {    // POP
                    cout << st.Pop() << endl;
                } else if (cmd.command == DSCommands["STACK"][2]) {    // PRINT
                    st.Print();
                }

                fileData[cmd.userStructName].clear();
                for (size_t i = 0; i < st.GetSize(); i++) {
                    fileData[cmd.userStructName].push_back(st.GetElm(i));
                }

                break;
            }
            case Structures::TREEAVL: {
                AVLTree tree;
                for (auto& elm : fileData[cmd.userStructName]) {
                    tree.Push(tree.root, stoi(elm));
                }
                
                if (cmd.command == DSCommands["TREEAVL"][0]) {           // PUSH
                    tree.root = tree.Push(tree.root, stoi(cmd.args[0]));
                } else if (cmd.command == DSCommands["TREEAVL"][1]) {    // FIND
                    if (tree.Find(tree.root, stoi(cmd.args[0])) != nullptr) {
                        cout << "TRUE" << endl;
                    } else {
                        cout << "FALSE" << endl;
                    }
                } else if (cmd.command == DSCommands["TREEAVL"][2]) {    // DELELM
                    tree.root = tree.DelElm(tree.root, stoi(cmd.args[0]));
                } else if (cmd.command == DSCommands["TREEAVL"][3]) {    // DFS
                    tree.DFS(tree.root);
                } else if (cmd.command == DSCommands["TREEAVL"][4]) {    // BFS
                    tree.BFS(tree.root);
                }

                fileData[cmd.userStructName].clear();
                
                vector<string> treeElements;
                tree.GetElms(tree.root, treeElements);
                fileData[cmd.userStructName] = treeElements;

                break;
            }
        }

        ofstream outFile(opts.fileName, ios::trunc);
        for (auto& entry : fileData) {
            outFile << entry.first;
            for (auto& elm : entry.second) {
                outFile << " " << elm;
            }
            outFile << "\n";
        }
        outFile.close();

    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        cerr << "COMMAND LIST:" << endl;
        for (auto& ds : DSCommands) {
            cerr << ds.first << ": ";
            for (auto& command : ds.second) {
                cerr << command << " ";
            }
            cerr << endl;
        }
        return 1;
    }

    return 0;
}
