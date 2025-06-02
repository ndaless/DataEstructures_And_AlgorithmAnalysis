#include<bits/stdc++.h>

using namespace std;

int main(){
    int T; cin >> T;
    
    for(int t = 0; t < T; t++){
        int F; cin >> F; // numero de amigos
        map<int, int> globalfrec;
        vector<map<int, int>> fsf(F); // frecuency of each stamp on each friend

        for(int f = 0; f < F; f++){ // for each friend get its stamps
            int K; cin >> K; // numero de estampas de f
            for(int i = 0; i < K; i++){
                int k; cin >> k;
                globalfrec[k]++;
                fsf[f][k]++;
            }
        }

        // for(int f = 0; f < F; f++){
        //     for(const auto stamp : fsf[f]){
        //         cout << stamp.first << '-' << stamp.second << ' ';
        //     } cout << endl;
        // }

        for(int f = 0; f < F; f++){ // keep only the unik elemets
            auto it = fsf[f].begin();
            while(it != fsf[f].end()){
                if(globalfrec[it->first] != it->second){  
                    it = fsf[f].erase(it);  // erase devuelve el siguiente iterador válido
                    // unik--;
                } else {
                    ++it;
                }
            }
        }

        double unik = 0.0;
        for(int f = 0; f < F; f++){
            unik += fsf[f].size();
        }

        cout << "Case " << t+1 << ':';
        for(int f = 0; f < F; f++){
            double percent = ((double)fsf[f].size() * 100.00)/(unik);
            cout << ' ' << fixed << setprecision(6) << percent << '%';
        } cout << endl;
    }

    return 0;
}