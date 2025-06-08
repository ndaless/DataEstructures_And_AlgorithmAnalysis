// calcular el mejor precio de un producto para satisfacer
// a los consumidores y productores
// complete search

#include<bits/stdc++.h>

using namespace std;

int main(){
    int T; cin >> T;

    for(int t = 0; t < T; t++){
        int P, C; cin >> P >> C;

        vector<int> producers(P);
        vector<int> costumers(C);
        vector<int> prices(P + C + 1);

        for(int p = 0; p < P; p++)
            {cin >> producers[p]; prices[p] = producers[p];}
        for(int c = 0; c < C; c++)
            {cin >> costumers[c]; prices[P + c] = costumers[c];}

        prices[P+C] = 0;

        sort(producers.begin(), producers.end());
        sort(costumers.begin(), costumers.end());
        sort(prices.begin(), prices.end());

        int pIdx = 0, cIdx = 0;
        int finalPrice = 0; int minAngry = INT_MAX;
        for(int i = 0; i <= C+P; i++){
            int pivPrice = prices[i];

            // we find the number of unsatisfied producer + satisfied costumers
            while(pIdx < P && producers[pIdx] <= pivPrice) pIdx++; // not angry
            while(cIdx < C && costumers[cIdx] < pivPrice) cIdx++; // angry

            int angry = cIdx + (P - pIdx);
            if(angry < minAngry){
                minAngry = angry;
                finalPrice = pivPrice;
            }
        }

        cout << finalPrice << ' ' << minAngry << endl;

    }

    return 0;
}