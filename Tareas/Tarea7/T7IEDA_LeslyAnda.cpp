# include <bits/stdc++.h>

using namespace std;

vector < int > zFunction(string s){
    vector< int > zf(s.size(), 0);

    int l = 0, r = 0;
    
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
    // declaramos strings necesarias (s y s invertida)
    string s = "Vamos Al Cerro", sRev = s;
    // string s = "HANNAH", sRev = s;
    reverse(sRev.begin(), sRev.end());
    
    // obtenemos la funcion z de la concatenacion de sRev con un caracter especial y s
    vector <int> zf = zFunction(sRev+'#'+s);

    // // para imprimir zf
    // for(const auto pfx : zf){
    //     cout << pfx << endl;
    // }

    int maxPfx = 0; // numero de elementos a agregar
    for(const auto pfx : zf){
        if(pfx == s.size()){
            cout << "The given string is already a palindrom." << endl;
            return 0;
        }

        // hallamos el mayor sufijo q también es un prefijo
        if(pfx > maxPfx) maxPfx = pfx;

    }

    // adjuntamos lo faltante a s para hacerla un palindromo
    cout << s + sRev.substr(maxPfx) << endl;
    return 0;
}