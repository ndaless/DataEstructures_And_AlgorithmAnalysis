// modificar un árbol para que cumpla con una propiedad específica:
// cada nodo no hoja debe tener exactamente 𝐾 hijos.
// DFS

// # include <bits/stdc++.h>
# include <iostream>
# include <vector>
# include <set>

using namespace std;


struct ChristmasTree{

    struct Node{
        int childs = 0;
        int subtree = 0;
    
        bool operator<(const Node &other) const {
            return subtree < other.subtree;
        }
    };

    int N; int K;
    int ans;
    vector< Node > tree;
    vector< vector <int> > edges;
    vector< set< pair<int, int> > > edgSet;

    ChristmasTree(int _K, const vector< vector <int> > &_edges){
        N = _edges.size();
        K = _K;

        tree.resize(N);
        edges = _edges;
        edgSet.resize(N);

        // for(int i = 0; i < N; i++){
        //     for(const auto nd : edges[i]){
        //         edgSet[i].insert({nd, 0});
        //     }
        // }

        buildCT();
    }

void buildCT(){
    // vector <int> visited(N, 0); 
    // visitDFS(0, 0, visited);
    int val = visitDFS(0, K);
    
    return;
}

// void visitDFS(int nd, int parent, vector <int> &visited){
int visitDFS(int nd, int K){
    // cout << "Entrando a nodo " << nd << endl;

    if(edges[nd].size() < K ) return tree[nd].subtree;;

    for(const auto &child : edges[nd]){ 
        tree[nd].childs += 1; // cout << "tree[" << nd << "].childs: " << tree[nd].childs << endl;
        edgSet[nd].insert({child, visitDFS(child, K)});
        tree[nd].subtree += (1 + tree[child].subtree); // cout << "tree[" << nd << "].subtree: " << tree[nd].subtree << endl;
    }

    while (tree[nd].childs > K){
        if (!edgSet[nd].empty()) {
            // tree[nd].childs -= 1; tree[nd].subtree -= *edgSet[nd].begin().second() -1; // esto no esta funcionando, si podriamos guardar un minheap en cada entrada para acceder rapido al primer elemento
            edgSet[nd].erase(edgSet[nd].begin());
        }
    }
    
    // cout << "Saliendo del nodo " << nd << " con valor " << tree[nd].subtree << endl;
    return tree[nd].subtree;
}

int ansqry(){
    return tree[0].subtree + 1;
}
};

// recurda restar uno el ingresar los nodos, estan indexados desde 1 en el problema
int main(){
    int T; cin >> T;
    int N, K;
    
    // vector <int> sol;

    for(int t = 0; t < T; t++){
        cin >> N >> K;
        vector < vector <int> > edges(N);
        int a, b;

        for(int i = 0; i < N-1; i++){
            cin >> a >> b;
            edges[a-1].push_back(b-1);
        }

        ChristmasTree CT(K, edges);
        
        // sol.push_back(CT.ansqry());
        cout << "Case " << t+1 << ": " << CT.ansqry() << endl;
    }
    
    // int t = 1;

    // for(const auto s : sol){
    //     cout << "Case " << t << ": " << s << endl;
    //     t++;
    // }
    return 0;
}