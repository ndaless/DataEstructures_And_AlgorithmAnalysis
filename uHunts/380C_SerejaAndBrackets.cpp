#include <bits/stdc++.h>

using namespace std;

class ST{
    vector<tuple<int, int, int>> st;
    // string s; 
    vector<int> sVec;
    int N;
    
    ST(const string& _s){
        // cambiamos los caracteres por enteros
        for(const auto c : _s){
            if(c == '(')
                sVec.push_back(1);
            else
                sVec.push_back(-1);
        }
        N = sVec.size();
        st.assign(4*N); // si es 4n? que es mejor, vector o tupla?
        build(0, 0, N-1);
    }

    void build(int nd, int tl, int tr){ // el vector se puede llamar con el string? necesitamos el vector?
        if(tl == tr){
            if(sVec[tl] == '('){
                st[v] = make_tuple(0, 1, 0);
            }
            else{
                st[v] = make_tuple(0, 0, 1);
            }
        } 
        
        else{
            int tm = (tl + tr) / 2;

            build(v*2, tl, tm);
            build(v*2+1, tm+1, tr);

            if(get<1>(st[v*2]) == 0){ // si los de la izquierda no son abiertos solo copiamos los valores
                get<1>(st[v]) = get<1>(st[v*2]) + get<1>(st[v*2+1]);
                get<2>(st[v]) = get<2>(st[v*2]) + get<2>(st[v*2+1]);
                get<0>(st[v]) = get<0>(st[v*2]) + get<0>(st[v*2+1]);
            }

            // sumamos positivos izquierda y negativos derecha
            int sum = get<1>(st[v*2]) + get<2>(st[v*2+1]); 
            int minVal = min(abs(get<1>(st[v*2])), abs(get<2>(st[v*2+1])))

            get<1>(st[v]) = 
            get<2>(st[v]) = 
            if()
                get<0>(st[v]) = get<0>(st[v*2]) + get<0>(st[v*2+1]) + min(abs(), abs())
        }
    }



    void solve(){

    }

};

int main(){
    string s; cin >> s;
    int M; cin >> M;

    int l, r;
    for(int m = 0; m < M; m++){
        cin >> l >> r;
        solve(l, r);
    }

    return 0;
}