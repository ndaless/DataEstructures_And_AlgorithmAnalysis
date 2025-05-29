#include <bits/stdc++.h>

using namespace std;
int main(){
    ios::sync_with_stdio(false); // acelera lectura
    cin.tie(nullptr);            // evita flush automático

    int T; cin >> T; cin.ignore();

    for(int t = 0; t < T; t++){
        string line; // finalLine;
        string token = "";
        vector<string> tokens;
        unordered_map<string, int> words; // store the unique words and its frecuency along the whole string


        // constuct the final line
        while(getline(cin, line) && line != "END"){
            char c;
            for(int i = 0; i < line.size(); i++){
                c = line[i];
                if(!isalpha(c)){ // (?
                    if(!token.empty()) {
                        tokens.push_back(token);
                        words[token] = 0;
                        token = "";
                    }
                }
                
                else if(islower(c)){
                    token.push_back(c);
                }

                if(token.size() > 0 && i == line.size()-1){ // to manage the las word on line
                    tokens.push_back(token);
                    words[token] = 0;
                    token = "";
                }
            }
        }

        // cout << "tokens are:" << endl;
        // for(const auto tok : tokens){
        //     cout << tok << ' ';
        // } cout << endl;
        
        // cout << "the unik word are:" << endl;
        // for(const auto par : words){
        //     cout << par.first << '-' << par.second << endl;
        // }

        // we get the interval    
        int left = 0, right = 0;
        int uniqueElems = 0;
        int totalW = words.size();
        int intLen = INT_MAX;
        pair<int, int> ans;

        while(right < (int)tokens.size()){ // expand the window
            words[tokens[right]]++; // ad finded words
            if (words[tokens[right]] == 1) uniqueElems++;

            // cout << "after finding the window, unik words are:" << endl;
            // for(const auto par : words){
            //     cout << par.first << '-' << par.second << endl;
            // }

            while (uniqueElems >= totalW) { // si tenemos más de los que necesitamos
                // cout << "trying to reduce window" << endl;
                if(right - left < intLen){// reducimos ventana por izquierda
                    intLen = right - left; // reducimos ventana
                    ans = make_pair(left + 1, right + 1);
                }
                words[tokens[left]]--; // quitamos el que quitamos
                if(words[tokens[left]] == 0) uniqueElems--; // si desaparecimo uno lo quitamos 
                left++;
            }

            right++;
        }

        cout << "Document " << t+1 << ": " << ans.first << ' ' << ans.second << endl;
    }
}