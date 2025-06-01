# include <bits/stdc++.h>

using namespace std;

int main(){
    int n; cin >> n;
    
    while(n != 0){
        priority_queue<string> names; // max_pq

        string name;
        for(int i = 0; i < n; i++){
            cin >> name;
            names.push(name);
        }
        
        // for(const auto n : names){
        //     cout << n << ' ';
        // } cout << endl;
        
        string next, last;
        
        // if(n == 2){
        //     next = names.top(); names.pop();
        //     last = names.top();
        // }
        // else{
        for(int i = 0; i < n/2-1; i++){
            names.pop();
        }
        next = names.top(); names.pop();
        last = names.top();
        // }
        
        // cout << last << ' ' << next << ' ' << next.size() << endl;
        
        if(next.size() == 1 && last[0] == (char)(next[0]-1)){
            cout << last << endl;
        }
        else if(last[0] != next[0])
            cout << (char)(last[0] + 1) << endl;
        else if(last == next.substr(0,last.size())){
            cout << last << endl;
        }
        else{
            int k = 0;
            while(last[k] == next[k]){ // find the different
                k++;
            }
            cout << last.substr(0, k) << (char)(last[k] +1) << endl;
        }
        cin >> n;
    }
    
    return 0;
}
