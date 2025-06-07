#include <bits/stdc++.h>

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

void buildGraph(){
        
    }

int main(){
    int T; cin >> T;

    for(int t = 0; t < T; t++){
        string line; string name, party, club;
        cin.ignore(); getline(cin, line); getline(cin, line);
        while(!line.empty()){
            vector<string> clubs;

            istringstream tokens(line);
            tokens >> name >> party;
            while(tokens >> club)
                clubs.push_back(club);

            for(const auto c : clubs){
                cout << c << ' ';
            }cout << endl;

            getline(cin, line);
        }
    }

    return 0;
}