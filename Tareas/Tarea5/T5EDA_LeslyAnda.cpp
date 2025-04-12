# include <iostream>
# include <vector>
#include <deque>

using namespace std;

// template <typename nodeVal> 
class KSJ{
    int N;

    vector <int> vals;
    vector <int> special; // vector que guarda cajas tq con un solo salto regresas
    vector< vector<int> > edges;
    vector< vector<int> > segde;
    deque<int> L; // usamos deque para poder agregar al frente
    vector <int> visAssg; // nos dice si nd ya fue visitado / asigando a una componente
    vector< vector<int> > CC; // Componentes Conexas

public: 

    KSJ(vector <int> _vals, vector< vector<int> > _edges, vector< vector<int> > _segde, vector <int> _special){
        N = _edges.size();

        edges = _edges;
        segde = _segde;
        vals = _vals;
        special = _special;
        
        visAssg.assign(N, 0);
        
        algKSJ();
    } 

void visit(int nd){
    // cout << "entrando a visit" << endl;

    visAssg[nd] = 1;

    for(const auto child:edges[nd]){
        if(visAssg[child] != 1) visit(child);
    }

    L.push_front(nd);

    return;
}

void assign(int nd, int &comp){ // agragara los nodos alcanzables a una misma componente 
    // cout << "entrnado a assign" << endl;

    visAssg[nd] = 1;
    
    for(const auto child : segde[nd]){
        if(visAssg[child] != 1){
            CC[comp].push_back(child);
            assign(child, comp);
        }
    }

}

void algKSJ(){
    // cout << "entrando a algKSJ" << endl;

    // primera DFS
    for(int nd = 0; nd < N; nd++){
        if(visAssg[nd] != 1){
            visit(nd);
        }
    }

    visAssg.assign(N, 0); 
    int comp = 0; int nd;
	
    // segunda DFS en orden de L
    while( !L.empty() ){

        nd = L.front(); // cout << nd << endl;
        if(visAssg[nd] != 1){
            vector< int > root; root.push_back(nd);
            CC.push_back(root);
            assign(nd, comp);
            comp ++;
        } 
        L.pop_front(); // cout << L.front() << endl; 
    }

    return;
}

int ansQry(){ 
    // cout << "entrando a ansQry" << endl;
    int magicBoxes = 0;
    
    // para responder
    for(const auto c : CC){
	// contamos las cajas que estan en un ciclo de dos o mas cajas
        if(c.size() > 1 ) magicBoxes += c.size();
	// si no, pero es una caja especial sumamos
        else if(special[c[0]] == 1) magicBoxes++;
    }
    
    // for(const auto c : CC){
    //     for(const auto nd : c){
    //         cout << nd;
    //     }
    //     cout << endl;
    // }
    
    return magicBoxes;
}


};

int main(){
    int T, N; cin >> T;

    int jump, destination;
    
    for(int t = 0; t<T; t++){
        cin >> N;
        vector <int> vals(N);
        vector <int> special(N, 0);
        vector< vector<int> > edges(N);
        vector< vector<int> > segde(N);
        
        for(int i = 0; i<N; i++){
            cin >> jump; 
            vals[i] = jump; jump++;
            destination = (i+jump)%N; // cada nodo se conectará con la caja que esta despues de las vals[i]
            edges[i].push_back(destination);
            segde[destination].push_back(i);
            if(i == destination) special[i] = 1; // detecta si caemos en la misma caja es una caja especial
        }
        
        KSJ myKSJ(vals, edges, segde, special);
        cout << myKSJ.ansQry() << endl;
    }
    
    return 0;
}
