#include <bits/stdc++.h>

using namespace std;

int main(){
    string bedLine;

    while(getline(cin, bedLine)){
        if(bedLine.empty()) break;

        int N = bedLine.size();
        vector<int> right(N);
        vector<int> left(N);
        
        // build first array: saves numer of free beds before u
        right[0] = (bedLine[0] == '.') ? 0 : -1; 
        for(int i =1; i < N; i++){
            if(bedLine[i] == '.')
                right[i] = right[i-1] + 1; 
            else
                right[i] = -1;
        }

        // build second array: saves numer of free beds after u
        left[N-1] = (bedLine[N-1] == '.') ? 0 : -1; 
        for(int i = N - 2; i >= 0; i--){
            if(bedLine[i] == '.')
                left[i] = left[i + 1] + 1; 
            else
                left[i] = -1;
        }

        int maxBed = 0;
        right[0] = left[0]; if(right[0] > maxBed) maxBed = right[0];
        for(int i = 1; i < N-1; i++){
            if(left[i] < right[i]){
                right[i] = left[i];
            }
            if(right[i] > maxBed) maxBed = right[i];
        }
        if(right[N-1] > maxBed) maxBed = right[N-1];

        cout << maxBed << endl;
    }

    return 0;
}