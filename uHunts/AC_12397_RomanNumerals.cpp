// contar el total de ceriilos utilizados para construir un numero en romano
// map

#include <bits/stdc++.h>

using namespace std;

map<char, int> buildmap(){
    map<char, int> c2m;

    c2m['I'] = 1;
    c2m['V'] = 2;
    c2m['X'] = 2;
    c2m['L'] = 2;
    c2m['C'] = 2;
    c2m['D'] = 3;
    c2m['M'] = 4; 

    return c2m;
}

int main(){

    map<char, int> matches = buildmap();

    int num;
    while(cin >> num){
        string rom;
        // add millares
        int mill = num / 1000;
        for(int i = 0; i < mill; i++){
            rom.push_back('M');
        }
        if(num >= 1000)
            num %= 1000; 

        // add centenas
        int cent = num / 100;
        if(cent < 4){
            for(int i = 0; i < cent; i++)
                rom.push_back('C');
        } else if(cent == 4){
            rom += "CD";
        } else if(cent == 5){
            rom.push_back('D');
        } else if(cent < 9){
            rom.push_back('D');
            cent -= 5;
            for(int i = 0; i < cent; i++)
                rom.push_back('C');
        } else if(cent == 9){
            rom += "CM";
        }
        if(num >= 100)
            num %= 100; 

        // add decenas
        int dec = num / 10;
        if(dec < 4){
            for(int i = 0; i < dec; i++)
                rom.push_back('X');
        } else if(dec == 4){
            rom += "XL";
        } else if(dec == 5){
            rom.push_back('L');
        } else if(dec < 9){
            rom.push_back('L');
            dec -= 5;
            for(int i = 0; i < dec; i++)
                rom.push_back('X');
        } else if(dec == 9){
            rom += "XC";
        }
        if(num >= 10)
            num %= 10; 

        // add units
        int units = num; 
        if(units < 4){
            for(int i = 0; i < units; i++)
                rom.push_back('I');
        } else if(units == 4){
            rom += "IV";
        } else if(units == 5){
            rom.push_back('V');
        } else if(units < 9){
            rom.push_back('V');
            units -= 5;
            for(int i = 0; i < units; i++)
                rom.push_back('I');
        } else if(units == 9){
            rom += "IX";
        }

        // cout << rom << endl;

        int sum = 0;
        for(const auto r : rom){
            sum += matches[r];
        }

        cout << sum << endl;
    }

    return 0;
}