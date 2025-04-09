// Tarea 4 - EDAII

#include <iostream>
#include <vector>
#include <complex>
#include <algorithm>

typedef long long ftype;
typedef std::complex<ftype> point;
#define x real
#define y imag

class LiChaoTree {
public:
    //static const int maxn = 2e5;
    static const int maxn = 4; 
    
    std::vector <point> line;
    
    LiChaoTree(){
        line.assign(4 * maxn, {0, 10});
    }
    
    ftype dot(point a, point b) {
        return (std::conj(a) * b).x();
    }

    ftype f(point a, ftype x) {
        return dot(a, {x, 1});
    }
    
void add_line(point nw, int v = 1, int l = 0, int r = maxn) {
    //       (idx de fun, nd del st, l_nd, r_nd)
    // std::cout << "entrando a ad_line en nd " << v << " " << line[v] << std::endl;
    
    int m = (l + r) / 2; // std::cout << m;
    bool lef = f(nw, l) < f(line[v], l); //std::cout << lef;
    //bool right = f(nw, l) < f(line[v], l);
    // std::cout << f(nw, m) << " " << f(line[v], m) << std::endl;
    bool mid = f(nw, m) < f(line[v], m); // std::cout << mid << std::endl; // aqui no se esta prendiendo cuando debe, manejar especial el caso dnd se cruzan en m
    if(mid) {                                   // aqui dice q si gana en la mitad, entonces gana en todo el segmento  
        // std::cout << "intercambiando "<< line[v] << " con " << nw << std::endl;
    
        std::swap(line[v], nw);                      // y despues trata de corregir el segmento dnd se cruzan
        
    }
    if(r - l == 1) {
        // std::cout << "saliendo de add_line" << std::endl;   // si ya no podemos partir el segmento, regresamos, se hizo lo que se debio de hacer (?
        return;
    } else if(lef != mid) {                     // aqui es dnd se elije dnd se va a insertar 
        add_line(nw, 2 * v, l, m);              // recursivamente la nueva función (ie, dnd se cruzan)
    } else {
        add_line(nw, 2 * v + 1, m, r);
    }

}

// Now to get the minimum in some point x we simply choose the minimum value along the path to the point.
// Regresar el índice en lugar de la evaluacion 

int get2(int x, int v, int l, int r) {
    //   (punto a responder, nd en st, l_nd, r_nd  )
    // std::cout << "entrando a get" << std::endl;
    int nv;
    int m = (l + r) / 2;
    if(r - l == 1) {
        // std::cout << "saliendo de get" << std::endl;
        // return f(line[v], x);
        return v;
    } else if(x < m) {                                                  // tratamos de encontrar los nodos que contengan al punto
        nv = get2(x, 2 * v, l, m);
        return (f(line[v], x) < f(line[nv], x) ?  v :  nv);
        // return std::min(f(line[v], x), f(get(x, 2 * v, l, m), x));     // y nos quedamos con el minimo de las funciones evaluadas en ese punto
    } else {
        nv = get2(x, 2 * v + 1, m, r);
        return (f(line[v], x) < f(line[nv], x) ? v : nv);
        //return std::min(f(line[v], x), f(get(x, 2 * v + 1, m, r), x));
    }
}

point get(int x){
    return line[get2(x, 1, 0, maxn)];
}

void printLine(){
    for(const auto node : line){
        std::cout << node;
    }
    std::cout << std::endl;
}

};

int main() {
    
    LiChaoTree tree;

    // tree.printLine();
    tree.add_line({0, 3});
    tree.add_line({1, 0});
    tree.add_line({0, 1});
    tree.add_line({0, 2});
    // tree.printLine();
    
    std::cout << tree.get(2) << " " << tree.get(0) << " " << tree.get(3) << std::endl; 
    return 0;
}
