# include <bits/stdc++.h>

using namespace std;

class DPalign{
    vector< vector<int> > DP; // matriz de costos
    vector< vector<string> > bt; // matriz de operaciones
    string A; string B;
    int lenA, lenB;
    int pInsert = 1, pDelete = 1, pMatch = 0, pMismatch = 1, pSwap = 1;

public:

    DPalign(const string& _A, const string& _B){
        A = _A; B = _B;
        lenA = _A.size(); lenB = _B.size();

        // fix problem with lengths
        if(lenA < lenB){
            A = _B; B = _A;
            lenA = _B.size(); lenB = _A.size();
        }

        DP.assign(lenA+1, vector<int> (lenB+1)); 
        bt.assign(lenA+1, vector<string> (lenB+1)); 

        damerau_levenshtein();
        
    }

    void damerau_levenshtein(){
        // casos base
        for(int i = 0; i < DP.size(); i++){ DP[i][0] = i * pDelete; bt[i][0] = "delete"; }
        for(int j = 0; j < DP[0].size(); j++) {DP[0][j] = j * pInsert; bt[0][j] = "insert";}
        bt[0][0] = "match";

        // llenamos matriz
        for(int i = 1; i < DP.size(); i++){
            for(int j = 1; j < DP[0].size(); j++){
                // tomamos diagonal + costo de match/mismatch
                DP[i][j] = DP[i - 1][j - 1] + (A[i - 1] == B[j - 1] ? pMatch : pMismatch);
                bt[i][j] = (A[i - 1] == B[j - 1] ? "match" : "mismatch");

                // tomamos celda superior + costo de borrar un caracter en A 
                if( DP[i][j] > DP[i - 1][j] + pDelete){ // space in B, vertical
                    DP[i][j] = DP[i - 1][j] + pDelete;
                    bt[i][j] = "delete";
                }

                // tomamos celda inferior + costo insertar espacio en A
                if( DP[i][j] > DP[i][j - 1] + pInsert){ // space in A, horizontal
                    DP[i][j] = DP[i][j - 1] + pInsert;
                    bt[i][j] = "insert";
                }

                // tomamos la celda que machea A[0,i-3] con B[0,j-3] + el costo de intercambiar A[i-1] con A[i-2]
                if((i > 1 && j > 1) && (A[i-1] == B[j-2] && A[i-2] == B[j-1]) ){
                    if(DP[i][j] > DP[i-2][j-2] + pSwap){
                        DP[i][j] = DP[i-2][j-2] + pSwap;
                        bt[i][j] = "swap";
                    }
                }
            }
        }
        return;
    }

    int getScore(){
        return DP[lenA][lenB];
    }

    void getChanges(){
        int i = lenA, j = lenB; 

        while(!(i == 0 && j == 0)){ // se detiene cuando i == 0 && j == 0
            if(bt[i][j] == "match" || bt[i][j] == "mismatch"){
                if(bt[i][j] == "match") cout << " - Match " << A[i-1] << " y " << B[j-1] << " + 0 " << endl;
                else cout << " - Sustituir " << A[i-1] << " con " << B[j-1] << " + 1 " << endl;
                i--; j--; // subimos en diagonal
            }
            else if(bt[i][j] == "insert"){
                cout << " - Insertar " << B[j-1] << " en la posicion" << j << " + 1 " << endl;
                j--; // regresamos horizontal
            }
            else if(bt[i][j] == "delete"){
                cout << " - Eliminar " << A[i-1] << " de la posicion" << i << " + 1 " << endl;
                i--; // subimos en vertical
            }
            else{
                cout << " - Swap " << A[i-2] << " con " << A[i-1] << " + 1 " << endl;
                i-= 2; j-= 2; // regresamos dos saltos en diagonal
            }
        }
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
    string A = "LEON", B = "LOEN";
    // string B = "MMPGMPPGG", A = "MGPMPG";
    // string A = "ABC", B = "ABCDEF";
    // string A = "ABCDEF", B = "ABC";
    // string A = "ACAATCC", B = "AGCATGC";

    DPalign align(A, B);

    // align.printDP();
    // cout << endl;
    // align.printBT();

    // imprimimos costo
    cout << "Costo: " << align.getScore() << endl;
    // imprimimos las acciones
    cout << "Steps: " << endl; align.getChanges();
}