#include <bits/stdc++.h>

using namespace std;

int main(){
    int T; cin >> T;

    for(int t = 0; t < T; t++){
        string line, finalLine;
        while(getline(cin, line) && line != "END"){
            finalLine += (line + ' ');
        }

        // stringstream ss(finalLine);
        string token;
        vector<string> tokens;
        unordered_map<string, int> words;

        // while(ss >> token){
        //     tokens.push_back(token);
        // }

        for(const auto c : finalLine){
            if(c == ' '){ // (?
                if(!token.empty()) {
                    tokens.push_back(token);
                    words[token]++;
                    token = "";
                }
            }

            else if(islower(c)){
                token.push_back(c);
            } 
        }

        // cout << "Los tokens de " << finalLine << "son:" << endl;
        // for(const auto tok : tokens){
        //     cout << ' ' << tok << endl;
        // } 

        // for(const auto par : words){
        //     cout << par.first << '-' << par.second << endl;
        // }
        }

        // we get the interval    
        int left = 0, right = 0;
        int uniqueElems = 0;
        int totalW = words.size();
        int intLen = INT_MAX;
        pair<int, int> ans;

        while(right < tokens.size()){
            words[tokens[right]]++;
            if (words[tokens[right]] == 1) uniqueElems++;

            while (uniqueElems >= totalW) {
                if(right - left < intLen){
                    intLen = right - left; // reducimos ventana
                    ans = make_pair(left, right);
                }
                words[tokens[left]]--;
                if(words[tokens[left]] == 0) uniqueElems--;
                left++;
            }
            right++;
        }

        cout << "Document " << t + 1 << ": " << ans.first << ' ' << ans.second << endl;
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