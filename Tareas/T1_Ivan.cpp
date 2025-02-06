/**************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

***************************/

//1#include <iostream>

#include <bits/stdc++.h>
#include <vector>
#include <map>
using std::vector; //Vamos a usar vector
using namespace std;

// #include <iostream>
// #include <utility>

// template <class TPriority, class TKey> class Node{
//     // vector<some type> data;    // Datos guardados en cada heap.
//     TPriority priority;
//     TKey key;
// };

template <class TPriority, class TKey> class UpdatableHeap {
private:

	class Node { // Definimos la clase nodo que es la que tendrC! los datos (no aplica en este caso), la prioridad y la llave (o id)

	public:
		// class data;    // Datos guardados en cada heap.
		TPriority priority;
		TKey key;

		bool operator<(const Node& other) const {       //Comparador de menor que para la clase nodo
			if(priority == other.priority) { // Primero nos fijamos en si la prioridad es la misma
				return (key < other.key);       // Si es el caso devolvemos lo que corresponde al orden lexicogrC!fico (string ya tiene un orden)
			} else {
				return (priority < other.priority); // De otro modo devolvemos el orden que tiene que ver con la prioridad
			}
		}
	};


	map<TKey, int> mapa; //Mapa donde a llaves C:nicas les asignaremos su C-ndice en el heap

	// POSIBLE ERROR (p = (i -1)/2) si indexado en 0
	int parent(int i) {
		return (i-1)/2;
	}


	// FUNCION HEAPIFY UP ITERATIVA
	void increaseKey(int index) {
		int i = index;
		while(i > 0 && (heap[parent(i)] < heap[i])) {
			mySwap(i, parent(i));
			i = parent(i);
		}
	}

	int left(int index) {
		return 2*index + 1;
	}

	int right(int index) {
		return (2*index) + 2;
	}

	// INTERCAMBIA VALORES EN MAP Y HEAP
	void mySwap(int i, int j) {
		if(i < heapSize && j < heapSize) { // Si ambos nodos existen
			Node pivote = heap[j]; //Creamos un nodo pivote

			mapa[heap[i].key] =  j; //Actualizamos el mapa
			mapa[heap[j].key] = i;

			heap[j].priority = heap[i].priority;// Hacemos cambios en el heap
			heap[j].key = heap[i].key;
			heap[i].priority = pivote.priority;
			heap[i].key = pivote.key;
			return;
		} else {
			// cout << "No es posible intercambiar el elemento " << i << " con " << j << "\n";
			return;
		}
	}

	// HEAPIFY DOWN
	void max_heapify(int index) { //La funciC3n que mantiene la propiedad de heap
		int l = left(index), r = right(index);
		int bigger;

		if(l < heapSize && heap[index] < heap[l]) { // Si el de la izquierda es mayor
			bigger = l; //Pues el mayor hasta el momento es el de la izquierda
		} else {
			bigger = index; // Sino pues el mayor sigue siendo index
		}

		// if(bigger != r){//Si bigger es distinto a r y por tanto a index entonces los comparo
		//     if(r <= heapSize && heap[bigger] < heap[r]){ // Ahora, si el que tenC-amos por el mC!s grande es mC!s pequeC1o que el de la derecha
		//     bigger = r; //Entonces el mC!s grande al final fue el de la derecha
		//     }  //De otro modo no hacemos algo
		// }

		if(r < heapSize && heap[bigger] < heap[r]) { // Ahora, si el que tenC-amos por el mC!s grande es mC!s pequeC1o que el de la derecha
			bigger = r; //Entonces el mC!s grande al final fue el de la derecha
		}  //De otro modo no hacemos algo

		if(bigger != index) { //Si resultC3 que el C-ndice del mayor no fue el original
			mySwap(bigger, index); // intercambiamos el mC!s grande por el C-ndice

			max_heapify(bigger); //Y hacemos lo mismo para este que quedC3 mC!s grande
			// max_heapify(bigger);
		}


		/*
		 int l = left(index), r = right(index);
		 int bigger;

		 if(l <= heapSize && r <= heapSize && heap[l] < heap[r]){ // Comparamos
		     bigger = r
		 } else{
		     bigger l
		 }

		 */

	}








public:
	int heapSize = 0;

	vector<Node> heap; // Vector donde tendremos el heap

	pair<TPriority, TKey> top() const {         // devuelve el elemento de mayor prioridad (devuelve la prioridad y la clave)
		// if(heap.empty()){       // Si el heap estC! vacC-o no devuelvas nada.
		//     // cout << "El heap esta vacio." << "\n";
		//     return NULL;
		// }
		pair<TPriority, TKey> Top;
		Top.first = heap[0].priority;
		Top.second = heap[0].key; // De otro modo definimos el par con la informaciC3n del elemento de mayor prioridad (el que estC! en la raiz)
		return Top;     //Y lo devolvemos
	}


	void pop() {
		if(heap.empty()) {      // Si el heap estC! vacC-o no haces nada.
			// cout << "-1\n";
			return;
		}

		TKey erased_key = heap[0].key; // guardamos (LA CLAVE) el C-ndice del elemento que queremos borrar

		// heap[0].priority = heap[heapSize - 1].priority; // Cambiamos el C:ltimo nodo por el primero.
		// heap[0].key = heap[heapSize - 1].key;

		// (LOGICA 0 AQUI

		mySwap(0, heapSize - 1); // cambiamos el C:ltimo nodo por el primero

		mapa.erase(erased_key); // Borramos llave del mapa
		//heap.erase(heap.end() - 1); // Eliminamos el C:ltimo elemento.
		heap.pop_back();

		heapSize -= 1; //Actualizamos el tamaC1o del heap

		max_heapify(0);
		// increaseKey(heapSize - 1);
	}


	void insertOrUpdate(const TPriority &p, const TKey &k) {
		if(mapa.find(k) == mapa.end()) { //Si en el mapa no estC! considerado el par con llave k entonces hay que construir un nuevo nodo y aC1adir la informaciC3n de este al mapa
			Node newNode;//creamos un nodo nuevo con los argumentos
			newNode.key = k;
			newNode.priority = p;
			heapSize += 1; //Aumentamos el tamaC1o del heap

			// heap.insert(heap.end(), newNode);//Insertamos dicho nodo creado al heap (AL FINAL)
			heap.push_back(newNode); // TE INSERTA EL NUEVO NODO AL FINAL DEL (VECTOR) HEAP
			// LOGICA CERO AQUC
			mapa.insert(pair<TKey, int> (k, heapSize - 1)); //En el mapa este nodo tiene el C:ltimo C-ndice

			increaseKey(heapSize - 1);//Lo acomodamos en el heap MANDANDOLE EL IDX
		} else { // De lo contrario entonces sC- tenemos un elemento con llave k en el heap, modificaremos su prioridad
			int index = mapa[k]; //Hallamos el C-ndice gracias al mapa
			heap[index].priority = p; //Actualizamos la prioridad.
			max_heapify(index);
			// UNA VEZ ACOMODADO EL ARBOL DE ESE NODO, VE SI EL NODO ESTA ACOMODADO CON SUS ANCESTROS
			increaseKey(index);
		}
	}

	// ESTO POSIBLEMENTE RESERE 0 Y 1
	bool isInserted(const TKey &k) const {
		if(mapa.find(k) == mapa.end()) { //si no estC! la llave en el mapa
			return false; //Devolvemos false
		} else {
			return true; //De otro modo si tenemos a la llave en el mapa y por tanto si estC! el nodo con llave k
		}
	}


	int getSize() const { // Devolvemos el tamaC1o del mapa que es el tamaC1o del heap
		return mapa.size();
	}

	void imprimeHeapInFucntion() {
		if(heapSize == 0) {
			cout << "El heap esta vacio\n";
		} else {
			cout << "\ninicia impresion\n";
			for(int i = 0; i < heapSize; i++) {
				cout << heap[i].key << " " << heap[i].priority << "\n";
			}
			// cout << "\nacaba impresion\n";
		}
	}


	void erase(const TKey &K) {
		if(mapa.find(K) != mapa.end()) { // Si el elemento con llave K sC- estC! en el heap entonces hacemos todo normal
			// cout << "se metio al if";

			int erased_index = mapa[K], last_index = heapSize - 1; // obtenemos los C-ndices del elemento que queremos borrar en el heap y el C-ndice del C:ltimo elemento del heap


			// cout << "\nerased_index = " << erased_index << ", last index = " << last_index;

			// cout << "\nHeap antes de swap\n";
			// imprimeHeapInFucntion();


			// TKey erased_key =
			mySwap(erased_index, last_index);// Cambiamos los nodos del que queremos borrar y del C:ltimo C-ndice

			// cout << "\nHeap despues de swap\n";
			// imprimeHeapInFucntion();

			mapa.erase(K); // Borramos al nodo con llave K del mapa
			// NO SE COMO FUNCIONA ERASE EN EL VECTOR JSJSJ POR ESO USE POP_BACK
			heap.pop_back();
			// heap.erase(heap.end() - 1); // Borramos el C:ltimo nodo del vector.
			heapSize -= 1; //Reducimos el tamaC1o del heap

			// cout << "\nHeap despues de borrar el ultimo nodo\n";
			// imprimeHeapInFucntion();

			// cout << "erased index = "
			if (erased_index != last_index) {
                max_heapify(erased_index);
                increaseKey(erased_index);
            }

			// cout << "\nHeap despues del maxeapify\n";
			// imprimeHeapInFucntion();

			return;
		}// De otro modo no hacemos nada
		// cout << "no se metio al if";
		return;
	}

};


