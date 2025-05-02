# include <bits/stdc++.h>

using namespace std;

class Password{
    string s; int n;
    vector<long long> hashed_prefixes;
    vector<long long> pi;

    const int p = 31;
    const int m = 1000000007;

void getPi(){ // O(n)
    pi[0] = 1;
    for (int i = 1; i < s.size(); i++)
        pi[i] = (pi[i-1] * p) % m;
}

void getHashPfx() { // O(n)
    for (int i = 0; i < s.size(); i++)
        hashed_prefixes[i+1] = (hashed_prefixes[i] + (s[i] - 'a' + 1) * pi[i]) % m;
}

public:
long long getHashVal(int i, int l){ // O(1)
    long long hashed = (hashed_prefixes[i + l] + m - hashed_prefixes[i]) % m; // hp[0] = 0 y hp[1] corresponde a s[0]
    hashed = (hashed * pi[n-i-1]) % m;
    return hashed;
}

int BSTL(int L){ // binarySearchTheLenght O(log n)
    if(L == 0) return L; 

    if(worksFor(L)){ // si para la longitud L la substr es password
        // cout << " funciona para " << s.substr(0, L) << endl;
        if(!worksFor(L+1)){
            // cout << " no funciona para " << s.substr(0, L+1) << endl;
            return L; // pero para L+1 NO, L es la respuesta
        }
        L = BSTL(L + L/2); // busca una más grande
    }
    else{ // si para la longitud L la substr NO es password
        // cout << " no funciona para " << s.substr(0, L) << endl;
        if(worksFor(L-1)){
            // cout << " funciona para " << s.substr(0, L-1) << endl;
            return L-1; // pero para L+1 SI, L-1 es la respuesta
        }
        L = BSTL(L - L/2); // busca una más pequena
    }

    return L;
}

bool worksFor(int L){ //(O(n))
    long long hpfx = getHashVal(0, L), hsfx = getHashVal(n-L, L);
    // cout << s.substr(0, L) << "-" << hpfx << ", " << s.substr(0, L) << "-" << hsfx << endl;
    if(hpfx != hsfx){
        // cout << "no es sufijo" << endl;
        return false; // si no es sufijo, no funciona
    }
    for(int i = 1; i < n-L; i++)
        if(getHashVal(i, L) == hpfx) return true; // si es pfx, sfx y existe en medio, funciona

    // cout << "no esta en medio" << endl;
    return false; // si es pfx, sfx pero no esta en medio no funciona
}

public:
Password(const string &_s){
    s = _s;
    n = s.size();
    hashed_prefixes.assign(s.size() + 1, 0);
    pi.resize(s.size());

    getPi();
    getHashPfx();
}

void solve(){
    int L = BSTL(2*s.size()/3); // iniciamos con el piso de 2*N/3;
    if(L == 0) cout << "Just a legend" << endl;
    else cout << s.substr(0, L) << endl;
}

};

int main(){
    string s; cin >> s;
    Password pwd(s);

    pwd.solve();
    return 0;
}

// no funciona con nfbdzgdlbjhrlvfryyjbvtsmzacxglcvukmyexdgpuiwvqbnfbdzgdlbjhrlvfryyjbtuomcwbwvlhefnfbdzgdlbjhrlvfryyjb