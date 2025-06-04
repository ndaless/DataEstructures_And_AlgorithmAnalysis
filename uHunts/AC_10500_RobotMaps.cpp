#include <bits/stdc++.h>

using namespace std;

int main(){
    int N, M; cin >> N >> M;
     while(N != 0 || M != 0){
        int x_ini, y_ini; cin >> x_ini >> y_ini;

        // constuct the original map
        vector<vector<char>> original(N, vector<char> (M)); // filas y columnas
        for(int n = 0; n < N; n++){ // filas
            for(int m = 0; m < M; m++){ // columnas
                cin >> original[n][m];
            }
        }

        // for(int n = 0; n < N; n++){ // filas
        //     for(int m = 0; m < M; m++){ // columnas
        //         cout << original[n][m];
        //     } cout << endl;
        // } cout << endl;

        // llenamos el mapa dle robot
        vector<vector<char>> robotMap(N, vector<char> (M, '?'));
        vector<vector<int>> visited(N, vector<int> (M, 0));
        int x = x_ini-1, y = y_ini-1;
        robotMap[x][y] = '0'; visited[x][y] = 1;

        int x_next = x, y_next = y;
        int flag = 1; // empty space flag
        int moves = 0;
        while(flag){
            visited[x][y] = 1;
            flag = 0; // cout << flag;
            if(0 < y && visited[x][y-1] != 1){ // si podemos acceder a la izquierda
                robotMap[x][y-1] = original[x][y-1];
                if(robotMap[x][y-1] == '0'){
                    x_next = x; y_next = y-1;
                    flag = 1;
                    // visited[x][y-1] = 1;
                }
            } if(x < N-1 && visited[x+1][y] != 1){ // si podemos acceder arriba
                robotMap[x+1][y] = original[x+1][y];
                if(robotMap[x+1][y] == '0'){
                    x_next = x+1; y_next = y;
                    flag = 1;
                    // visited[x+1][y] = 1;
                }
            } if(y < M-1 && visited[x][y+1] != 1){ // si podemos acceder a la derecha
                robotMap[x][y+1] = original[x][y+1];
                if(robotMap[x][y+1] == '0'){
                    x_next = x; y_next = y+1;
                    flag = 1;
                    // visited[x][y+1] = 1;
                }
            } if(0 < x && visited[x-1][y] != 1){ // si podemos acceder abajo
                robotMap[x-1][y] = original[x-1][y];
                if(robotMap[x-1][y] == '0'){
                    x_next = x-1; y_next = y;
                    flag = 1;
                    // visited[x-1][y] = 1;
                }
            }
            x = x_next; y = y_next;
            moves ++;
        }

        // // Imprimimos nueva matriz
        // for(int n = 0; n < N; n++){ // filas
        //     for(int m = 0; m < M; m++){ // columnas
        //         cout << robotMap[n][m];
        //     } cout << endl;
        // } cout << endl;

        // Imprimir resultado con formato:
        // empty line
        cout << endl;
        // robot map
        for(int n = 0; n < N; n++){ // filas
            // linea
            for(int m = 0; m < M; m++){ // columnas
                cout << "|---";
            } cout << '|' << endl;
            // datos
            for(int m = 0; m < M; m++){ // columnas
                cout << "| " << robotMap[n][m] << ' ';
            } cout << '|' << endl;
        } 
        // linea final
        for(int m = 0; m < M; m++){
            cout << "|---";
        } cout << '|' << endl << endl;
        // Number of movements
        cout << "NUMBER OF MOVEMENTS: " << moves-1 << endl;

        cin >> N >> M;
    }

    return 0;
}