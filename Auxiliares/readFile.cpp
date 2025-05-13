#include <bits/stdc++.h>

using namespace std;

int main(){

    //1. Leer strings de archivo, concatenar y detener al leer una subcadena
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

    cout << "La string leída y procesada es: " << endl;
    cout << ' ' <<  finalLine << endl;

    // 2. Encontrar posición de substr en str
    string T = finalLine;
    string P = "love";

    set<size_t> positions; 
    size_t pos = T.find(P);

    while(pos != std::string::npos){
        positions.insert(pos);
        pos = T.find(P, pos + P.size()); // find P desde la posición
    }

    if(positions.size() == 0)
        cout << '\''<< P << '\'' << " no fue encontrada en " << '\'' << T << '\'' << -1 << endl;

    else{
        cout << '\''<< P << '\'' << " aparece en " << '\'' << T << '\'' << "en las posiciones: ";
        for(const auto pos : positions)
            cout << pos << ' ';
        cout << endl;
    }

    // 3. Contar vowels, consonats y digits
    int vowels = 0, consonants = 0, digits = 0;
    for(auto& c : T){
        c = tolower(c); //?
        if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'){
            vowels++;
        }
        else{
            if(isalpha(c))
                consonants++;
            if(isdigit(c))
                digits++;
        }
    }

    cout << "Consonants: " << consonants << endl;
    cout << "Vowels: " << vowels << endl;
    cout << "Digits: " << digits << endl;

    //4. Tokenize
    stringstream ss(T);
    string token;
    vector<string> tokens;

    while(ss >> token){
        tokens.push_back(token);
    }

    sort(tokens.begin(), tokens.end());

    cout << "Los tokens de " << T << "son:" << endl;
    for(const auto tok : tokens){
        cout << ' ' << tok << endl;
    }

    // 5. Most frecuent substr
    unordered_map<string, int> frecuencias;
    int maxFrec = 0; string maxFrecStr;
    for(const auto str : tokens){
        frecuencias[str] ++;
        if(frecuencias[str] > maxFrec){
            maxFrec = frecuencias[str];
            maxFrecStr = str;
        }
    }

    cout << "Token más frecuente: " << maxFrecStr << endl;

    // 6. Get a line without lenght
    getline(txt, line);
    cout << "Last line:" << endl << ' ' << line << endl;
    txt.close();
    return 0;
}