# include <bits/stdc++.h>

using namespace std;

class DPalign{
    vector< vector<int> > DP;
    vector< vector<char> > bt;
    string A; string B;
    int lenA, lenB;
    int pInsert = -1, pDelete = -1, match = 2, mismatch = -1;

    int count;

public:

    DPalign(const string& _A, const string& _B){
        A = _A; B = _B;
        lenA = _A.size(); lenB = _B.size(); // (int) strsize(A); ?

        // fix problem with lengths
        if(lenA < lenB){
            A = _B; B = _A;
            lenA = _B.size(); lenB = _A.size();
        }

        DP.assign(lenA+1, vector<int> (lenB+1)); 
        bt.assign(lenA+1, vector<char> (lenB+1)); 

        count = 0;

        buildDP();
        
    }

    void buildDP(){

        for(int i = 0; i < DP.size(); i++){ DP[i][0] = i; bt[i][0] = 'v'; }
        for(int j = 0; j < DP[0].size(); j++) {DP[0][j] = j; bt[0][j] = 'h';}
        bt[0][0] = 'd';

        for(int i = 1; i < DP.size(); i++){
            for(int j = 1; j < DP[0].size(); j++){
                DP[i][j] = DP[i - 1][j - 1] + (A[i - 1] == B[j - 1] ? match : mismatch);
                bt[i][j] = 'd';

                // estamos dandole prioridad a q aparezcan verticales en la tabla bt
                // por eso no funciona si lenA > lenB, pq 

                if( DP[i][j] < DP[i - 1][j] + pDelete){ // space in B, vertical
                    // cout << "entrando a vertical para " << i << ", " << j << endl;
                    DP[i][j] = DP[i - 1][j];
                    bt[i][j] = 'v';
                }
                // si eran iguales, se va a quedar con el vertical
                if( DP[i][j] < DP[i][j - 1] + pInsert){ // space in A, horizontal
                    // cout << "entrando a horizontal para " << i << ", " << j << endl;
                    DP[i][j] = DP[i][j - 1];
                    bt[i][j] = 'h';
                }

            }
        }
        return;
    }

    int getScore(){
        // nt idx = lenA + lenB;
        int i = lenA, j = lenB; // cout << i << "=" << lenA << "=" << bt.size()<< endl;

        while(!(i == 0 && j == 0)){ // quiero q se detenga cuando i == 0 && j == 0
            // cout << i << " " << j << endl; 
            if(bt[i][j] == 'h'){
                // cout << "h ";
                count ++; j--;
            }
            else if(bt[i][j] == 'v'){
                // cout << "v ";
                count ++; i--;
            }
            else{
                // cout << "d ";
                i--; j--;
            }
        }
        return count;
    }

    void printDP(){
        for(int i = 0; i < DP.size(); i++){
            for(int j = 0; j < DP[0].size(); j++){
                cout << DP[i][j] << " ";
            }
            cout << endl;
        }
    }

    void printBT(){
        for(int i = 0; i < bt.size(); i++){
            for(int j = 0; j < bt[0].size(); j++){
                cout << bt[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main(){
    string A = "MMPGMPPGG", B = "MGPMPG";
    // string B = "MMPGMPPGG", A = "MGPMPG";
    // string A = "ABC", B = "ABCDEF";
    // string A = "ABCDEF", B = "ABC"; // funciona si lenA > lenB, si no no

    DPalign align(A, B);

    cout << align.getScore() << endl;
}