//  void ejecute(string OP, ){            //FunciC3n que recibe C3rdenes y ejecuta funciones del heap (para este problema)
//             if (OP == "P"){
//                 pair<int, string> alimentoMayor = UpdatableHeap.top();

//             } else if(OP == "IU"){

//             } else if(OP == "DL"){

//             } else if(OP == "D"){

//             }
// }

// template <class TPriority, class TKey>
// UpdatableHeap<


// template <class TPriority, class TKey>
// pair<TPriority, TKey> UpdatableHeap::top() const{

// }

void imprimeHeap(UpdatableHeap<int, string> UH) {
	if(UH.heapSize == 0) {
		cout << "El heap esta vacio\n";
	} else {
		cout << "\ninicia impresion\n";
		for(int i = 0; i < UH.heapSize; i++) {
			cout << UH.heap[i].key << " " << UH.heap[i].priority << "\n";
		}
		// cout << "\nacaba impresion\n";
	}
}


int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	UpdatableHeap<int, string> alimentos; //Creamos la clase alimentos

	int OP_size; //NC:mero de operaciones a recibir
	string OP; // OperaciC3n en cuestion

	cin >> OP_size; // Primero recibimos el nC:mero de operaciones porque en funciC3n a esto estaremos recibiendo OP_size cantidad de inputs


	// //Vamos a debuguear

	// int newPriority; string newKey; string eraseAliment; pair<int, string> alimentoMayor;

	// //Primero recibimos P (como no hay elementos en el heap pues imprime -1 o sea el mensaje)
	// imprimeHeap(alimentos);

	// //Luego recibe un alimento (pato)
	// newPriority = 1; newKey = "Pato";
	// alimentos.insertOrUpdate(newPriority, newKey);
	// imprimeHeap(alimentos);

	// //Luego recibe un alimento (albondigas)
	// newPriority = 8; newKey = "Albondigas";
	// alimentos.insertOrUpdate(newPriority, newKey);
	// imprimeHeap(alimentos);

	// //Luego recibe un alimento (Pescado)
	// newPriority = 8; newKey = "Pescado";
	// alimentos.insertOrUpdate(newPriority, newKey);
	// imprimeHeap(alimentos);

	// //Luego pide imprimir el de mayor prioridad(DeberC-a ser pescado)
	// if(alimentos.heapSize == 0){
	//     cout << "-1\n";
	// } else{
	//     pair<int, string> alimentoMayor = alimentos.top();
	//     cout << "\n" << alimentoMayor.second << " " << alimentoMayor.first << "\n";
	// }

	// //Luego actualizamos el valor de pescado a 7 y por tanto el que estC! a la cabeza es albondigas
	// newPriority = 7; newKey = "Pescado";
	// alimentos.insertOrUpdate(newPriority, newKey);
	// imprimeHeap(alimentos);

	// //Quitamos el de mayor prioridad (albondigas)
	// cout << "\nQuitamos el de mayor prioridad";
	// alimentos.pop();
	// imprimeHeap(alimentos);

	// //Quitamos pescado
	// cout << "\nquitamos pescado\n";
	// eraseAliment = "Pescado";
	// alimentos.erase(eraseAliment);
	// imprimeHeap(alimentos);

	// //Imprimimos alimento mayor
	// alimentoMayor = alimentos.top();
	// cout << "\nEl alimento mayor es\n";
	// cout << alimentoMayor.second << " " << alimentoMayor.first << "\n";

	// //Quitamos flan  (no pasa nada)
	// cout << "quitamos Flan\n";
	// eraseAliment = "Flan";
	// alimentos.erase(eraseAliment);
	// imprimeHeap(alimentos);

	// //Imprimimos alimento mayor
	// alimentoMayor = alimentos.top();
	// cout << "El alimento mayor es\n";
	// cout << alimentoMayor.second << " " << alimentoMayor.first << "\n";

	// //Quitamos pato
	// cout << "quitamos pato\n";
	// eraseAliment = "Pato";
	// alimentos.erase(eraseAliment);

	// //como ya no hay alimentos debe imprimir menos 1
	// imprimeHeap(alimentos);
	for (int i = 0; i < OP_size; i++)
	{
		cin >> OP;
		if (OP == "P") {
			if(alimentos.heapSize == 0) {
				cout << "-1\n";
			} else {
				pair<int, string> alimentoMayor = alimentos.top();
				cout << alimentoMayor.second << " " << alimentoMayor.first << "\n";
			}

		} else if(OP == "IU") {
			int newPriority;
			string newKey;
			cin >> newKey >> newPriority;
			alimentos.insertOrUpdate(newPriority, newKey);
		} else if(OP == "DL") {
			alimentos.pop();
		} else if(OP == "D") {
			string eraseAliment;
			cin >> eraseAliment;
			alimentos.erase(eraseAliment);
		}
	}
	return 0;
}