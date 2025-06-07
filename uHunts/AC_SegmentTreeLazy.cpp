#include <bits/stdc++.h>
#define optimizar_io
using namespace std;

// enum STATE{
//     E0=0,
//     F1=1,
//     I=2,
//     NONE=3
// };

struct ST{
    int n;
    vector<int> A;                                                          // Vector de valores iniciales 
    vector<int> st;                                                         // Segmente Tree

    vector<int> lzy;                                                        // Vector de estados lazy

public:
    ST(vector<int> &a){                                                     // Construimos loa elementos necesarios
        A = a;
        n = a.size();
        st.resize(4*n);

        lzy.assign(4*n, 3);

        buildST(1, 0, n-1);
        return;
    }

    void buildST(int nd, int L, int R){                                     // Funcion que construye el arbol princial,        
        // (idx, idx ini, idx fin) -> void                                  // recibe el nodo raiz y los extremos del 
                                                                            // intervalo para construir el arbol
        if (L == R){                                                        // Caso base: llegar a una hoja y anadir        
            st[nd] = A[L];
            return;
        }

        buildST(left(nd), L, (L+R)/2);                                      // Si no hemos llegado a un nodo hoja,
        buildST(right(nd), (L+R)/2+1, R);                                   // construimos los hijo del nodo actual.
        
        st[nd] = st[left(nd)] + st[right(nd)];                              // Nodo actual se construye con nodos hijos
       
        return;
    }

    void update(int nd, int L_nd, int R_nd, int l, int r, int action){      // Funcion que recibe el intervalo a actualizar             
        push(nd, L_nd, R_nd);                                               // Y dependiendo de la qry, fija o intercambia 
                                                                            // los valores.
        if(L_nd > r || R_nd < l){
            return;
        }

        if( L_nd >= l && R_nd <= r ){
            lzy[nd] = action;
            push(nd, L_nd, R_nd);
            return;
        }

        int mid = (L_nd + R_nd)/2;

        update(left(nd), L_nd, mid, l, r, action);
        update(right(nd), mid+1, R_nd, l, r, action);

        st[nd] = st[left(nd)] + st[right(nd)];
        return;

    }

    void update(int l, int r, int action){
        update(1, 0, n-1, l, r, action);
    }

    int qry(int nd, int L_nd, int R_nd, int l, int r){                      // Funcion que responde la qry de solicitud.
                                                                            // Recibe el intervalo del que se quiere
        push(nd, L_nd, R_nd);                                               // conocer el numero de 1's

        if(L_nd > r || R_nd < l){
            return 0;
        } 

        if( L_nd >= l && R_nd <= r ){
            return st[nd];
        }

        int mid = (L_nd + R_nd)/2;

        return qry(left(nd), L_nd, mid, l, r) + qry(right(nd), mid+1, R_nd, l, r);
    }

    int qry(int l, int r){
        return qry(1, 0, n-1, l, r);
    }

    void push(int nd, int L_nd, int R_nd){                                  // Funcion que actualiza el valor del nodo 
                                                                            // que recibe, dejandolo sin tag pendiente
        if( lzy[nd] == 3 ){                                                 // y pasa el tag a los hijos. 
            return;
        }

        else if (lzy[nd] == 0){
            st[nd] = 0;
        }

        else if (lzy[nd] == 1){
            st[nd] = R_nd - L_nd + 1;
        }

        else if(lzy[nd] == 2){
            st[nd] = (R_nd - L_nd + 1) - st[nd];
        }

        if( L_nd < R_nd ){
            setLzyTag(left(nd), lzy[nd]), setLzyTag(right(nd), lzy[nd]);
        }

        lzy[nd] = 3;
    }

    void setLzyTag(int nd, int action){                                     // Funcion auxiliar para push. Solo asigna 
                                                                            // el tag lazy al nodo evaluando los casos 
        if (action == 0){                                                   // para combinar los tags correctamente.
            lzy[nd] = 0;
        }

        else if (action == 1){
            lzy[nd] = 1;
        }

        else if(action == 2){
            if(lzy[nd] == 0){
                lzy[nd] = 1;
            }
            else if(lzy[nd] == 1){
                lzy[nd] = 0;
            }
            else if(lzy[nd] == 2){
                lzy[nd] = 3;
            }
            else if(lzy[nd] == 3){
                lzy[nd] = 2;
            }
        }
    }

private:
    int left(int p){                                                        // Funcion que regresa el indice del 
        // (idx) -> idx                                                     // hijo izquierdo del nodo dado.
        return p << 1;
    }

    int right(int p){    
        // (idx) -> idx                                                     // Funcion que regresa el indice del 
        return (p << 1) + 1;                                                // hijo derecho del nodo dado.
    }

};

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);

    int casos, M, Q, n, l, r;
    string stg = "", mainStg = "";
    char type;
    
    cin >> casos;
    
    for (int i=0; i < casos; i++){
        cin >> M;
        for(int j=0; j<M; j++){
            cin >> n >> stg;
            for (int k=0; k<n; k++){
                mainStg += stg;
            }
            stg = "";
        }
        
        vector<int> A;
        
        for (char c : mainStg) {
            if (c == '0') {
                A.push_back(0);
            } 
            else if (c == '1') {
                A.push_back(1);
            } 
        }
        
        ST mainTree(A);

        cin >> Q;

        for(int m=0; m<Q; m++){
            cin >> type;
            if( type == 'F'){
                //cout << "entrando a caso F" << endl;
                cin >> l >> r;
                mainTree.update(l, r, 1);
            }
            else if( type == 'E'){
                //cout << "entrando a caso E" << endl;
                cin >> l >> r;
                mainTree.update(l, r, 0);
            }
            else if( type == 'I'){
                //cout << "entrando a caso I" << endl;
                cin >> l >> r;
                mainTree.update(l, r, 2);
            }
            else if( type == 'S'){
                //cout << "entrando a caso S" << endl;
                cin >> l >> r;
                cout << mainTree.qry(l, r) <<endl; 
            }
        }
        
        mainStg = "";
    
    }

    return 0;
}