# include <bits/stdc++.h>
// # include <istream>
# include <ext/pb_ds/assoc_container.hpp> // common file
# include <ext/pb_ds/tree_policy.hpp> // including tree_order_statistics_node_update
// # include <vector>
// # include <queue>
# include <algorithm>
// # include <climits>

using namespace std;
using namespace __gnu_pbds;

typedef tree <pair<int, int>,
            null_type,
            less< pair<int, int> >,
            rb_tree_tag,
            tree_order_statistics_node_update> ordered_set;

struct Ext_ST{
    int val_max = 100000;
    
    int N;
    vector < int > arr;         // arreglo original
    vector < int > o_arr;       // sorted posible values
    vector <ordered_set> st;    // segment tree con sets en nodos

    Ext_ST(vector < int > &_arr, vector < int > &_oarr){
        N = _arr.size();
        arr = _arr;
        o_arr = _oarr;

        st.resize(4*N);

        buildExtST(0, 0, N-1);
    }

// funcion que construye el st armando los sets de los nodos
void buildExtST(int nd, int L, int R){
    if (L == R){
        st[nd].insert({arr[L], L});
        return;
    }

    buildExtST(left(nd), L, (R+L)/2);
    buildExtST(right(nd), (R+L)/2 + 1, R);

    st[nd] = st[left(nd)];
    for(auto newPair : st[right(nd)]){
        st[nd].insert(newPair);
    }

    return;
}

// responde quien queda en la posicion k del subarray [l,r]
int answ(int l, int r, int k){
    
    if(k > r - l){
        return -1;
    }
    // busqueda binaria solo en posibles valores
    int count; int L = 0; int R = o_arr.size()-1; int mid;

    while(L < R){
        mid = (R + L)/2; 
        
        // vemos cuantos valores hay <= que el valor elegido en la bs
        count = kcount(l, r, o_arr[mid]); 

        if(count <= k){
            L = mid + 1;
        }else{
            R = mid;
        }
    }
    
    return o_arr[L];
}

// funcion que cuenta cuandos elemntos hay <= que val en el subarreglo [l,r], buscando los nodos correspondientes del st
int kcount(int nd, int L_nd, int R_nd, int l, int r, int val){
    
    if(r < L_nd || l > R_nd ){
        return 0;
    }
    
    if(l <= L_nd && R_nd <= r ){
        return st[nd].order_of_key({val, INT_MAX});
    }
    
    return kcount(left(nd), L_nd, (R_nd + L_nd)/2, l, r, val) 
           + kcount(right(nd), (R_nd + L_nd)/2 + 1, R_nd, l, r, val);

}

int kcount(int l, int r, int val){
    return kcount(0, 0, N-1, l, r, val);
}

// qry para cambiar el valor en idx a val
void update(int nd, int L, int R, int idx, int val){
    
    // borramos valor anterior e insertamos nuevo valor en los sets de los nodos
    st[nd].erase({arr[idx], idx}); //logN
    st[nd].insert({val, idx}); // logN

    // al finalizar, actualizamos el valor en el arreglo original
    if(L == R){
        arr[idx] = val;
        return;
    }

    // seguimos buscando los nodos afectados
    if (idx <= (R+L)/2){
        update(left(nd), L, (R+L)/2, idx, val);
    } else{
        update(right(nd), (R+L)/2 + 1, R, idx, val);
    }
    return;
}

void update(int idx, int val){
    update(0, 0, N-1, idx, val);
}

private:

int left(int nd){
    return 2*nd + 1;
}

int right(int nd){
    return 2*nd + 2;
}

};

int main(){
    int N; cin >> N;
    vector< int > arr(N); vector <int> o_arr;

    int val;
    for(int i = 0; i<N; i++){
        cin >> val; arr[i] = val; o_arr.push_back(val);
    }

    int M; cin >> M;
    int qtype, idx, l, r, k;

    vector<int> qrys;  queue< pair<pair<int, int>, int> > qrys0; queue< pair<int, int> > qrys1;

    for (int i=0; i<M; i++){
        cin >> qtype; qrys.push_back(qtype);

        if (qtype == 0){
            cin >> l >> r >> k;
            qrys0.push({{l, r}, k});
        } else{
            cin >> idx >> val;
            qrys1.push({idx, val}); o_arr.push_back(val);
        }
    }

    sort(o_arr.begin(), o_arr.end());
    Ext_ST st(arr, o_arr);

    for(auto qry : qrys){
        if(qry == 0){
            pair<pair<int, int>, int> dato = qrys0.front();
            qrys0.pop();
            cout << st.answ(dato.first.first, dato.first.second, dato.second) << endl;
        } else{
            pair<int, int> dato = qrys1.front();
            qrys1.pop();
            st.update(dato.first, dato.second);
        }
    }

    return 0;
}

