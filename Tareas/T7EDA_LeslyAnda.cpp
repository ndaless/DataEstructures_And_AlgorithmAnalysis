# include <bits/stdc++.h>

// # include <iostream>
// # include <vector>
// # include <string>

using namespace std;

vector < pair<int, string> > zFunction(string s, map <string, int> &count){
    vector< pair<int, string> > zf(s.size(), {0, ""}); // guardamos el tamano del prefijo y el prefijo
    // que hacen l y r?
    int l = 0, r = 0;

    zf[0].first = s.size();
    zf[0].second = s;
    count[zf[0].second]++;

    int flag = 0;

    for(int i = 1; i < s.size(); i++){
        // este if se fija si ya habiamos encontrado esa subcadena?
        // si si, podemos ahorrarnos el contar?
        if(i < r){ // aqui esta el problema 
            cout << "entrando a cambio" << endl;
            zf[i].first = min(r-i, zf[i-l].first); // qué hace el r-i y cómo influye en la substg?
            zf[i].second = zf[i-l].second;
            if(zf[i].first > 0){ // si si agregamos una cadena != ""
                count[zf[i].second]++;
            }
        }

        // Encontramos un match y matcheamos todo lo q podamos uno por uno
        // No entra a este while pq ya se lleno corectamente con lo antes procesado
        while(i + zf[i].first < s.size() && s[zf[i].first] == s[i + zf[i].first]){ // match
            zf[i].second.push_back(s[zf[i].first]);
            zf[i].first++;
            flag = 1; // se ecnontró un prefijo
        }
        if(flag == 1){
            count[zf[i].second]++;
            flag = 0;
        }
        // Que hace este if?
        if(i + zf[i].first > r){
            l = i;
            r = i + zf[i].first;
        }
    }

    return zf;

}

// POR QUE ESTA AGREGANDO LA CADENA VACIA

int main(){
    map <string, int> sfxCount;

    string s = "BLABLADEBLABLA";
    vector <pair<int, string>> zfun = zFunction(s, sfxCount); // hallamos funcion prefijos de s en s

    for(const auto pfx : zfun){
        cout << pfx.first << " " << pfx.second << endl;
    }

    // procesamos zfun para hallar los prefijos q tambien son sufijos
    // for(int i = 0; i < zfun.size(); i++){
    //     // if(zfun[i].first == (s.size() - i)){ // si la longitud del pfx coincide con la del sufijo
    //     //     // if(sfxCount.find(zfun[i].second) == sfxCount.end()) sfxCount.insert({zfun[i].second, 0});
    //     //     sfxCount[zfun[i].second] ++;
    //     // }
    //     if (zfun[i].second == s.substr(i)) {
    //         sfxCount[zfun[i].second]++;
    //     }
    // }

    // cout << sfxCount.size() << endl;

    for(const auto& elemento : sfxCount){ // no estoy comprobando q sean tambien sufijos
        cout << "Prefix: " << elemento.first << ", Apariciones: " << elemento.second << endl;
    }

    // for(const auto sfx : sfxCount){
    //     cout << sfx.first << " " << sfx.second << endl;
    // }

    return 0; 
}
