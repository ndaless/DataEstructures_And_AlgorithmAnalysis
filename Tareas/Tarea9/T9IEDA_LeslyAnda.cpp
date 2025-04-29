# include <bits/stdc++.h>

# include <ext/pb_ds/assoc_container.hpp> // common file
# include <ext/pb_ds/tree_policy.hpp> // including tree_order_statistics_node_update

using namespace std;
using namespace __gnu_pbds;

typedef tree <pair<int, string>, // change type
            null_type,
            less< pair<int, string> >, // change type
            rb_tree_tag,
            tree_order_statistics_node_update> ordered_set;

ordered_set uniqueSubStrings(const string& s){
    const int p = 31; // 33
    const int m = 1000000007;

    // precalculamos las potencias
    vector <long long> pi(s.size());
    pi[0] = 1;
    for(int i = 0; i< s.size(); i++)
        pi[i] = (pi[i-1]*p) % m;

    // obtenemos los hash vals de los prefijos
    vector <long long> hashedPrefix(s.size()+1, 0);
    for(int i = 0; i < s.size(); i++)
        hashedPrefix[i+1] = (hashedPrefix[i] + (s[i] - 'a' + 1) * pi[i]) % m;

    ordered_set disctint;
    
    // cycle over substring lenghts
    for(int l = 1; l <= s.size(); l++){
        // set <long long> allHashed;
        // cycle over string position
        for(int i = 0; i <= s.size() - l; i++){
            long long hashed = (hashedPrefix[i+l] + m - hashedPrefix[i]) % m; // +m?
            // to compare we multiply by p^{n-1-i}
            hashed = (hashed * pi[s.size()-i-1]) % m;
            disctint.insert(make_pair(hashed, s.substr(i, l)));
        }
    }

    return disctint;
}

set<pair<string, int>> uniqueGoodSubStrings(const string& s, const string& val, const int& k){
    // const int p = 31;
    // const int m = 1000000007;

    // // precalculamos las potencias
    // vector <long long> pi(s.size());
    // pi[0] = 1;
    // for(int i = 0; i< s.size(); i++)
    //     pi[i] = (pi[i-1]*p) % m;

    // obtenemos los hash vals de los prefijos
    vector <long long> hashedPrefix(s.size(), 0);
    // calculate the first value
    if (val[s[0] -'a'] == '0'){
        hashedPrefix[0] = 1;
    } else hashedPrefix[0] = 0;

    // get the prefix values
    for(int i = 1; i < s.size(); i++){
        // hashedPrefix[i+1] = (hashedPrefix[i] + (s[i] - 'a' + 1) * pi[i]) % m;
        hashedPrefix[i] = hashedPrefix[i-1];
        if (val[s[i] -'a'] == '0'){
            hashedPrefix[i]++;
        }
    }

    // for(const auto value : hashedPrefix) cout << value << " "; cout << endl;

    set<pair<string, int>> disctint; // aqui
    
    // cycle over substring lenghts
    for(int l = 1; l <= s.size(); l++){
        // set <long long> allHashed;
        // cycle over string position

        for(int i = 0; i <= s.size() - l; i++){
            int hashed;
            if (i == 0) hashed = hashedPrefix[l-1];
            else hashed = (hashedPrefix[i+l-1] - hashedPrefix[i-1]);
            if(hashed > k) continue;
            disctint.insert(make_pair(s.substr(i, l), hashed));
        }
    }

    return disctint;
}

int main(){
    string s, val; int k;
    cin >> s >> val >> k;

    set<pair<string, int>> strArr = uniqueGoodSubStrings(s, val, k);
    int result = strArr.size();
    // for(const auto str : strArr) cout << str.first << " " << str.second << endl;
    // for(const auto str : strArr){
    //     int count = 0;
    //     for(const auto c : str.second){
    //         if (val[c -'a'] == '0'){
    //             count ++;
    //         }
    //     }
    //     if (count > k) result--;
    // }
    // for(const auto str : strArr) cout << str.first << " " << str.second << endl;
    
    cout << strArr.size() << endl;

    return 0;
}