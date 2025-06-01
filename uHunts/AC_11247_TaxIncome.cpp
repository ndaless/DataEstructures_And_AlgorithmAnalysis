#include<bits/stdc++.h>

using namespace std;

long long int getBestIncome(long long m, long long x){
    long long int v;
    
    (x != 100) ? v = (long long int)((m-1) * 100) / (100 - x) : v = 0;
    if(v * (100-x) / 100 == m - 1) v--;
     
    return v;   
}

int main(){
    long long m, x; cin >> m >> x;
    
    while(m != 0 || x != 0){
        long long int v = getBestIncome(m, x);
        
        if(v < m) cout << "Not found" << endl;
        else cout << v << endl;
        
        cin >> m >> x;
    }
    
    return 0;
}
