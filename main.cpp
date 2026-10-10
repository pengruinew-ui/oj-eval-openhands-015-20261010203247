#include <bits/stdc++.h>
using namespace std;

// Number of bucket files (must be <= 20 as per file count limit)
static const int BUCKET_COUNT = 19;

static string bucket_file(int idx) {
    return "bucket_" + to_string(idx) + ".txt";
}

static int bucket_id(const string& key) {
    // deterministic polynomial rolling hash
    unsigned long long h = 0;
    for (unsigned char c : key) {
        h = h * 131 + c;
    }
    return (int)(h % BUCKET_COUNT);
}

// Load all values for a given key from its bucket file
static set<int> load_values(const string& key) {
    set<int> vals;
    int b = bucket_id(key);
    ifstream fin(bucket_file(b));
    if(!fin) return vals;
    string k; int v;
    while(fin >> k >> v) {
        if(k == key) vals.insert(v);
    }
    return vals;
}

// Append a (key, value) pair to its bucket file
static void append_pair(const string& key, int val) {
    int b = bucket_id(key);
    ofstream fout(bucket_file(b), ios::app);
    fout << key << ' ' << val << '\n';
}

// Rewrite the bucket file without a specific (key, value) pair
static void delete_pair(const string& key, int val) {
    int b = bucket_id(key);
    string tmp = bucket_file(b) + ".tmp";
    ifstream fin(bucket_file(b));
    ofstream fout(tmp);
    string k; int v;
    while(fin >> k >> v) {
        if(!(k == key && v == val)) {
            fout << k << ' ' << v << '\n';
        }
    }
    fin.close();
    fout.close();
    rename(tmp.c_str(), bucket_file(b).c_str());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    if(!(cin >> n)) return 0;
    string cmd, key;
    int val;
    for(int i = 0; i < n; ++i) {
        cin >> cmd >> key;
        if(cmd == "insert") {
            cin >> val;
            set<int> cur = load_values(key);
            if(cur.find(val) == cur.end()) {
                append_pair(key, val);
            }
        } else if(cmd == "delete") {
            cin >> val;
            set<int> cur = load_values(key);
            if(cur.find(val) != cur.end()) {
                delete_pair(key, val);
            }
        } else if(cmd == "find") {
            set<int> cur = load_values(key);
            if(cur.empty()) {
                cout << "null\n";
            } else {
                bool first = true;
                for(int v : cur) {
                    if(!first) cout << ' ';
                    first = false;
                    cout << v;
                }
                cout << "\n";
            }
        }
    }
    return 0;
}
