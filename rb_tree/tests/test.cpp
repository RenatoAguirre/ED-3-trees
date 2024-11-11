#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

#include "trees/rb.hpp"

using namespace std;
using namespace std::chrono;

vector<int> loadKeys(const string &filename) {
  cout << "Loading keys from " << filename << endl;
    ifstream file(filename, ios::binary);
    vector<int> keys;
    int key;
    while (file.read(reinterpret_cast<char*>(&key), sizeof(int))) {
        keys.push_back(key);
    }
    cout << "Loaded " << keys.size() << " keys from " << filename << endl;
    return keys;
}
template <typename TreeType>
long long measureBuildTime(TreeType& tree, const vector<int>& keys) {
    auto start = high_resolution_clock::now();
    for (const int &key : keys) {
        tree.insert(key);
    }
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}

template <typename TreeType>
long long measureSearchTime(TreeType& tree, const vector<int>& queries) {
    auto start = high_resolution_clock::now();
    for (const int &query : queries) {
        tree.find(query);
    }
    auto end = high_resolution_clock::now();
    return duration_cast<milliseconds>(end - start).count();
}

void runExperiments() {
    vector<string> sortedFiles = {
        "data_trees/keys_sorted_1024.bin", 
        "data_trees/keys_sorted_32768.bin",
        "data_trees/keys_sorted_1048576.bin",
        "data_trees/keys_sorted_33554432.bin",
    };
    vector<string> randomFiles = {
        "data_trees/keys_1024.bin", 
        "data_trees/keys_32768.bin", 
        "data_trees/keys_1048576.bin",
        "data_trees/keys_33554432.bin",
    };
    string queryFile = "data_trees/queries_1000.bin";
    
    vector<int> queries = loadKeys(queryFile);
    
    cout << "Data\tABB Build (ms)\tAVL Build (ms)\tRB Build (ms)\tABB Search (ms)\tAVL Search (ms)\tRB Search (ms)" << endl;
    
    for (const string &file : sortedFiles) {
        vector<int> keys = loadKeys(file);
        
        
        // Construcción y medición para RB
        trees::RB rbTree;
        long long rbBuildTime = measureBuildTime(rbTree, keys);
        long long rbSearchTime = measureSearchTime(rbTree, queries);
        
        // Imprime resultados para archivo ordenado
        cout << "Sorted (" << file << ")\t" 
             << rbBuildTime << "\t"
             << rbSearchTime << endl;
    }
    
    for (const string &file : randomFiles) {
        vector<int> keys = loadKeys(file);
        
        // Construcción y medición para RB
        trees::RB rbTree;
        long long rbBuildTime = measureBuildTime(rbTree, keys);
        long long rbSearchTime = measureSearchTime(rbTree, queries);
        
        // Imprime resultados para archivo aleatorio
        cout << "Random (" << file << ")\t" 
             << "\t" << rbBuildTime << "\t"
             << "\t" << rbSearchTime << endl;
    }
}

int main() {
    runExperiments();
    return 0;
}
