#include<bits/stdc++.h>

using namespace std;

int main(){
    stack<string> dreams;
    int n; cin >> n;
    
    string qry;
    for(int i = 0; i < n; i++){
        cin >> qry;
        
        if(qry == "Test"){
            if(!dreams.empty()){
                cout << dreams.top() << endl;
            } else{
                cout << "Not in a dream" << endl;
            }
        }
        else if(qry == "Kick"){
            if(!dreams.empty()){
                dreams.pop();
            }
        }
        else{
            cin >> qry;
            dreams.push(qry);
        }
    }
    
    return 0;
}
