# include <bits/stdc++.h>

// # include <iostream>
// # include <vector>
// # include <queue>

using namespace std;

struct Edge{
    long long c; // capacity
    long long f; // flow
    int to;
};

class FordFulkerson{

public:
    FordFulkerson(vector < vector <pair <int, long long> > > &graph) : g(graph){}

    long long getMaxFlow(int s, int t){
        init();
        long long f = 0;
        while(findAndUpdate(s, t, f)){}
        return f;
    }

private:
    vector < vector <pair <int, long long> > > g; //graph(to, capacity)
    vector < Edge > edges; // list of edges (including the inverse ones)
    vector <vector <int> > eIndexes; // indexes of edges going out frmo each vertex

    void init(){ // crates our flow graph
        edges.clear();
        eIndexes.clear(); eIndexes.resize(g.size());
        for(int i = 0; i < g.size(); i++){
            for(int j = 0; j < g[i].size(); j++){
                edges.push_back({g[i][j].second, 0, g[i][j].first});
                edges.push_back({0, 0, i});
                eIndexes[i].push_back(edges.size() - 2);
                eIndexes[g[i][j].first].push_back(edges.size()-1);
            }

        }

    }

    bool findAndUpdate(int s, int t , long long&flow){
        //Encontrar camino de s a t con BFS
        queue<int> pending;
        //Desde donde llego y con que arista
        vector< pair<int , int> > from(g.size() , make_pair(-1, -1));
        pending.push(s);
        from[s] = make_pair(s, -1);
        bool found = false;

        while(pending.size() && (!found)){
            int u = pending.front(); pending.pop();
            for (int i = 0; i < eIndexes[u]. size(); i++){
                int eI = eIndexes[u][i];
                if ((edges[eI].c > edges[eI].f) &&
                    (from[edges[eI].to].first == -1)){
                        from[edges[eI].to] = make_pair(u, eI);
                        pending.push(edges[eI].to);
                        if (edges[eI].to == t){
                            found = true;
                        }
                }
            }
        }
        
        if (!found) return false;
        //Encontrar cap. minima del camino de aumento
        long long uFlow=LLONG_MAX;
        int current = t ;
        while(current != s){
            uFlow = min(uFlow, edges[from[current].second].c-
                               edges[from[current].second].f);
            current = from[current].first ;
        }
        current = t ;
        //Actualizar flujo
        while(current != s){
            edges[from[current].second].f += uFlow;
            edges[from[current].second^1].f -=uFlow; //Arista inversa
            current = from[current]. first;
        }
        flow += uFlow;
        return true;
    }

};

void builBipartiteG(int N, vector< vector<int> > closure, vector < vector <pair <int, long long> > > &graph){
    // conectamos s con todos los nodos out
    for(int nd = 0; nd < N; nd ++){
        graph[0].push_back(make_pair(nd+1, 1));
    }
    // conectamos los nodos out con los in
    for(int nd = 0; nd<N; nd++){
        for(const auto elem : closure[nd]){
            // las columnas en [1, N] representan a los N nodos out
            // las columnas en [N+1, 2N] representan a los N nodos out
            graph[nd+1].push_back(make_pair(elem+1+N, 1));
        }
    }
    // conectamos in (en las posiciones [N+1, 2N]) con t
    for(int nd = 0; nd < N; nd ++){
        graph[nd+1+N].push_back(make_pair(graph.size()-1, 1));
    }
}

void buildClosure(int nd, vector <vector<int> > edges, vector <vector<int> > &closure, vector<int> &builded){ // no estaba pasando builded por referencia (&), so no lo estaba editando
    builded[nd] = 1;
    for(const auto child: edges[nd]){
        if(builded[child] != 1){
            // si su cerradura no se ha construido, la construimos
            buildClosure(child, edges, closure, builded);
        }
        // anadimos el hijo a la cerradura del nodo, y tambien anadimos a todos los hijos del hijo
        closure[nd].push_back(child);
        for(const auto reach : closure[child]) {
            closure[nd].push_back(reach);
        }

        // if(builded[child] != 1){
        //     buildClosure(child, edges, closure, builded);
        //     closure[nd].push_back(child); // cout << " adding " << child << "to closure of" << nd << endl;
        //     for(const auto reach : closure[child]) {
        //         // cout << "  adding " << reach << "to closure of" << nd << endl;
        //         closure[nd].push_back(reach);
        //     }
        // }
    }
}

void DFS(vector <vector<int> > edges, vector <vector<int> > &closure){
    int N = edges.size();
    vector<int> builded(N, 0);
    // construimos la cerradura de cada nodo recursivamente
    for(int nd = 0; nd < edges.size(); nd++){
        if(builded[nd] != 1) buildClosure(nd, edges, closure, builded);
    }

}

int main(){

    int N, M; cin >> N >> M;

    // ifstream entrada("drumuri2.in");
    // ofstream salida("drumuri2.out");

    // int N, M; entrada >> N >> M;
    vector < vector <int> > edges(N);
    
    int a, b;
    for(int i = 0; i<M; i++){
        // entrada >> a >> b;
        cin >> a >> b;
        edges[a-1].push_back(b-1);
    }
    
    vector <vector<int> > closure(N); 
    DFS(edges, closure);
    // vector <vector<int> > graph(N+2, vector<int>(N+2, 0));
    // vector <vector<int> > graph(2*N+2, vector<int>(2*N+2, 0));
    vector < vector <pair <int, long long> > > graph(2*N+2);

    // int graph [N+2][N+2];                    // como no conocemos N en tiempo de compilacion y no se
                                                // como pasarle esto a una funcion, usare vector jaja

    builBipartiteG(N, closure, graph);
    
    FordFulkerson FF(graph);
    long long maxFlow = FF.getMaxFlow(0, graph.size()-1);

    cout << N-maxFlow << endl;
    // salida << N-maxFlow << endl;

    // entrada.close();
    // salida.close();

    return 0;

}