# include <iostream>
# include <vector>

using namespace std;

void visitDFS(int nd, vector<int> &topoSort, vector< vector<int> > edges, vector<int> visited){
    cout << "entrando a visitDFS" << endl;
    if(nd == 0){
        visited[nd] = 1;
        topoSort.push_back(nd);
        return;
    }

    for(int child = nd-1; child > 0; child--){
        if(edges[nd][child] != -1 ) visitDFS(child, topoSort, edges, visited);
    }

    visited[nd] = 1;
    topoSort.push_back(nd);

    return;
}

vector<int> qrySolve(vector< vector<int> > edges){ // esta quiza necesita ser otra estructura
    cout << "entrando a qrySolve" << endl;
    int N = edges.size(); 
    vector<int> topoSort(N); vector<int> visited(N, 0);

    for(int nd = N-1; nd > 0; nd--){
        if(visited[nd] != 0) visitDFS(nd, topoSort, edges, visited);
    }
    return topoSort;
}


int main(){
    int T, N, M; cin >> T;
    // vector< vector <int> > solution;
    
    cout << "entrando a main" << endl;
    
    for(int t=0; t<T; t++){
        cin >> N >> M;
        int a, b; cin >> a >> b;
        
        vector< vector<int> > edges(N, vector<int>(N, -1));

        for(int i = 1; i<N; i++){
            for(int j = i; j<N; j++){
                if(i == a && j == b){
                    // edges[i][j] = -1;
                    cin >> a >> b;
                }else edges[j][i] = 1;
            }
        }
        
        cout << "se han leído todas las entradas" << endl;
        
        vector <int> sol = qrySolve(edges);

        for(const auto elem : sol){
            cout << elem << " ";
        }
        cout << endl;
        // NO IMPRIME LO Q DEBERIA
    }

}