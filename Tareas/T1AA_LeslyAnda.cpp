#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm> 

using namespace std;

template <class TPriority, class TKey> 
class UpdatableHeap {

private:

    struct HeapNode {
        TPriority priority;
        TKey key;

        bool operator<(const HeapNode &other) const {
                if (priority == other.priority){
                    return key > other.key;
                }
            return priority < other.priority;
        }
    };
    
    // declaramos el heap(p, k) y el map(k, idx en heap)
    vector<pair<TPriority, TKey>> heap;
    unordered_map<TKey, long long> id2pos;
    
    
    void heapify_down(vector<pair<TPriority, TKey>> &arr, unordered_map<TKey, long long> &i2p, long long idx){
        
        long long n = arr.size();

        // declaramos idx de lxs hijxs
        long long left = 2 * idx + 1;
        long long right = 2 * idx + 2;

        //hallamos hijx mas grande en prioridad
        long long biggest = idx;
        if(left < n && arr[idx].first < arr[left].first) biggest = left;
        if(right < n && arr[biggest].first < arr[right].first) biggest = right;

        // si tengo un hijx mas grande que yo
        if(biggest != idx){
            // le doy mi lugar en el heap (ahora hijx esta en idx y yo en biggest)
            swap(arr[idx], arr[biggest]);
            // arreglamos posiciones en el map
            i2p[arr[biggest].second] = biggest; i2p[arr[idx].second] = idx;
            // acomodamos hacia abajo en caso en caso de que el cambio haya roto el heap 
            heapify_down(arr, i2p, biggest);
        }
    
        return;
    }
    
    void heapify_up(vector<pair<TPriority, TKey>> &arr, unordered_map<TKey, long long> &i2p, long long idx){
        
        // si el nodo es la raiz no hay algo q hacer
        if(idx == 0) return;

        long long parent = (idx - 1)/2;

        // si mi padre es menor en prioridad
        if(arr[parent] < arr[idx]){
            // le quito el lugar (ahora yo en parent y mi madre en idx)
            swap(arr[idx], arr[parent]);
            // arreglamos posiciones en el map
            i2p[arr[parent].second] = parent; i2p[arr[idx].second] = idx;
            // me comparo (ahora como padre) con mi padre
            heapify_up(arr, i2p, parent);
        }
    
        return;
    }

public: 
    // solo regresamos el primer elemento del heap si no esta vacio
    pair<TPriority, TKey> top(){
        if(heap.size() == 0) {
            TPriority p = -1;                                   // que otra cosa se puede regresar aqui?
            TKey k;
            return make_pair(p, k); 
        }
        return heap[0];                                         
    }

    // elimina el elemento de mayor prioridad intercambiandolo con el ultimo nodo
    void pop(){
        if(heap.size() == 0) return;

        long long last = heap.size() - 1;

        // intercambiamos raiz con el ultimo nodo (ahora elemento de mayor prioridad en last)
        swap(heap[0], heap[last]);
        // acomodamos las posiciones 
        swap(id2pos[heap[0].second], id2pos[heap[last].second]); 

        // borramos el elemento de mayor prioridad (en last) del heap y del map
        id2pos.erase(heap[last].second);
        heap.pop_back();

        // acomodamos todo el heap
        heapify_down(heap, id2pos, 0);

        return;
    }

    // insertamos si no esta, actualizamos si si
    void insertOrUpdate(TPriority &p, TKey &k){
        
        // si no esta, asctualizamos y acomodamos
        if(isInserted(k) == 1){
            heap[id2pos[k]].first = p;
            heapify_down(heap, id2pos, id2pos[k]);
            heapify_up(heap, id2pos, id2pos[k]); 
            return; 
        }
        
        // si si esta, agreamos el final y acomodamos
        heap.push_back(make_pair(p, k));
        long long last = heap.size()-1;
        id2pos.insert({k, last}); 
        heapify_up(heap, id2pos, last);
        
        return;

    }

    // ve si existe el elemento en el heap
    bool isInserted(TKey &k){
        
        if(id2pos.count(k) == 0){
            return false;
        }
        
        return true;
    }

    // regresa el tamano del heap
    long long getSize(){
        return id2pos.size();
    }

    // borra un nodo si esta
    void erase(TKey &k){
        // si no esta o esta vacio el heap, regresa
        if (heap.empty() || !isInserted(k)) {
        return;
        }

        long long last = heap.size() - 1;
        // extraemos la posicion de esa clave en el heap
        long long idx = id2pos[k];

        // intercambia el nodo a borrar con el ultimo del heap
        swap(heap[idx], heap[last]);
        // ( yo en last y last en idx )
        id2pos[heap[idx].second] = idx;
        
        // borramos el ultimo elemento
        id2pos.erase(k);
        heap.pop_back();
        
        // si el remplazo no es ahora un nodo hoja, acomodamos el heap
        if(idx < getSize()){
            heapify_down(heap, id2pos, idx);
            heapify_up(heap, id2pos, idx);
        }

        return;
    }

};


