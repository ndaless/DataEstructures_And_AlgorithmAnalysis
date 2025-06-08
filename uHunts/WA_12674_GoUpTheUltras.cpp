// encontrar los picos de un arreglo y evaluar si cumplen la propiedad de ser 'ultras'
// sparce table

#include <bits/stdc++.h>

using namespace std;

struct SparceTable {
    int MAXN;
    vector <int> vec;
    vector <vector<int>> st;
    vector <int> lg;

    SparceTable(const vector<int>& points){
        MAXN = points.size();
        vec = points;

        lg.resize(MAXN+1);
        buildlog();

        st.assign(lg[MAXN] + 1, vector<int>(MAXN));
        buildST();

        // printST();
    }

    void buildlog(){
        lg[1] = 0; // empieza en 1 pq log(0) bai
        for(int i = 2; i <= MAXN; i++){
            lg[i] = lg[i/2] + 1;
        }
    }

    void buildST(){
        for(int j = 0; j <= MAXN; j++){
            st[0][j] = vec[j];
        }

        for(int i = 1; i <= lg[MAXN]; i++){
            for(int j = 0; j + (1 << i) <= MAXN; j++){
                st[i][j] = min(st[i-1][j], st[i-1][j+(1 << (i-1))]);
            }
        }
    }

    int getMin(int L, int R){
        int i = lg[R-L+1];
        int minimum = min(st[i][L], st[i][R - (1 << i) + 1]);

        return minimum;
    }

    void printST(){
        for(int i = 0; i <= lg[MAXN]; i++){
            for(int j = 0; j + (1 << i) <= MAXN; j++){
                cout << st[i][j] << ' ';
            } cout << endl;
        }
    }
};

int main(){
    int N;
    while(cin >> N){
        // get the points
        vector<int> points(N);
        for(int i = 0; i < N; i++)
            cin >> points[i];
        
        SparceTable st(points);

        // identificamos los picos
        vector<pair<int, int>> peaks; // altura, idx end og array ordenamos
        if(points[1] < points[0])
            peaks.push_back(make_pair(points[0], 0));
        for(int i = 1; i < N-1; i++){
            if(points[i-1] < points[i] && points[i] > points[i+1])
                peaks.push_back(make_pair(points[i], i));
        }
        if(points[N-2] < points[N-1])
            peaks.push_back(make_pair(points[N-1], N-1));

        sort(peaks.begin(), peaks.end());

        // cout << "PEAKS:" << endl;
        // for(int pk = 0; pk < peaks.size(); pk++)
        //     cout << peaks[pk].first << ' ' << peaks[pk].second << ' ';
        // cout << endl;

        // cout << "RESULTS:" << endl;
        // // ask the queries
        // if(peaks.size() < 2){ // si solo hay un punto
        //     if(peaks[0].first >= 150000)
        //         cout << peaks[0].second +1 << endl;
        //         continue;
        // }

        // inicio
        int down = 0; // min point between the peaks
        int h = 0;
        
        vector<int> result;
        int pk = 0;
        while(peaks[pk].first < peaks[peaks.size()-1].first){
            (peaks[pk].second < peaks[peaks.size()-1].second) ? down = st.getMin(peaks[pk].second, peaks[peaks.size()-1].second) : down = st.getMin(peaks[peaks.size()-1].second, peaks[pk].second); // hacia la derecha
            h = peaks[pk].first - down;
            if(h >= 150000)
                result.push_back(peaks[pk].second +1);
            pk++;
        }

        // final
        while(pk < peaks.size()){
            if(peaks[peaks.size()-1].first >= 150000)
                result.push_back(peaks[pk].second +1);
            pk++;
        }

        sort(result.begin(), result.end());

        for(int i = 0; i < result.size(); i++){
            if(i == result.size() -1)
                cout << result[i] << endl;
            else
                cout << result[i] << ' ';
        }
        
    }

    return 0;
}