#include <bits/stdc++.h>

using namespace std;

class myString{
    string s; int n;

    vector<long long> hashed_prefixes;
    vector<long long> pi;

    const int p = 33;
    const int m = 1000000007;

    bool operator<(int k, int l, int n) const {
        return compare(k, l, n);
    }
    
    void getPi(){
        pi[0] = 1;
        for (int i = 1; i < s.size(); i++)
            pi[i] = (pi[i-1] * p) % m;
    }
    
    void getHashPfx() {
        for (int i = 0; i < s.size(); i++)
            hashed_prefixes[i+1] = (hashed_prefixes[i] + (s[i] - 'a' + 1) * pi[i]) % m;
    }

    bool compare(int k, int l, int n){
        int idx = getIdx(k, l, n);
        if(idx == -1) return true;

        return (s_1[idx] < s_2[idx]);
    }

    int getIdx(int ini_1, int ini_2, int L){ // BS, L = len of str actual to compare
        int idx; if(ini_2 < ini_1) swap(ini_1, ini_2); // so ini_1 is always the first

        long long hs_1 = getHashVal(ini_1, L), hs_2 = getHashVal(ini_2, L);

        if(L < ini_1) return -1;
        if(hs_1 != hs_2){
            if(getHashVal(ini_1, L-1) != getHashVal(ini_2, L-1)) return L; // L is a lenght so -1
            idx = getIdx(ini_1, ini_2, L-L/2);
        }
        else idx = getIdx(ini_1, ini_2, L+L/2);

        return idx;
    }

public:
    myString(const string &_s){
        s = _s + _s;
        n = s.size();
        hashed_prefixes.assign(s.size() + 1, 0);
        pi.resize(s.size());

        getPi();
        getHashPfx();
    }

    long long getHashVal(int i, int l){
        // cout << s.substr(i,l);
        long long hashed = (hashed_prefixes[i + l] + m - hashed_prefixes[i]) % m; // hp[0] = 0 y hp[1] corresponde a s[0]
        hashed = (hashed * pi[n-i-1]) % m;
        return hashed;
    }

    // int solve(){
    //     int maxIdx = 0;
    //     for(int i = 0; i < n; i++){
    //         if(s_max < s_i) maxIdx = i;
    //     }
    //     return maxIdx;
    // }
};

int main(){
    string _s; cin >> _s;
    myString s(_s);

    s.solve();
}