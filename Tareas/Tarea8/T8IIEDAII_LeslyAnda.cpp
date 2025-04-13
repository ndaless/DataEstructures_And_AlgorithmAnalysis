#include <bits/stdc++.h>

using namespace std;

class StrMerge{
    vector< vector<int> > DP;
    string A, B, C;
    int lenA, lenB, lenC;

public:
    StrMerge(const string& _A, const string& _B, const string& _C){
        A = _A; B = _B; C = _C;
        lenA = A.size(); 
        lenB = B.size();
        lenC = C.size();

        DP.assign(lenA + 1, vector<int> (lenB + 1)); // +1 pq agregamos caracter vacio al inicio de a y b

        buildDP();
    }

    void buildDP(){
        // llenamos [0][0] y primer fila y columna
        DP[0][0] = 1;
        for(int i = 1; i < DP.size(); i++)
            DP[i][0] = (A[i-1] == C[i-1]) ? 1 : 0;
        for(int j = 1; j < DP[0].size(); j++)
            DP[0][j] = (B[j-1] == C[j-1]) ? 1 : 0;
        
        for(int i = 1; i < DP.size(); i++){
            for(int j = 1; j < DP[0].size(); j++){
                if(DP[i][j - 1] == 1 && B[j - 1] == C[i+j - 1]){ // horizontal
                    cout << "Llenando DP[" << i << "][" << j <<"] con 1." << endl;
                    DP[i][j] = 1;
                }
                else if(DP[i - 1][j] == 1 && A[i - 1] == C[i+j - 1]){ // vertical 
                    cout << "Llenando DP[" << i << "][" << j <<"] con 1." << endl;
                    DP[i][j] = 1;
                }
                else{
                    cout << "Llenando DP[" << i << "][" << j <<"] con 0." << endl;
                    DP[i][j] = 0;
                }
            }
        }
        return;
    }

    bool isMerge(){
        // si C tiene mas o menos caracteres que A y B juntas, no es mezcla
        if(lenC != lenA + lenB) return 0;

        return DP[lenA][lenB]; // sin -1 pq en la DP agregamos un vacio al inicio
                                // idx al final de tabla coincide con numero de caracteres en str
    }

    void printDP(){
        for(int i = 0; i < DP.size(); i++){
            for(int j = 0; j < DP[0].size(); j++){
                cout << DP[i][j] << " ";
            }
            cout << endl;
        }
    }

};

int main(){
    // se puede implementar para repsonder muchas qrys con solo una matriz?
    string A = "SILAO", B = "LEON", C = "SILLEAOON";
    // string A = "SILAO", B = "LEON", C = "SILAO";
    // string A = "SILAO", B = "LEON", C = "SILLEAOONO";
    // string A = "SILAO", B = "LEON", C = "SILALOEON";
    // string A = "SILAO", B = "LEON", C = "SLILEANOO";
    StrMerge merge(A, B, C);

    // merge.printDP();

    cout << merge.isMerge() << endl;

    return 0;
}