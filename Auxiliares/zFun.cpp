#include <bits/stdc++.h>

using namespace std;

vector<int> getZfun(const string& s){
    vector <int> z(s.size());

    int l = 0, r = 0;
    for(int i = 1; i < s.size(); i++){
        if(i < r){
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < s.size() && s[z[i]] == s[i + z[i]]){
            z[i]++;
        }
        if(i + z[i] > r){
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

// void solve(s){
//     vector<int> zfun = getZfun(s);
//     // for(const auto val : zfun){
//     //     cout << val << ' ';
//     // } cout << endl;

// }

int main(){
    string s = "aabaab";
    vetor<int> getZfun(s);

    return 0;
}