int main() {
    UpdatableHeap<long long, string> uHeap;
    int OP; cin >> OP;
    string type;

    long long priority;
    string key;
    
    vector<string> sol;

    for(int i = 0; i < OP; i++){
        cin >> type;
        if(type == "P"){
            priority = uHeap.top().first; 
            key = uHeap.top().second;

            if (priority == -1) sol.push_back("-1");
            else{
                sol.push_back(key + ' ' + to_string(priority));
            }
        }

        if(type == "IU"){
            cin >> key >> priority;
            uHeap.insertOrUpdate(priority, key);
        }

        if(type == "DL"){
            uHeap.pop();
        }

        if(type == "D"){
            cin >> key;
            uHeap.erase(key);
        }
    }
    
    for (const auto &s : sol) {
        cout << s << endl;
    }
    
}

// P R I M E R A   V E R S I O N

// #include <iostream>
// #include <string>
// #include <vector>
// #include <unordered_map>
// #include <algorithm> 

// using namespace std;

// template <class TPriority, class TKey> 
// class UpdatableHeap {

// private:

// // ¿CÓMO SOBRECARGO EL OPERADOR?

// struct HeapNode{
//     TPriority priority;
//     TKey key;

//     bool opertator<(const HeapNode &other) const{            // Sobrecargamos el operador menor que
//         return priority < other.priority;                   // para poder comparar los prioridades no int
//     }
// };

// vector<pair<TPriority, TKey>> heap;
// unordered_map<TKey, int> id2pos;

// // void buildHeap(vector<pair<TPriority, TKey>> &arr){
// //     int n = vec.size();
// //     for (int i = n / 2 - 1; i >= 0; i--) heapify_down(arr, n, i);  
// // }

// void heapify_down(vector<pair<TPriority, TKey>> &arr, int idx){

//     int n = arr.size();
//     int left = 2 * idx;
//     int right = 2 * idx + 1;

//     int biggest = idx;
//     if(left < n && arr[idx].first < arr[left].first) biggest = left;
//     if(right < n && arr[idx].first < arr[right].first) biggest == right;

//     if(biggest != idx){
//         swap(arr[idx], arr[biggest]);
//         id2pos[biggest] = idx; id2pos[idx] = biggest;
//         heapify_down(arr, biggest);
//     }

//     return;
// }

// void heapify_up(vector<pair<TPriority, TKey>> &arr, int idx){
//     if(idx == 0) return;

//     int parent = (idx - 1)/2;

//     if(arr[parent] < arr[idx]){
//         swap(arr[idx], arr[parent]);
//         id2pos[parent] = idx; id2pos[idx] = parent;
//         heapify_up(parent);
//     }

//     return;
// }

// public: 

//     pair<TPriority, TKey> top(){
//         if(heap.size() == 0) return make_pair(-1, -1);          // ¿ESTÁ BIEN QUE REGRESE ESTO?
//         return heap[0];                                         // Solo regresamos el primer elemento del heap
//     }

//     void pop(){
//         if(heap.size() == 0) return;

//         int last = heap.size() - 1;

//         swap(heap[0], heap[last]);
//         swap(id2pos[0], id2pos[last]);

//         id2pos.erase(last);
//         heap.pop_back();

//         heapify_down(heap, 0);

//         return;
//     }

//     void insertOrUpdate(TPriority &p, TKey &k){
//         if(heap.isInserted(k) == true){
//             heap[id2pos[k].first] == p;
//             return; 
//         }

//         heap.push_back(make_pair(p, k));
//         int last = heap.size()-1;

//         id2pos.insert({k, last}); 
//         heapify_up(heap, last);

//         return;

//     }

//     bool isInserted(TKey &k){
//         int temp = id2pos.count(k);

//         return (temp == 0 ? false : true);
//     }

//     int getSize(){
//         return id2pos.size();
//     }

//     void erase(TKey &k){
//         if(heap.size() == 0 || isInserted(TKey &k) == false){
//             return; 
//         }

//         int last = heap.size() - 1;
//         int idx = id2pos[k];

//         swap(heap[idx], heap[last]);
//         swap(idx, id2pos[last]);

//         heap.pop_back();
//         id2pos.erase(last);

//         heapify_down(heap, idx);
//         heapify_up(heap, idx);

//         return;
//     }

// };


// int main() {
//     UpdatableHeap<int, string> uHeap;
//     int OP; cin >> OP;
//     string type;

//     int priority;
//     string key;

//     for(int i = 0; i < OP; i++){
//         cin >> type;
//         if(type == "P"){
//             priority = uHeap.top().first; 
//             key = uHeap.top().second;

//             if (priority == -1) cout << priority << endl;
//             else{
//                 cout << key << ' ' << priority;
//             }
//         }

//         if(type == "IU"){
//             cin >> key >> priority;
//             uHeap.insertOrUpdate(priority, key);
//         }

//         if(type == "DL"){
//             uHeap.pop();
//         }

//         if(type == "D"){
//             cin >> key;
//             uHeap.erase(key);
//         }
//     }
// }
