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

int getPalindrom(string s){
    // invertimos s
    string sRev = s; reverse(sRev.begin(), sRev.end()); 
    
    // obtenemos la funcion z de la concatenacion de sRev con un caracter especial y s
    vector <int> zf = zFunction(sRev+'#'+s);

    int maxPfx = 0; // len mayor palindromo que termina al final de s
    for(const auto pfx : zf){
        // if(pfx == s.size()){
        //     cout << "The given string is already a palindrom." << endl;
        //     return 0;
        // }

        // hallamos el mayor sufijo q también es un prefijo
        if(pfx > maxPfx) maxPfx = pfx;

    }

    // adjuntamos lo faltante a s para hacerla un palindromo
    // cout << s + sRev.substr(maxPfx) << endl;
    return maxPfx;
}

// bool isPalindrom(string s){
//     int lenPal = getPalindrom(s);

//     if(lenPal == s.size()){
//         return true;
//     }

//     return false;

// }

void solve(string s){
    int lenPal = getPalindrom(s);

    if(lenPal == s.size()){
        cout << "palindrome" << endl;
        return;
    }

    // NO funciona pq puede que el palindomo mas grande esté al final
    // y sí encontraremos un prefijo-sufijo grande

    // if(lenPal == 1){
    //     cout << "simple" << endl;
    // }
    // cout << "alindrome" << endl;

    // veremos si la cadena restante es un palindromo
    string secStr = s.substr(lenPal);
    int lenSecPal = getPalindrom(secStr); 
    if(lenSecPal == secStr){
        cout << "alindrome" << endl;
        return;
    }
    
    cout << "simple" << endl;

}

int main(){
    int T; cin >> T;
    string s;

    for (int t = 0; t < T; t++){
        cin >> s;
        solve(s);
    }

    return 0;
}
