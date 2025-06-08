// identificar el caracter segun una 'imagen' hecha de caracteres de el
// string processing

# include <bits/stdc++.h>

using namespace std;

int main(){
    int n; cin >> n;
    char first, second, third;

    for(int i = 0; i < 4; i++){ // bajamos hasta columna 3
        for(int j = 0; j < 4*n; j++){ // numero de numero leido
            if(i == 3){
                if(j % 4 == 0){
                    cin >> first;
                    if(first == '*') {cout << 2; continue;}
                }
                else if(j % 4 == 1){
                    cin >> second;
                    if(second == '*') {cout << 1; continue;}
                }
                else if(j % 4 == 2){
                    cin >> third;
                    if(third == '*') {cout << 3; continue;}
                }

                else{
                    cin >> first;
                }
            }
            else{
                cin >> first;
            }
        }
    }
    cout << endl;
    return 0;
}