// P R I M E R A   V E R S I O N 

// # include <iostream>
// # include <ext/pb_ds/assoc_container.hpp> // common file
// # include <ext/pb_ds/tree_policy.hpp> // including tree_order_statistics_node_update
// # include <vector>
// # include <climits>

// using namespace std;
// using namespace __gnu_pbds;

// typedef tree <pair<int, int>,
//             null_type,
//             less< pair<int, int> >,
//             rb_tree_tag,
//             tree_order_statistics_node_update> ordered_set;

// struct Ext_ST{

//     int N;
//     vector < int > arr; // arr<val, pos>
//     vector <ordered_set> st;

//     Ext_ST(vector < int > _arr){
//         N = _arr.size();
//         arr = _arr;

//         st.resize(4*N);

//         buildExtST(0, 0, N-1);
//     }

// void buildExtST(int nd, int L, int R){
//     if (L == R){
//         st[nd].insert({arr[L], L});
//     }

//     buildExtST(left(nd), L, (R+L)/2);
//     buildExtST(left(nd), (R+L)/2 + 1, R);

//     st[nd] = st[left(nd)];
//     for(auto newPair : st[right(nd)]){
//         st[nd].insert(newPair);
//     }

//     return;
// }
// // qry answare quien queda en la posicion k
// int answ(int l, int r, int k){
//     // int low = arr[0]; int high = arr[N-1];
//     int count; int L = 0; int R = N-1; int mid;

//     while(L < R){
//         mid = (R+L)/2;
//         count = kcount(l, r, arr[mid]);

//         if(count == k + 1){
//             return arr[mid];
//         }

//         if(count <= k){
//             L = mid + 1;
//         }else{
//             R = mid;
//         }
//     }
//     return -1;
// }

// int kcount(int nd, int L_nd, int R_nd, int l, int r, int val){
    
//     if(r < L_nd || l > R_nd ){
//         return 0;
//     }
    
//     else if(l <= L_nd && R_nd <= r ){
//         return st[nd].order_of_key({val, INT_MAX});
//     }
    
//     return kcount(left(nd), L_nd, (R_nd - L_nd)/2, l, r, val) 
//            + kcount(right(nd), (R_nd - L_nd)/2 + 1, R_nd, l, r, val);
    

// }

// int kcount(int l, int r, int val){
//     return kcount(0, 0, N-1, l, r, val);
// }

// // qry para cambiar el valor en idx a val
// void update(int nd, int L, int R, int idx, int val){

//     st[nd].erase({arr[idx], idx});
//     st[nd].insert({val, idx});

//     if(L == R){
//         arr[idx] = val;
//     }

//     if (idx <= (R-L)/2){
//         update(left(nd), L, (R-L)/2, idx, val);
//     } else{
//         update(right(nd), (R-L)/2 + 1, R, idx, val);
//     }
//     return;
// }

// void update(int idx, int val){
//     update(0, 0, N-1, idx, val);
// }

// private:

// int left(int nd){
//     return 2*nd + 1;
// }

// int right(int nd){
//     return 2*nd + 2;
// }

// };

// int main(){
//     int N; cin >> N;
//     vector< int > arr(N);

//     int val;
//     for(int i = 0; i<N; i++){
//         cin >> val; arr[i] = val;
//     }

//     Ext_ST st(arr);

//     int M;
//     cin >> M;

//     int qtype, idx, l, r, k;

//     for (int i=0; i<M; i++){
//         cin >> qtype;

//         if (qtype == 0){
//             cin >> l >> r >> k;
//             // cout << "Caso Query0 con" << l << r << k << endl;
//             cout << st.answ(l, r, k) << endl;
//         }

//         else if(qtype == 1){
//             cin >> idx >> val;
//             st.update(idx, val);
//         }
//     }

//     return 0;
// }
