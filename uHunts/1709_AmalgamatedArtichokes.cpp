#include <bits/stdc++.h>

using namespace std;

long double getPrice(int k, const int& p, const int& a, const int& b, const int& c, const int& d){
    return p * (sin(a * k + b) + cos(c * k + d) + 2);
}

int main(){
    string line;

    while(getline(cin, line)){
        // read the values
        int p, a, b, c, d, n;
        istringstream stream(line);
        stream >> p >> a >> b >> c >> d >> n;

        // calculate the prices
        vector<long double> prices;
        for(int k = 0; k < n; k++)
            prices.push_back(getPrice(k+1, p, a, b, c, d));
        

        // for(const auto val: prices){
        //     cout << val << ' ';
        // } cout << endl;

        // get the max decline
        long double maxDec = 0.00; long double grater = prices[0];
        for(int i = 0; i < prices.size(); i++){
            if(prices[i] > grater)
                grater = prices[i];
            if(grater - prices[i] > maxDec)
                maxDec = grater - prices[i];
        }
        cout << setprecision(15) << maxDec << endl;
    }
    return 0;
}
