// intentar maximizar los puntos de un jugador sabiendo el resultado del juego 'dont be greedy'
// greedy

#include <bits/stdc++.h>

using namespace std;

int main(){
    int N, M; // cin >> N >> M;
    
    while(cin >> N){ cin >> M; // por cada caso
        int MG = 0; // total de puntos a obtener en el caso
        for(int m = 0; m < M; m++){ // hacemos M rounds
            int B; cin >> B;
            int pc, p1; // jugadores en general y jugador 1
            int sum = 0; // suma de cada ronda
            for(int n = 0; n < N; n++){ // leemos a cada jugador
                cin >> pc;
                if(n == 0) p1 = pc;
                sum += pc; // y sacamos la suma total
            }
            if(sum < B && p1 < 10000){ // si se quedaron abajo y p1 pudo haber puesto algo más grande
                sum = B - sum + p1; // calculamos restante sin considerar a lx jugadorx 1 
                if(sum >= 10000){
                    MG += 10000 - p1;
                }
                else if(sum >= 1000){
                    MG += 1000 - p1;
                }
                else if(sum >= 100){
                    MG += 100 - p1;
                }
                else if(sum >= 10){
                    MG += 10 - p1;
                }
                // else if(sum > 1){
                //     MG += 1 - p1;
                // }
            }
            else if(sum > B && 1 < p1){
                sum = sum - p1;
                sum = B - sum; // obtenemos cuanto les falta a los demás 
                if(sum == 0) // si sin p1 quedan bien, p1 no puede hacer nada
                    continue;
                if(sum >= 10000){
                    MG += 10000;
                }
                else if(sum >= 1000){
                    MG += 1000;
                }
                else if(sum >= 100){
                    MG += 100;
                }
                else if(sum >= 10){
                    MG += 10;
                }
                else if(sum >= 1){
                    MG += 1;
                }
            }
        }
        cout << MG << endl;
        // cin >> N;
    }
    
    
    return 0;
}
