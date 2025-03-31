# include <bits/stdc++.h>

using namespace std;

vector <int> kmpPreprocess(const string &p){
    vector <int> resets(p.size());

    int i = 0, j = -1;
    //Initial value: if mismatch at zero, nothing to do
    resets[0] = -1;
    // Scan the pattern
    while(i < p.size()){
        // Same structure as kmpMatch: if mismatch i (current end)/j(current prefix), we use the resets
        while(j >= 0 && p[i]!=p[j]) j = resets[j];
        // If there is a match or no matched structure at all (j=-1), we advance
        i++; j++;
        resets[i] = j;
    }
    return resets;
}

vector <int> kmpMatch(const string &s, const string &pattern){
    vector <int> resets(pattern.size());
    resets = kmpPreprocess(pattern);
    
    vector <int> occ;

    int i = 0, j = 0; // nc = 0;
    //scan the string s
    while (i<s.size()) {
        while(j>=0 && s[i] != pattern[j]) j = resets[j];
        i++; j++;

        if(j == pattern.size()){
            // nc++;
            // cout << "encontrado en " << (i-1)-(j-1) << endl; 
            occ.push_back((i-1)-(j-1));
            j = resets[j];
        }
    }
    return occ;
}

int kmpFind(const string &s, const string &pattern){
    // regresa primer ocurrencia de p en s
    vector <int> resets(pattern.size());
    // vector <int> occ;

    int i = 0, j = 0, nc = 0;
    //scan the string s
    while (i<s.size()) {
        while(j>=0 && s[i] != pattern[j]) j = resets[j];

        if(j == pattern.size()){
            return i-j;
            // nc++;
            // occ.push_back((i-1)-(j-1));
            // j = resets[j];
        }

        i++; j++;
    }
    return nc;
}


int findMat(const vector<string> &WH, const vector<string> &wh){
    vector <int> occ; int nc = 0;
    string p = wh[0]; // debo inicializarlas de otra forma
    /// cout << p << endl;
    for(int i = 0; i <= WH.size()-wh.size(); i++){ // recorremos las filas de WH
        string s = WH[i]; // cout << s << endl;

        occ = kmpMatch(s, p); // idx at which there's an occurence
        
        for(const auto oc : occ); // cout << "occ: " << oc << " " << endl;
        
        int flag = 0; // will tell us if we found a mismatch
        for(const auto oc : occ){
            // cout << "oc: " << oc << endl;
            if(oc > WH[0].size()-wh[0].size()) break;   // si la ocurrencia se da en una columna tq wh no cabe,
            for(int r = 0; r < wh.size(); r++){         // (c+oc se sale de WH) ignoramos las siguiente ocurrencias
                for(int c = 0; c < wh.size(); c++){
                    if(WH[r + i][c + occ[oc]] != wh[r][c]){
                        // cout << "mismatch found" << endl;
                        flag = 1; // we found a mismatch
                        break; // we dont see the rest of the colum
                    }
                }
                if (flag == 1) break; // if mismatch, we dont see the following rows
            }
            if (flag == 1){ // if mismatch
                flag = 0; // we reset the flag to compare the next occurence
                continue;
            }
            nc++;
        }
    }
    return nc;
}

int main(){

    vector<string> WH(3);
    vector<string> wh(2);
    
    WH[0] = "AAA";
    WH[1] = "AAA";
    WH[2] = "CBC";
    
    wh[0] = "AA";
    wh[1] = "AA";
    
    cout << "wh aparece " << findMat(WH, wh) << " veces en WH."<< endl;

    return 0;
}