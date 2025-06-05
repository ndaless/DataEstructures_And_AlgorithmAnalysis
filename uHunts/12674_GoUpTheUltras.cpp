#include <bits/stdc++.h>

using namespace std;

struct SparceTable {
    int max_d = 50000;

    int N;
    vector< int > vals; 
    // vector< vector<int> > edges;

    // vector< int > parents; // indice del padre de cada nodo
    // vector< int > depths; // profundidad de cada nodo
    // vector< long long > sums_tr; // suma a raiz de cada nodo

    vector< vector<long long> > st;
    // vector< vector<int> > jump_ptr;

    // vector< int > mylogs;



// F U N C I O N E S   A U X I L I A R E S

SparceTable(const vector<int> _vals){
    vals = _vals;
    // edges = _edges;

    N = _vals.size();

    // depths.resize(N);
    // sums_tr.resize(N);
    // parents.resize(N);
    // mylogs.resize(max_d + 1);

    // construimos preproceso de logaritmos
    // buildLOGS();

    // jump_ptr.assign(mylogs[N]+1, vector<int>(N + 1, -1));
    st.assign(log2(N)+1, vector<long long>(N + 1, LLONG_MAX));

    // DFS para llenar profundidades, padres, sums_tr y primera fila de ST y JumpPtr
    // DFS();

    // construimos la sparce table de jump pointers y sumas
    // buildJumpPtr();
    buildST();

}

// void DFS(){
//     vector <int> visited(N, 0); 
//     visitDFS(0, 0, visited);
// }

// void visitDFS(int nd, int parent, vector <int> &visited){
//     visited[nd] = 1;
    
//     if(nd == 0){
//         depths[nd] = 0;
//         sums_tr[nd] = vals[nd];
//         parents[nd] = -1;
//         jump_ptr[0][nd] = -1;
//     }

//     else{
//         depths[nd] = depths[parent] + 1;
//         sums_tr[nd] = sums_tr[parent] + vals[nd];
//         parents[nd] = parent;
//         jump_ptr[0][nd] = parent;
//     }

//     st[0][nd] = vals[parent];
    
//     for(const auto &child : edges[nd]){ 
//         if(visited[child] == 0){
//             visitDFS(child, nd, visited);
//         }
//     }

//     return;

// }


// void buildLOGS() {
//     mylogs[0] = -1;
//     for (int i = 1; i <= max_d; i++) {
//         mylogs[i] = mylogs[i / 2] + 1;
//     }
// }


// void buildJumpPtr(){
//     int k = 1; int jump = pow(2, k);

//     // llenamos las log N + 1 filas
//     while(k <=  mylogs[N]){
//         // de cada nodo
//         for(int nd = 0; nd < N; nd++){ 
//             // con los indices de los padres a distancia 2^k
//             if(pow(2, k) <= depths[nd]) jump_ptr[k][nd] = jump_ptr[k-1][jump_ptr[k-1][nd]];  
//         }
//         k++;
//         jump = pow(2, k);
//     }
    
//     return;
// }


void buildST(){
    int k = 1; // int jump = pow(2, k);

    // llenamos las log N + 1 filas
    while(k <= log2(N)){
        // de cada punto
        for(int i = 0; i < N; i++){
            st[k][i] = st[k-1][i] + st[k-1][?];
        }
        k++;
        // jump = pow(2, k);
    }
}


// void printSPT(){
//     for(int i = 0; i<mylogs[N]; i++){
//         for(int j = 0; j<N; j++){
//             cout << st[i][j] << " ";
//         }
//         cout << endl;
//     }
// }


// void printJPTS(){
//     for(int i = 0; i<mylogs[N]; i++){
//         for(int j = 0; j<N; j++){
//             cout << jump_ptr[i][j] << " ";
//         }
//         cout << endl;
//     }
// }

public:


long long qry(int nd, int d){

    if(d == 0) return vals[nd];
    if(d > depths[nd]) return sums_tr[nd];

    long long sum = vals[nd]; 
    int jump = mylogs[d];

    while(jump < d && d > 0){
        sum += st[jump][nd]; // sumamos la suma del mayor salto posible
        nd = jump_ptr[jump][nd]; // nos movemos al ultimo indice sumado
        d -= pow(2, jump);  // d = a distancia que nos falta por saltar
        jump = mylogs[d]; // jump = maximo salto desde nuestro nuevo nd
    }
    return sum;
}

};

int main(){
    int N;
    while(cin >> N){
        // get the points
        vector<int> points(N);
        for(int i = 0; i < N; i++){
            cin >> points[i];
        }

        // identificamos los picos
        vector<int> peaks;
        if(points[1] < points[0])
            peaks.push_back(0);
        for(int i = 1, i < N-1; i++){
            if(points[i-1] < points[i] && points[i] < points[i+1])
                peaks.push_back(N-1);
        }
        if(points[N-2] < points[N-1])
            peaks.push_back(N-1);
        
    }

    return 0;
}