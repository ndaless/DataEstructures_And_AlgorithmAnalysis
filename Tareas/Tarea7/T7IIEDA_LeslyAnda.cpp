# include <bits/stdc++.h>

using namespace std;

vector < int > zFunction(string s){
    vector< int > zf(s.size(), 0);

    int l = 0, r = 0;
    zf[0] = s.size(); // contamos la primer entrada como toda la cadena

    for(int i = 1; i < s.size(); i++){
        if(i < r){
            // cout << "entrando a cambio" << endl;
            zf[i] = min(r-i, zf[i-l]);
        }

        // Encontramos un match y matcheamos todo lo q podamos uno por uno
        while(i + zf[i] < s.size() && s[zf[i]] == s[i + zf[i]]){ // match
            zf[i]++;
        }
    
        if(i + zf[i] > r){
            l = i;
            r = i + zf[i];
        }
    }

    return zf;

}

int main(){
    // hallamos los prefijos de s en s
    string s = "BLABLADEBLABLA";
    vector < int > zfun = zFunction(s); // hallamos funcion prefijos de s en s

    // // para imprimir zfun
    // for(const auto pfx : zfun){
    //     cout << pfx << endl;
    // }

    // procesamos zfun para hallar los prefijos q tambien son sufijos y los agregamos al map
    map <string, int> pfxCount;
    for(int i = 0; i < zfun.size(); i++){
        if(zfun[i] == (s.size() - i)){ // si el prefijo termina en el final
            if(zfun[i] > 0) pfxCount[s.substr(0, zfun[i])] = 0;
        }
        
    }

    // ahora, con contamos cuantas veces aparece
    for(const auto pfx : pfxCount){
        string newS = pfx.first + '#' + s; 
        vector< int > zPfx = zFunction(newS); // vector para contar apariciones
        for(const auto apSize : zPfx){
            if(apSize == pfx.first.size()) pfxCount[pfx.first]++;
        }
    }

    // imprimimos
    for(const auto& elemento : pfxCount){ // no estoy comprobando q sean tambien sufijos
        cout << elemento.first << ": " << elemento.second << endl;
    }

    return 0; 
}