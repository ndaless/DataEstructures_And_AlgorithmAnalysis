#include <bits/stdc++.h>

using namespace std;

class myString{
    vector<long long> hashed_prefixes;
    vector<long long> pi;

    const int p = 33;
    const int m = 1000000007;

public:
    string s; int n;

    myString(const string &_s){
        s = _s;
        n = s.size();
        hashed_prefixes.assign(s.size() + 1, 0);
        pi.resize(s.size());

        getPi();
        getHashPfx();
    }

    bool operator<(myString &other){
        int idx = getLen(other, other.s.size()); // calculate the missmatch
        if(idx == -1) return s[0] < other.s[0];

        return (s[idx] < other.s[idx]); // true if s[k, n] <= s[l, n]
    }

    long long getHashVal(int i, int l){
        // cout << s.substr(i,l);
        long long hashed = (hashed_prefixes[i + l] + m - hashed_prefixes[i]) % m; // hp[0] = 0 y hp[1] corresponde a s[0]
        hashed = (hashed * pi[n-i-1]) % m;
        return hashed;
    }

    void solve(){
        int minIdx = 0; int len = n/2;
        for(int idx = 1; idx < len; idx++){
            // cout << " comparando: " << s.substr(idx, len) << "<" << s.substr(minIdx, len);
            if(s.substr(idx, len) < s.substr(minIdx, len)) minIdx = idx;
        }
        cout << minIdx + 1 << endl; // pq problema indexa en 1
        return;
    }

private:
    void getPi(){
        pi[0] = 1;
        for (int i = 1; i < s.size(); i++)
            pi[i] = (pi[i-1] * p) % m;
    }
    
    void getHashPfx() {
        for (int i = 0; i < s.size(); i++)
            hashed_prefixes[i+1] = (hashed_prefixes[i] + (s[i] - 'a' + 1) * pi[i]) % m;
    }

    // returns the lenght of the largest common prefix 
    int getLen(myString &s2, int L){ // BS, L = len of str actual to compare
        long long hs1 = hashed_prefixes[L], hs2 = s2.hashed_prefixes[L];

        if(hs1 != hs2){
            if(hashed_prefixes[L-1] == s2.hashed_prefixes[0, L-1]) return L-1;
            L = getLen(s2, L-L/2);
        }
        else{
            if(hashed_prefixes[L+1] != s2.hashed_prefixes[L+1]) return L;
            L = getLen(s2, L+L/2);
        }
        return L;
    }

    // returns the lenght of the largest common prefix 
    // int getLen(myString &s2, int L){ // BS, L = len of str actual to compare
    //     long long hs1 = getHashVal(0, L), hs2 = s2.getHashVal(0, L);

    //     // if(L <= 0) return -1;
    //     if(hs1 != hs2){
    //         if(getHashVal(0, L-1) == s2.getHashVal(0, L-1)) return L-1;
    //         L = getLen(s2, L-L/2);
    //     }
    //     else{
    //         if(getHashVal(0, L+1) != s2.getHashVal(0, L+1)) return L;
    //         L = getLen(s2, L+L/2);
    //     }
    //     return L;
    // }

};

int main(){
    int T; cin >> T;
    for(int t = 0; t<T; t++){
        string _s; cin >> _s;
        myString s(_s + _s);
        s.solve();
    }
    return 0;
}