# include <bits/stdc++.h>

using namespace std;

class Password{
    string s; int n;
    vector<long long> hashed_prefixes;
    vector<long long> pi;

    const int p = 33;
    const int m = 1000000007;

void getPi(){
    pi[0] = 1;
    for (int i = 1; i < s.size(); i++)
        pi[i] = (pi[i-1] * p) % m;
}

void getHashPfx() {
    
    for (int i = 0; i < s.size(); i++)
        hashed_prefixes[i+1] = (hashed_prefixes[i] + (s[i] - 'a' + 1) * pi[i]) % m;

    // map<string, long long> distinct;

    // // Cycle over substring lengths
    // for (int l = 1; l <= n; l++) {
    //     // Cycle over starting positions
    //     for (int i = 0; i <= n - l; i++) {
    //         long long hashed = (hashed_prefixes[i + l] + m - hashed_prefixes[i]) % m; // hp[0] = 0 y hp[1] corresponde a s[0]
    //         // To compare hashed values, set them all to power pˆ{n-1}
    //         // As the difference above is the hash multiplies by pˆi
    //         // we multiply by pˆ{n-1-i}
    //         hashed = (hashed * pi[n-i-1]) % m;
    //         distinct[s.substr(i, l)] = hashed;
    //     }
    // }
}
public:
long long getHashVal(int i, int l){
    // cout << s.substr(i,l);
    long long hashed = (hashed_prefixes[i + l] + m - hashed_prefixes[i]) % m; // hp[0] = 0 y hp[1] corresponde a s[0]
    hashed = (hashed * pi[n-i-1]) % m;
    return hashed;
}

int BSTL(int L){ // binarySearchTheLenght
    // si no funcionó para ninguna len
    // cout << L << endl;
    if(L == 0) return L; 

    if(worksFor(L)){
        // cout << "funcionó para " << L << endl;
        if(!worksFor(L+1)) return L;
        L = BSTL(L + L/2);
    }
    else{
        if(worksFor(L-1)) return L-1;
        L = BSTL(L - L/2);
    }

    return L;
}

bool worksFor(int L){
    // cout << "comparando: " << s.substr(0,L) << " con " << s.substr(n-L, L) << endl;
    long long hpfx = getHashVal(0, L), hsfx = getHashVal(n-L, L);
    if(hpfx != hsfx) return false;

    for(int i = 1; i < n-L; i++)
        if(getHashVal(i, L) == hpfx) return true;

    // cout << " returning false" << endl;
    return false;
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

    // cout << s.substr(0,3) <<":" << endl << pwd.getHashVal(0, 3) << endl << s.substr(s.size()-3, 3) << ":" << endl << pwd.getHashVal(14-3, 3) << endl;
    pwd.solve();
    return 0;
}