// calculate the acumulated water on a city dado un arrego
// stack
#include<bits/stdc++.h>

using namespace std;

int getWater(const string& s){
    int water = 0;
    stack<int> downs;
    
    for(int i = 0; i < s.size(); i++){
        if(s[i] == (char)92){
            downs.push(i);
        }
        else if(s[i] == '/' && !downs.empty()){
            int j = downs.top(); downs.pop();
            water += i - j; // we get the water inside those chars
        }
    }
    
    return water;
}

int main(){
    int T; cin >> T;
    
    for(int t = 0; t < T; t++){
        string s; cin >> s;
        int water = getWater(s);
        cout << water << endl;
    }
    
    return 0;
}
