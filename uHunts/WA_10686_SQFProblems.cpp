// clasificar problemas segun las palabras que aparecen en ellos
// map

#include <bits/stdc++.h>

using namespace std;

int main(){
    int T; cin >> T;

    for(int t = 0; t < T; t++){
        int C; cin >> C;
        map<string, string> kw2ct; // caterogy of each keyword
        map<string, int> minKW; // number of keywords to be classify
        map<string, set<string>> ct2set; // apariciones de las palabras en el texto

        for(int c = 0; c < C; c++){
            string categrory, keyword; int W, P; // total keywords and min to classify
            cin >> categrory >> W >> P;
            minKW[categrory] = P;
            for(int w = 0; w < W; w++){
                cin >> keyword;
                kw2ct[keyword] = categrory;
            }
        }

        // cout << endl << "kw2ct:"<< endl;
        // for(const auto par : kw2ct){
        //     cout << par.first << '-' << par.second << endl;
        // }

        // cout << "minKW:"<< endl;
        // for(const auto par : minKW){
        //     cout << par.first << '-' << par.second << endl;
        // }

        string line; cin.ignore();
        while(getline(cin,line)){
            if(line.empty()){
                break;
            }
            istringstream stream(line);
            string word;
            while(stream >> word){
                if(kw2ct.find(word) != kw2ct.end()){
                    string ctgry = kw2ct[word];
                    ct2set[ctgry].insert(word);
                }
            }
        }

        // cout << "ct2set:"<< endl;
        // for(const auto par : ct2set){
        //     cout << par.first << '-' << par.second.size() << endl;
        // }

        if(ct2set.empty()){
            cout << "SQF Problem." << endl;
        } else{
            for(const auto par : minKW){
                if(ct2set.find(par.first) != ct2set.end()){
                    if(ct2set[par.first].size() >= par.second)
                        cout << par.first; 
                    ct2set.erase(par.first);
                }
                if(ct2set.size() > 0){
                    cout << ',';
                }
            }cout << endl;
        }

    }

    return 0;
}