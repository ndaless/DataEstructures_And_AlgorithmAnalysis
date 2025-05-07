#include <bits/stdc++.h>

using namespace std;

class ST{
    vector<tuple<int, int, int>> st;
    vector<int> sVec;
    int N;
    int count;

    void build(int v, int tl, int tr){ // el vector se puede llamar con el string? necesitamos el vector?
        if(tl == tr){
            if(sVec[tl] == 1){
                // st[v] = make_tuple(0, 1, 0);
                get<1>(st[v]) = 1;
                get<2>(st[v]) = 0;
                get<0>(st[v]) = 0;
            }
            else{
                // st[v] = make_tuple(0, 0, 1);
                get<1>(st[v]) = 0;
                get<2>(st[v]) = 1;
                get<0>(st[v]) = 0;
            }
        } 
        
        else{
            int tm = (tl + tr) / 2;

            build(v*2+1, tl, tm);
            build(v*2+2, tm+1, tr);

            if(get<1>(st[v*2+1]) == 0){ // si no hay abiertos en la izquierda, solo arrastramos los valores
                get<1>(st[v]) = get<1>(st[v*2+1]) + get<1>(st[v*2+2]);
                get<2>(st[v]) = get<2>(st[v*2+1]) + get<2>(st[v*2+2]);
                get<0>(st[v]) = get<0>(st[v*2+1]) + get<0>(st[v*2+2]);
            } else{

            // sumamos positivos izquierda y negativos derecha
            // int sum = get<1>(st[v*2+1]) + get<2>(st[v*2+2]); 
            // obtenemos cantidad de pares formados
            int pares = min(abs(get<1>(st[v*2+1])), abs(get<2>(st[v*2+2])));

            // actualizamos pares formados y quitamos los () usados
            get<1>(st[v]) = get<1>(st[v*2+1]) - pares + get<1>(st[v*2+2]);
            get<2>(st[v]) = get<2>(st[v*2+1]) + get<2>(st[v*2+2]) - pares;
            get<0>(st[v]) = get<0>(st[v*2+1]) +  get<0>(st[v*2+2]) + pares; 
            }
        }
    }

public:
    ST(const string& _s){
        // cambiamos los caracteres por enteros
        for(const auto c : _s){
            if(c == '(')
                sVec.push_back(1);
            else
                sVec.push_back(-1);
        }       
        N = sVec.size();
        st.resize(4*N); // si es 4n? que es mejor, vector o tupla?
        build(0, 0, N-1);
        count = 0;
    }

    void printST(){
        for(const auto tup : st){
            cout << get<0>(tup) << ' ' << get<1>(tup) << ' ' << get<2>(tup) << endl;
        }
    }

    tuple<int, int, int> ans(int v, int tl, int tr, int l, int r){
        // cout << "calculando answare en st en nodo " << v << "," << l << ","  << r << endl;
        count ++;
        if(count == 10) 
            return make_tuple(0, 0, 0);
        if(l > r) // 
            return make_tuple(0, 0, 0);

        if(l == tl && r == tr){ // si llegamos a un nodo que tiene info toda necesaria
            return st[v];
        }

        int tm = (tl + tr) / 2;
        tuple<int, int, int> left = ans(v*2+1, tl, tm, l, min(r, tm));
        tuple<int, int, int> right = ans(v*2+2, tm + 1, tr, max(l, tm + 1), r);

        if(get<1>(left) == 0){
            return make_tuple(get<0>(left) + get<0>(right), 
                              get<1>(left) + get<1>(right), 
                              get<2>(left) + get<2>(right));
        }

        int pares = min(abs(get<1>(left)), abs(get<2>(right)));
        return  make_tuple(get<0>(left) +  get<0>(right) + pares,
                           get<1>(left) - pares +  get<1>(right),
                           get<2>(left) +  get<2>(right) - pares); 
    }

    int ans(int l, int r){
        tuple<int, int, int> answare = ans(0, 0, N-1, l, r);
        return 2*get<0>(answare);
    }

};

int main(){
    string s; cin >> s;
    ST st(s);
    // st.printST();

    int M; cin >> M;
    int l, r;

    for(int m = 0; m < M; m++){
        cin >> l >> r;
        cout << st.ans(l-1, r-1) << endl;
    }

    return 0;
}