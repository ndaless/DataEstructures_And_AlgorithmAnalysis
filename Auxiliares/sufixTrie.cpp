# include <bits/stdc++.h>

// # include <algorithm>
// # include <string>
// # include <iostream>

using namespace std;

// Node structure for trie
struct trieNode{
    int children[26]; // como no cambiaremos esto, es mejor un arreglo estatico
    bool isWord;
    trieNode() : isWord(false){ // asi se asigna el valor al momento de construir (varias too)
        fill(begin(children), end(children), -1); // assign para arreglos estaticos
    }
};

// Trie Class
class trie {
    // vector de nodos, que guarda? todos los nodos 
    vector<struct trieNode> nodes;

public:
    // insertamos raiz
    trie() : nodes(1) {} 

    // print function
    void print(){
        for(int i = 0; i < nodes.size(); i++){
            cout << "Node " << i << ": ";
            for(int j = 0; j < 26; j++){
                if(nodes[i].children[j] != -1){
                    cout << (char) ('a' + j) << " (" << nodes[i].children[j] << ") ";
                }
            }
            cout << endl;
        }
    }

    // insert a string into the trie
    void insert(const string& s){
        // star from root 
        int n = 0;
        for(const auto ch : s){
            int c = ch - 'a'; // convertimos a entero
            // create the child if not existed
            if(nodes[n].children[c] == -1){
                nodes[n].children[c] = nodes.size(); // anotamos que el hijo ch del nodo actual esta 
                nodes.push_back(trieNode());         // en la ultima posicion actual del arreglo de nodos
            }
            n = nodes[n].children[c]; // vamos al nuevo nodo para insertar siguiente letra
        }
        nodes[n].isWord = true; // al terminar de insertar s, marcamos el nodo como el final de s
    }

};

int main(){

    trie t;
    t.insert("vamos");  // asi le estamos pasando un rvalue (da problema con void insert(string& s){) pq no es un objeto en la memoria
    string s = "al";    // asi no daria problema
    t.insert(s);
    t.insert("cerro");  // asi no da problema si ponemos const en void insert(CONST string& s){

    t.print();
    return 0;

}