#include "trees/abb.hpp"
#include <iostream>
#include "trees/abb.hpp"
#include <iostream>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>

using namespace std;
using namespace std::chrono;

vector<int> loadKeys(const string &filename) {
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
        "data_trees/keys_sorted_33554432.bin"
    };
    vector<string> randomFiles = {
        "data_trees/keys_1024.bin", 
        "data_trees/keys_32768.bin", 
        "data_trees/keys_1048576.bin", 
        "data_trees/keys_33554432.bin"
    };
    string queryFile = "data_trees/queries_1000.bin";
    
    vector<int> queries = loadKeys(queryFile);
    
    cout << "Data\tABB Build (ms)\tABB Search (ms)\t" << endl;
    
    // Iteración para archivos ordenados
    for (const string &file : sortedFiles) {
        vector<int> keys = loadKeys(file);
        
        // Construcción y medición para ABB
        trees::ABB* abbTree = new trees::ABB(); // Crear árbol en el heap
        long long abbBuildTime = measureBuildTime(*abbTree, keys);
        long long abbSearchTime = measureSearchTime(*abbTree, queries);
        
        // Imprime resultados para archivo ordenado
        cout << "Sorted (" << file << ")\t" 
             << abbBuildTime << "\t"
             << abbSearchTime << endl;

        // Liberar memoria del árbol después de la prueba
        delete abbTree;
    }
    
    // Iteración para archivos aleatorios
    for (const string &file : randomFiles) {
        vector<int> keys = loadKeys(file);
        
        // Construcción y medición para ABB
        trees::ABB* abbTree = new trees::ABB(); // Crear árbol en el heap
        long long abbBuildTime = measureBuildTime(*abbTree, keys);
        long long abbSearchTime = measureSearchTime(*abbTree, queries);

        // Imprime resultados para archivo aleatorio
        cout << "Random (" << file << ")\t" 
             << abbBuildTime << "\t"
             << abbSearchTime << endl;

        // Liberar memoria del árbol después de la prueba
        delete abbTree;
    }
}


int main() {
    runExperiments();
    return 0;
}

