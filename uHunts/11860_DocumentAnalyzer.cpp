#include <bits/stdc++.h>

using namespace std;

int main(){
    int T; cin >> T;

    for(int t = 0; t < T; t++){
        string line, finalLine;
        while(getline(cin, line)){
            if(line == "END")
                break;
            finalLine += (line + ' ');
        }

        // stringstream ss(finalLine);
        string token;
        vector<string> tokens;

        // while(ss >> token){
        //     tokens.push_back(token);
        // }

        for(const auto c : finalLine){
            if(c == ' '){ // (?
                tokens.push_back(token);
                token = "";
            }
            else if(islower(c)){
                token.push_back(c);
            } 
        }

        cout << "Los tokens de " << finalLine << "son:" << endl;
        for(const auto tok : tokens){
            cout << ' ' << tok << endl;
        } 

    }

    return 0;
}

    // stringstream ss(T);
    // string token;
    // vector<string> tokens;

    // while(ss >> token){
    //     tokens.push_back(token);
    // }

    // // sort(tokens.begin(), tokens.end());

    // cout << "Los tokens de " << T << "son:" << endl;
    // for(const auto tok : tokens){
    //     cout << ' ' << tok << endl;
    // }

    // // 5. Most frecuent substr
    // unordered_map<string, int> frecuencias;
    // int maxFrec = 0; string maxFrecStr;
    // for(const auto str : tokens){
    //     frecuencias[str] ++;
    //     if(frecuencias[str] > maxFrec){
    //         maxFrec = frecuencias[str];
    //         maxFrecStr = str;
    //     }
    // }

    // cout << "Token más frecuente: " << maxFrecStr << endl;