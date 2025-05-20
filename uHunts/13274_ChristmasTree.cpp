// // # include <bits/stdc++.h>
// # include <vector>
// # include <iostream>

// using namespace std;

// struct Node{
//     int childs = 0;
//     int subtree = 0;
// };

// struct ChristmasTree{
//     int N; int K;
//     int ans;
//     vector< Node > tree;
//     vector< vector <int> > edges;

//     ChristmasTree(int _K, const vector< vector <int> > &_edges){
//         N = _nodes.size();
//         K = _K;

//         tree.resize(N);
//         edges = _edges;

//         ans = buildCT();
//     }

// int buildCT(){
//     // vector <int> visited(N, 0); 
//     // visitDFS(0, 0, visited);
//     return visitDFS(0, K);
// }

// // void visitDFS(int nd, int parent, vector <int> &visited){
// int visitDFS(int nd, int K){

//     for(const auto &child : edges[nd]){ 
//         tree[nd].childs++;
//         tree[nd].subtree += (1 + visitDFS(child, K));
//     }
//         if(tree[nd].subtree < K) {
//             tree[nd].subtree = 0; tree[nd].childs = 0; // lo convertimos en un nodo hoja
//         }
//     return tree[nd].subtree;

// }

// int ansqry(){
//     return ans;
// }
// };

// // recurda restar uno el ingresar los nodos, estan indexados desde 1 en el problema
// int main(){
//     int T; cin >> T;
//     int N, K;

//     for(int t = 0; t < T; t++){
//         cin >> N >> K;
//         vector < vector <int> > edges(N);
//         int a, b;

//         for(int i = 0; i < N-1; i++){
//             cin >> a >> b;
//             edges[a].push_back(b);
//         }

//         ChristmasTree CT(K, edges);

//         cout << CT.ansqry() << endl;
//     }
// }

// // # include <bits/stdc++.h>
// # include <iostream>
// # include <vector>
// # include <algorithms>

// using namespace std;


// struct ChristmasTree{

//     struct Node{
//         int childs = 0;
//         int subtree = 0;
    
//         bool operator<(const Node &other) const {
//             return subtree < other.subtree;
//         }
//     };

//     int N; int K;
//     int ans;
//     vector< Node > tree;
//     vector< vector <int> > edges;
//     vector< set <int> > edgSet;


//     ChristmasTree(int _K, const vector< vector <int> > &_edges){
//         N = _edges.size();
//         K = _K;

//         tree.resize(N);
//         edges = _edges;
//         edgSet.resize(N);

//         // for(int i = 0; i < N; i++){
//         //     for(const auto nd : edges[i]){
//         //         edgSet[i].insert({nd, 0});
//         //     }
//         // }

//         buildCT();
//     }

// void buildCT(){
//     // vector <int> visited(N, 0); 
//     // visitDFS(0, 0, visited);
//     int val = visitDFS(0, K);
    
//     return;
// }

// // void visitDFS(int nd, int parent, vector <int> &visited){
// int visitDFS(int nd, int K){
//     // cout << "Entrando a nodo " << nd << endl;

//     if(edges[nd].size() < K ) return;

//     for(const auto &child : edges[nd]){ 
//         tree[nd].childs += 1; // cout << "tree[" << nd << "].childs: " << tree[nd].childs << endl;
//         edgSet[nd].insert({child, visitDFS(child, K)});
//         tree[nd].subtree += (1 + tree[child].subtree); // cout << "tree[" << nd << "].subtree: " << tree[nd].subtree << endl;
//     }

//     while (tree[nd].childs > K){
//         if (!edgSet[nd].empty()) {
//             tree[nd].childs -= 1; tree[nd].subtree[edgSet[nd][0].first()]; 
//             edgSet[nd].erase(edgSet[nd].begin());
//         }
//     }
    
//     // cout << "Saliendo del nodo " << nd << " con valor " << tree[nd].subtree << endl;
//     return tree[nd].subtree;

// }

// int ansqry(){
//     return tree[0].subtree + 1;
// }
// };

// // recurda restar uno el ingresar los nodos, estan indexados desde 1 en el problema
// int main(){
//     int T; cin >> T;
//     int N, K;
    
//     vector <int> sol;

//     for(int t = 0; t < T; t++){
//         cin >> N >> K;
//         vector < vector <int> > edges(N);
//         int a, b;

//         for(int i = 0; i < N-1; i++){
//             cin >> a >> b;
//             edges[a-1].push_back(b-1);
//         }

//         ChristmasTree CT(K, edges);
        
//         sol.push_back(CT.ansqry());
//         // cout << "Case " << t << ": " << CT.ansqry() << endl;
//     }
    
//     int t = 1;

//     for(const auto s : sol){
//         cout << "Case " << t << ": " << s << endl;
//         t++;
//     }

// }

// Input:
// 2
// 27 2
// 1 2
// 1 3
// 1 4
// 4 5
// 4 6
// 6 7
// 6 8
// 6 9
// 2 12
// 2 10
// 2 11
// 12 15
// 12 16
// 10 13
// 10 14
// 13 25
// 13 26
// 11 17
// 11 18
// 11 19
// 18 20
// 18 21
// 19 22
// 19 23
// 19 24
// 13 27
// 1 100

// Expected Output 
// Case 1: 19
// Case 2: 1

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