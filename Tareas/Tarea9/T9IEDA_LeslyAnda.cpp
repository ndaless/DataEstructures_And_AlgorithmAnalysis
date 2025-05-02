# include <bits/stdc++.h>

using namespace std;

int goodSubStrings(const string& s, const string& val, const int& k){
    const int p = 33; // 33
    const int m = 1000000007;

    // precalculamos las potencias (O(n))
    vector <long long> pi(s.size());
    pi[0] = 1;
    for(int i = 0; i< s.size(); i++)
        pi[i] = (pi[i-1]*p) % m;

    // obtenemos los hash y vals de los prefijos (O(n))
    vector <long long> hashedPrefix(s.size()+1, 0);
    for(int i = 0; i < s.size(); i++)
        hashedPrefix[i+1] = (hashedPrefix[i] + (s[i] - 'a' + 1) * pi[i]) % m;

    // obtenemos los vals de los prefijos
    vector <int> goodPrefix(s.size(), 0);

    if (val[s[0] -'a'] == '0'){ // calculate the first value
        goodPrefix[0] = 1;
    } else goodPrefix[0] = 0;

    for(int i = 1; i < s.size(); i++){ // get the prefix values (O(n))
        goodPrefix[i] = goodPrefix[i-1];
        if (val[s[i] -'a'] == '0'){
            goodPrefix[i]++;
        }
    }
    
    set<long long> disctint;
    
    // cycle over substring lenghts (O(n))
    for(int l = 1; l <= s.size(); l++){ 
        // cycle over string position (O(n))
        for(int i = 0; i <= s.size() - l; i++){
            long long hashed = (hashedPrefix[i+l] + m - hashedPrefix[i]) % m; // +m?
            // to compare we multiply by p^{n-1-i}
            hashed = (hashed * pi[s.size()-i-1]) % m;
            if(goodPrefix[i+l-1]-goodPrefix[i-1] <= k){
                disctint.insert(hashed); // solo la agregamos si es good substr
            }
        }
    }

    return disctint.size();
}

int main(){
    string s, val; int k;
    cin >> s >> val >> k;

    int sol = goodSubStrings(s, val, k);

    cout << sol << endl;

    return 0;
}