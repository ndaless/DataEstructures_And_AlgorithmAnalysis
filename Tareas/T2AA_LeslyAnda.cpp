#include <bits/stdc++.h>
#include <cmath>
#include <vector>
#include <climits> 

#define optimizar_io

using namespace std;

struct SparceTable {
    int max_d = 50000;

    int N;
    vector< int > vals; 
    vector< vector<int> > edges;

    vector< int > parents; // indice del padre de cada nodo
    vector< int > depths; // profundidad de cada nodo
    vector< long long > sums_tr; // suma a raiz de cada nodo

    vector< vector<long long> > st;
    vector< vector<int> > jump_ptr;

    vector< int > mylogs;



// F U N C I O N E S   A U X I L I A R E S

SparceTable(const vector<int> _vals, const vector< vector<int> > _edges){
    vals = _vals;
    edges = _edges;

    N = _vals.size();

    depths.resize(N);
    sums_tr.resize(N);
    parents.resize(N);
    mylogs.resize(max_d + 1);

    // construimos preproceso de logaritmos
    buildLOGS();

    jump_ptr.assign(mylogs[N]+1, vector<int>(N + 1, -1));
    st.assign(mylogs[N]+1, vector<long long>(N + 1, LLONG_MAX));

    // DFS para llenar profundidades, padres, sums_tr y primera fila de ST y JumpPtr
    DFS();

    // construimos la sparce table de jump pointers y sumas
    buildJumpPtr();
    buildST();

}

void DFS(){
    vector <int> visited(N, 0); 
    visitDFS(0, 0, visited);
}

void visitDFS(int nd, int parent, vector <int> &visited){
    visited[nd] = 1;
    
    if(nd == 0){
        depths[nd] = 0;
        sums_tr[nd] = vals[nd];
        parents[nd] = -1;
        jump_ptr[0][nd] = -1;
    }

    else{
        depths[nd] = depths[parent] + 1;
        sums_tr[nd] = sums_tr[parent] + vals[nd];
        parents[nd] = parent;
        jump_ptr[0][nd] = parent;
    }

    st[0][nd] = vals[parent];
    
    for(const auto &child : edges[nd]){ 
        if(visited[child] == 0){
            visitDFS(child, nd, visited);
        }
    }

    return;

}


void buildLOGS() {
    mylogs[0] = -1;
    for (int i = 1; i <= max_d; i++) {
        mylogs[i] = mylogs[i / 2] + 1;
    }
}


void buildJumpPtr(){
    int k = 1; int jump = pow(2, k);

    // llenamos las log N + 1 filas
    while(k <=  mylogs[N]){
        // de cada nodo
        for(int nd = 0; nd < N; nd++){ 
            // con los indices de los padres a distancia 2^k
            if(pow(2, k) <= depths[nd]) jump_ptr[k][nd] = jump_ptr[k-1][jump_ptr[k-1][nd]];  
        }
        k++;
        jump = pow(2, k);
    }
    
    return;
}


void buildST(){
    int k = 1; int jump = pow(2, k);

    // llenamos las log N + 1 filas
    while(k <= mylogs[N]){
        // de cada nodo
        for(int nd = 0; nd < N; nd++){
            // con la suma de los padres 2^k ancestros
            if(pow(2, k) <= depths[nd]) st[k][nd] = st[k-1][nd] + st[k-1][jump_ptr[k-1][nd]];
        }
        k++;
        jump = pow(2, k);
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

    ios_base::sync_with_stdio(0);cin.tie(0);

    int N, Q;
    cin >> N >> Q;

    vector<int> iniVals;
    int val;

    for (int i=0; i<N; i++){
        cin >> val;
        iniVals.push_back(val);
    }

    int a, b;
    vector< vector<int> > edges(N);

    for (int i=0; i<N-1; i++){
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }    

    SparceTable spt(iniVals, edges);

    vector<long long> qrys; int nd; int d; 

    for (int i = 0; i < Q; i++){
        cin >> nd >> d;
        qrys.push_back(spt.qry(nd, d));
    }
    
    for (int i = 0; i < Q; i++){
        cout << qrys[i] << endl;
    }
    
    return 0;
}


// // PRIMERA VERSION

// // #include <bits/stdc++.h>
// // #include <cmath>
// // #include <vector>

// // #define optimizar_io

// // using namespace std;

// // // #define MAX_SUM (100000 * 50000 +1)

// // // struct Node{
// // //     int val;
// // //     int parent;
// // //     int depth;
// // //     long long sum_root;
// // // };

// // struct SparceTable {
// //     int max_d = 5000;

// //     int N;
// //     vector< int > vals; 
// //     vector< vector<int> > edges;

// //     vector< int > parents;
// //     vector< int > depths;
// //     vector< long long > sums_tr;

// //     vector< vector<long long> > st;
// //     vector< vector<int> > jump_ptr;

// //     vector< int > mylogs;



// // // F U N C I O N E S   A U X I L I A R E S

// // SparceTable(const vector<int> _vals, const vector< vector<int> > _edges){
// //     vals = _vals;
// //     edges = _edges;

// //     N = _vals.size();

// //     depths.resize(N);
// //     sums_tr.resize(N);
// //     parents.resize(N);
// //     mylogs.resize(max_d + 1);

// //     // construimos preproceso de logaritmos
// //     buildLOGS();

// //     // construimos la matriz de jump pointers (con una funcion, la pasamos por referencia)
// //     jump_ptr.assign(N, vector<int>(mylogs[N] + 1, -1));
// //     st.assign(N, vector<long long>(mylogs[N], LONG_LONG_MAX));
// //     // st.resize(N);
// //     // for (int nd = 0; nd < N; ++nd) {
// //     //     jump_ptr[nd].resize(mylogs[N], -1); // el -1 indica que salto > profundidad
// //     //     st[nd].resize(mylogs[N], LONG_LONG_MAX);
// //     // }

// //     DFS();
// //     buildJumpPtr();
// //     buildST();

// // }

// // void DFS(){
// //     vector <int> visited(N, 0); 
// //     visitDFS(0, 0, visited);
// // }

// // void visitDFS(int nd, int parent, vector <int> &visited){
// //     visited[nd] = 1;
    
// //     if(nd == 0){
// //         depths[nd] = 0;
// //         sums_tr[nd] = vals[nd];
// //         parents[nd] = 0;
// //     }

// //     else{
// //         depths[nd] = depths[parent] + 1;
// //         sums_tr[nd] = sums_tr[parent] + vals[nd];
// //         parents[nd] = parent;
// //     }

// //     //jump_ptr[0][nd] = parent; // si es asi o es al reves?
// //     jump_ptr[nd][0] = parent;
// //     st[0][nd] = vals[parent];
    
// //     for(const auto &child : edges[nd]){ 
// //         if(visited[child] == 0){
// //             visitDFS(child, nd, visited);
// //         }
// //     }

// //     return;

// // }

// // // // ARREGLAR ESTO PARA HACERLO RECURSIVO ( D O N E )
// // // int mylog(int i){
// // //     if(i == 0 || i == 1){
// // //         return 0;
// // //     }
    
// // //     return mylogs[i/2] + 1;
// // // }

// // // // AQUI HAY UN EEROR EN EL i = 0 ( A R R E G L A D O )
// // // void buildLOGS(){ // en este caso en 50000 // este solo se usa para d!=0
// // //     // (int max_d, vector<int> &mylogs)

// // //     mylogs[0] = -1;
// // //     for(int i = 1; i <= max_d; i++){
// // //         mylogs.push_back(mylog(i));
// // //     }
// // //     return;
// // // }

// // int mylog(int i) {
// //     return mylogs[i]; // Solo acceder al valor precalculado
// // }

// // void buildLOGS() {
// //     mylogs[0] = -1;
// //     for (int i = 1; i <= max_d; i++) {
// //         mylogs[i] = mylogs[i / 2] + 1; // Log2(i) precomputado
// //     }
// // }

// // void buildJumpPtr(){
// //     // (vector< vector<int> > vals, vector< vector<int> > &jump_ptr)
// //     int k = 1; int jump = pow(2, k);

// //     while(jump < mylog(N)){ // AQUI SI ES MEJOR O IGUAL?
// //         for(int nd = 0; nd < N; nd++){
// //             if(pow(2, k) <= depths[nd]) jump_ptr[k][nd] = jump_ptr[k-1][jump_ptr[k-1][nd]];
// //         }
// //         k++;
// //         jump = pow(2, k);
// //     }
// //     return;

// // }

// // // ARREGLAR ESTA FUNCION, REVISAR EL LLENADO DEL PRIMER NIVEL EN DFS (DONE)
// // void buildST(){
// //     // (vector< vector<int> > vals, vector< vector<long long> > &st, vector< vector<int> > ancestros)
// //     int k = 1; int jump = pow(2, k);

// //     while(jump < mylog(N)){ // AQUI SI ES MEJOR O IGUAL? 
// //         for(int nd = 0; nd < N; nd++){
// //             if(pow(2, k) <= depths[nd]) st[k][nd] = st[k-1][nd] + st[k-1][st[k-1][nd]]; // AQUI ESTA SUMANDO EL NODO? 
// //         }
// //         k++;
// //         jump = pow(2, k);
// //     }

// // }

// // void printMAT(){
// //     for(int i = 0; i<mylogs[N]; i++){
// //         for(int j = 0; j<N; j++){
// //             cout << st[i][j];
// //         }
// //         cout << endl;
// //     }
// // }

// // public:

// // // PENDIENTE
// // long long qry(int nd, int d){

// //     if(d == 0) return vals[nd];
// //     if(d > depths[nd]) return sums_tr[nd];

// //     long long sum = vals[nd]; 
// //     // sum += st[mylogs[d]][nd]; // AUN NO SE SI SUMARLE EL NODO O NO PQ NO SE SI LO ESTA SUMANDO LA ST
// //     // return sum += qry(parents[jump_ptr[mylogs[d]][nd]], d-mylogs[d]);

// //     int jump = mylogs[d];

// //     while(jump < d && d > 0){
// //         sum += st[jump][nd];
// //         nd = jump_ptr[jump][nd];
// //         d -=jump;
// //         jump = mylogs[d];
// //     }
// //     return sum;
// // }

// // };

// // int main(){

// //     // leemos entradas y construimos el arbol (la lista de adyasencias)
// //     ios_base::sync_with_stdio(0);cin.tie(0);

// //     int N, Q;
// //     cin >> N >> Q;

// //     vector<int> iniVals;
// //     int val;

// //     for (int i=0; i<N; i++){
// //         cin >> val;
// //         iniVals.push_back(val);
// //     }

// //     int a, b;
// //     vector< vector<int> > edges(N);

// //     for (int i=0; i<N-1; i++){
// //         cin >> a >> b;
// //         edges[a].push_back(b);
// //         edges[b].push_back(a);
// //     }    

// //     SparceTable spt(iniVals, edges);

// //     // leemos y respondemos las preguntas (crear funcion que responda la pregunta, pasar cosas por referencia podria ayudar)

// //     int nd; int d;

// //     vector<long long> qrys;

// //     for (int i = 0; i < Q; i++){
// //         cin >> nd >> d;
// //         qrys.push_back(spt.qry(nd, d));
// //     }
    
// //     for (int i = 0; i < Q; i++){
// //         cout << qrys[i] << endl;
// //     }
    
// //     return 0;
// // }

// // // SEGURO SE ESTA QUEDANDO ATRAPADO EN UN CICLO
