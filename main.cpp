#include <bits/stdc++.h>
using namespace std;

const string DB_FILE = "data.txt";

// Load entire database into memory from file
static unordered_map<string, set<int>> load_db() {
    unordered_map<string, set<int>> db;
    ifstream fin(DB_FILE);
    if(!fin) return db; // no file yet
    string key; int val;
    while(fin >> key >> val) {
        db[key].insert(val);
    }
    return db;
}

// Save entire database back to file
static void save_db(const unordered_map<string, set<int>>& db) {
    ofstream fout(DB_FILE, ios::trunc);
    for(const auto& p : db) {
        for(int v : p.second) {
            fout << p.first << ' ' << v << '\n';
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto db = load_db();
    int n;
    if(!(cin >> n)) return 0;
    string cmd, key;
    int val;
    for(int i = 0; i < n; ++i) {
        cin >> cmd >> key;
        if(cmd == "insert") {
            cin >> val;
            db[key].insert(val);
        } else if(cmd == "delete") {
            cin >> val;
            auto it = db.find(key);
            if(it != db.end()) {
                it->second.erase(val);
                if(it->second.empty()) db.erase(it);
            }
        } else if(cmd == "find") {
            auto it = db.find(key);
            if(it == db.end() || it->second.empty()) {
                cout << "null\n";
            } else {
                bool first = true;
                for(int v : it->second) {
                    if(!first) cout << ' ';
                    first = false;
                    cout << v;
                }
                cout << "\n";
            }
        }
    }
    save_db(db);
    return 0;
}
