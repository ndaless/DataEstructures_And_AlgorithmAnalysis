// calcular la fecha después de 𝐾 dias
// a partir de una fecha dada en el calendario
// time

#include<bits/stdc++.h>

using namespace std;

map <string, int> month2int(){
    map <string, int> daysOn;
    vector<string> months = {"January", "February", "March", "April",
                             "May", "June", "July", "August", "September",
                             "October", "November", "December"};
    
    for(int i = 1; i <= 12; i++){
        daysOn[months[i-1]] = i;
    }
    
    return daysOn;
}

map <int, string> int2month(){
    map <int, string> daysOn;
    vector<string> months = {"January", "February", "March", "April",
                             "May", "June", "July", "August", "September",
                             "October", "November", "December"};
    
    for(int i = 1; i <= 12; i++){
        daysOn[i] = months[i-1];
    }
    
    return daysOn;
}

int main(){
    map<string, int> m2i = month2int();
    map<int, string> i2m = int2month();
    
    int T; cin >> T;
    for(int t = 0; t < T; t++){
        string date; cin >> date;
        int K; cin >> K;
        
        int year = stoi(date.substr(0,4));
        int month = m2i[date.substr(5, date.size()-8)];
        int day = stoi(date.substr(date.size()-2, 2));
        
        // cout << year <<' '<< month <<' '<< day << endl;
    
        tm fecha = {};
        fecha.tm_year = year - 1900;
        fecha.tm_mon = month - 1;
        fecha.tm_mday = day;
        
        time_t tiempo = mktime(&fecha);
        tiempo += K * 86400;
        
        tm* newFecha = localtime(&tiempo);
        
        if(newFecha->tm_mday < 10)
            cout << "Case " << t+1 << ": " << newFecha->tm_year + 1900 <<'-'<< i2m[newFecha->tm_mon + 1] <<"-0"<< newFecha->tm_mday << endl;
        else
            cout << "Case " << t+1 << ": " << newFecha->tm_year + 1900 <<'-'<< i2m[newFecha->tm_mon + 1] <<'-'<< newFecha->tm_mday << endl;
    }
    
    return 0;
}
