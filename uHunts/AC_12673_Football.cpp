// calcular el total de puntos que se pueden obtener comprando goles en los partidos ya jugados
// greedy

#include <bits/stdc++.h>

using namespace std;

int main(){
    int N, G;

    while(cin >> N){ cin >> G;
        int wins = 0, drawns = 0;
        priority_queue<int> loose; 
        int points = 0;

        int scored, received;
        for(int n = 0; n < N; n++){
            cin >> scored >> received;
            if(scored > received){
                wins++; points += 3;
            }
            else if(scored == received){
                drawns++; points++;
            }
            else    
                loose.push(scored - received); // to make min-heap
        }

        while(drawns){
            if(G < 1) break; // si ya no podemos pagar para ganar drawn
            G--; drawns--;
            points += 2;
        }

        int canBuy = 1; // flag to know if we can still buy 
        while(canBuy){
            if(loose.empty()) break;
            int toDrawn = -1*loose.top(); loose.pop();
            if(G < toDrawn) canBuy = 0;
            else{ // if we cam buy to drawn or win
                if(G >= toDrawn + 1){ // if we can win, we win
                    G -= (toDrawn + 1); points += 3;
                } else{ // if not, but we can drawn, we drawn
                    G -= toDrawn; points += 1;
                }
            }
        }
        cout << points << endl;
    }

    return 0;
}