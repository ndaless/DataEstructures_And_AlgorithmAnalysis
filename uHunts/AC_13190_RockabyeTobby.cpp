#include <bits/stdc++.h>

using namespace std;

int main(){
    int T; cin >> T;

    for(int t = 0; t < T; t++){
        int N, K; cin >> N >> K;

        priority_queue<pair<int, int>> pq; // max heap <time, priority>
        map<int, string> prior2name; // mapeamos la prioridad al medicamento
        // vector<tuple<int, int, string>> meds; // <time, name>
        map<int, int> prior2time;

        string name; int time;
        for(int i = 0; i < N; i++){
            cin >> name >> time;
            // meds.push_back(make_tuple(time, N-i, name));
            pq.push(make_pair(-1*time, N-i));
            prior2name[N-i] = name;
            prior2time[N-i] = time;
        }

        // for(int i = 0; i < N; i++){
        //     pair<int, int> next_med = pq.top();
        //     cout << -1*next_med.first << ' ' << prior2name[next_med.second] << endl;
        //     pq.pop();
        // }

        // sort(meds.begin(), meds.end());
        // for(int i = 0; i < K; i+){
        //     pq.insert(make_pair(get<1>(meds[i]), get<2>(meds[i])));
        // }

        int k = 0; // int i = 0; int count = 1;
        while(k < K){
            if(pq.empty())
                cout << "error" << endl;
            // extraemos next_med
            pair<int, int> next_med = pq.top();
            // imprimimos
            cout << -1* next_med.first << ' ' << prior2name[next_med.second] << endl;
            // eliminamos y agregamos siguiente toma
            pq.pop(); pq.push(make_pair(next_med.first - prior2time[next_med.second], next_med.second));

            k++;
        }
    }

    return 0;
}