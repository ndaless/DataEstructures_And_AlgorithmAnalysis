#include <bits/stdc++.h>

using namespace std;

vector<int> getPrefix(const string& s){
    vector<int> pi(s.size());

    pi[0] = 0;
    for(int i = 1; i < s.size(); i++){
        int j = pi[i - 1];
   
        while(j > 0){
            if(s[j] == s[i]){
                pi[i] = j + 1;
                break;
            }
            j = pi[j - 1];
        }
        
        if(j == 0){
            (s[j] == s[i]) ? pi[i] = 1 :  pi[i] = 0;
        }
    }

    return pi;
}

int main(){
    string s1 = "abcabcd";
    vector<int> p1 = getPrefix(s1);

    for(const auto val : p1){
        cout << val << ' ';
    } cout << endl;

    string s2 = "aabaaab";
    vector<int> p2 = getPrefix(s2);

    for(const auto val : p2){
        cout << val << ' ';
    } cout << endl;

    return 0;
}