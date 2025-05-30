# include<bits/stdc++.h>

using namespace std;

void fill_card2point(unordered_map<string, double>& c2p){
    // kings
    c2p["king of spades"] = 4.5; 
    c2p["king of hearts"] = 4.5; 
    c2p["king of diamonds"] = 4.5; 
    c2p["king of clubs"] = 4.5; 
    // oudlers
    c2p["one of trumps"] = 4.5;
    c2p["twenty-one of trumps"] = 4.5;
    c2p["fool"] = 4.5;
    // queens
    c2p["queen of spades"] = 3.5;
    c2p["queen of hearts"] = 3.5; 
    c2p["queen of diamonds"] = 3.5; 
    c2p["queen of clubs"] = 3.5; 
    // knights
    c2p["knight of spades"] = 2.5;
    c2p["knight of hearts"] = 2.5; 
    c2p["knight of diamonds"] = 2.5; 
    c2p["knight of clubs"] = 2.5; 
    // jacks
    c2p["jack of spades"] = 1.5;
    c2p["jack of hearts"] = 1.5; 
    c2p["jack of diamonds"] = 1.5; 
    c2p["jack of clubs"] = 1.5; 
    
    return;
}

void fill_oudlers(unordered_set<string>& ods){
    ods.insert("fool");
    ods.insert("one of trumps");
    ods.insert("twenty-one of trumps");
    
    return;    
}

int main(){
    unordered_map<string, double> card2points;
    unordered_set<string> oudlers;
    
    fill_card2point(card2points);
    fill_oudlers(oudlers);
    
    int T, M; cin >> T;
    
    for(int t = 0; t < T; t++){
        cin >> M; cin.ignore();
        string card; 
        int ods = 0; double points = 0.0;
        for(int m = 0; m < M; m++){
            // process the cards
            getline(cin, card);
            if(oudlers.find(card) != oudlers.end()) // si es un oudler
                ods++;
            if(card2points.find(card) != card2points.end())
                points += card2points[card];
            else // si es una all other card
                points += 0.5;
        }
        
        // get the result
        int diff = 0;
        if(ods == 3)
            diff = (int)points - 36;
        else if(ods == 2)
            diff = (int)points - 41;
        else if(ods == 1)
            diff = (int)points - 51;
        else
            diff = (int)points - 56;
            
        if(diff >= 0){
            cout << "Hand #" << t+1 << "\nGame won by " << diff << " point(s).\n";
        }else{
            cout << "Hand #" << t+1 << "\nGame lost by " << abs(diff) << " point(s).\n";
        }
    }
    
    return 0;
}
