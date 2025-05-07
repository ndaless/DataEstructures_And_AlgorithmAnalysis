#include <bits/stdc++.h>

using namespace std;

int main(){

    //1. 
    ifstream txt("fichero.txt");
    string line, finalLine;

    if(txt.is_open()){
        while(getline(txt, line)){
            if(line.substr(0, 7) == ".......")
                break;
            finalLine += (line + ' ');
        }
    } else{
        cout << "NO se pudo abrir el archivo :(" << endl;
    }

    cout << finalLine << endl;

    // 2.
    string T = finalLine;
    string P = "book";

    set<size_t> positions; 
    size_t pos = T.find(P);

    while(pos != std::string::npos){
        pos = T.find(P, pos + P.size());
        positions.insert(pos);
    }

    if(positions.size() == 0)
        cout << -1 << endl;

    // cout << P << " aparece en " << T << "en las posiciones: ";
    for(const auto pos : positions)
        cout << pos;
    cout << endl;

    return 0;
}