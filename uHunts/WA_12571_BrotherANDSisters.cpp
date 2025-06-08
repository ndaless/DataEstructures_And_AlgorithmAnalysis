// encontrar el valor máximo de la operación bitwise AND entre un número dado 𝑎 y una secuencia de números
// Trie

#include<bits/stdc++.h>

using namespace std;

const int MAX_BITS = 30;

struct TrieNode {
    TrieNode* child[2] = {nullptr, nullptr};
};

void insert(TrieNode* root, int num) {
    TrieNode* node = root;
    for(int i = MAX_BITS; i >= 0; i--) {
        int bit = (num >> i) & 1; // extre bit en pos i
        if(!node->child[bit]) node->child[bit] = new TrieNode();
        node = node->child[bit];
    }
}

int getMAX(TrieNode* root, int a){
    TrieNode* node = root;
    int res = 0;
    for(int i = MAX_BITS; i >= 0; i--){
        int abit = (a >> i) & 1; // extrae el bit i de a
        if(abit == 1){
            if(node->child[1]) {
                res |= (1 << i);
                node = node->child[1];
            } else if(node->child[0]){
                node = node->child[0];
            } else break;
        } else{
            if(node->child[0]){
                node = node->child[0];
            } else if(node->child[1]){
                node = node->child[1];
            } else break;
        }
    }
    return res;
}

void deleteTrie(TrieNode* node) {
    if(!node) return;
    deleteTrie(node->child[0]);
    deleteTrie(node->child[1]);
    delete node;
}


int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T; cin >> T;

    for(int t = 0; t < T; t++){
        int N, Q; cin >> N >> Q;

        TrieNode* root = new TrieNode();
        vector<int> numbers(N);

        for(int n = 0; n < N; n++){ // O(N*30)
            cin >> numbers[n];
            insert(root, numbers[n]);
        }

        int a; // number to compare
        for(int q = 0; q < Q; q++){ // O(Q*30)
            cin >> a;
            cout << getMAX(root, a) << endl;
        }

        deleteTrie(root);
    }

    return 0;
}