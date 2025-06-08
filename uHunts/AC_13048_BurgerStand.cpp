// intentar poner un puesto de hamburguesas 'B' en una posición que cumpla ciertos requerimientos
// string processing

#include<bits/stdc++.h>

using namespace std;

int main(){
    int T; cin >> T;
    for(int t = 0; t < T; t++){
        string road; cin >> road;
        vector<int> goodPos(road.size(), 1);

        int goodPosotions = 0;
        for(int pos = 0; pos < road.size(); pos++){
            if(road[pos] == 'B' || road[pos] == 'S' || road[pos] == 'D')
                goodPos[pos] = 0;
            if(pos < road.size()-1 && (road[pos+1] == 'B' || road[pos+1] == 'S'))
                goodPos[pos] = 0;
            if(pos < road.size()-2 && road[pos+2] == 'B')
                goodPos[pos] = 0;
            if(pos > 0 && road[pos-1] == 'S')
                goodPos[pos] = 0;
            if(goodPos[pos] == 1)
                goodPosotions ++;
        }
        cout << "Case " << t+1 << ": " << goodPosotions << endl;
    }

    return 0;
}