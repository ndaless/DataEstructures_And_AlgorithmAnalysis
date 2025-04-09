// Let's go to implementation now. Once again we will use complex numbers to keep linear functions.

# include <bits/stdc++.h>
# include <complex>

typedef long long ftype;
typedef std::complex<ftype> point;
#define x real
#define y imag

// esta funcion, creo que es como una composicion de funciones, pues la usa para evaluar b en la funcion f_a
ftype dot(point a, point b) {
    return (conj(a) * b).x();
}

// creo que esta funcion esta evaluando la funcion (lineal) f_a en el punto x, pone coordeanda Y=1 pq esa no se usa, me thinks
ftype f(point a,  ftype x) {
    return dot(a, {x, 1});
}

// We will keep functions in the array line and use binary indexing of the segment tree. 
// If you want to use it on large numbers or doubles, you should use a dynamic segment tree. 
// The segment tree should be initialized with default values, e.g. with lines  0x + \infty.

const int maxn = 2e5; // max valor de la recta o total de funciones a insertar?

point line[4 * maxn]; // arreglo de st

void add_line(point nw, int v = 1, int l = 0, int r = maxn) {
    //       (idx de fun, nd del st, l_nd, r_nd)
    int m = (l + r) / 2;
    bool lef = f(nw, l) < f(line[v], l);
    bool mid = f(nw, m) < f(line[v], m);
    if(mid) {                                   // aqui dice q si gana en la mitad, entonces gana en todo el segmento  
        swap(line[v], nw);                      // y despues trata de corregir el segmento dnd se cruzan
    }
    if(r - l == 1) {                            // si ya no podemos partir el segmento, regresamos, se hizo lo que se debio de hacer (?
        return;
    } else if(lef != mid) {                     // aqui es dnd se elije dnd se va a insertar 
        add_line(nw, 2 * v, l, m);              // recursivamente la nueva función (ie, dnd se cruzan)
    } else {
        add_line(nw, 2 * v + 1, m, r);
    }
}

// Now to get the minimum in some point x we simply choose the minimum value along the path to the point.

ftype get(int x, int v = 1, int l = 0, int r = maxn) {
    //   (punto a responder, nd en st, l_nd, r_nd  )
    int m = (l + r) / 2;
    if(r - l == 1) {
        return f(line[v], x);
    } else if(x < m) {                                      // tratamos de encontrar los nodos que contengan al punto
        return min(f(line[v], x), get(x, 2 * v, l, m));     // y nos quedamos con el minimo de las funciones evaluadas en ese punto
    } else {
        return min(f(line[v], x), get(x, 2 * v + 1, m, r));
    }
}

// okay, le creo que en general funciona ese algoritmo
// teorias de cosas que podrían fallar:
// - funciones que nunca se cruzan
// - funciones que se intersecan en alguna mitad (posible mejor teoria) ps si se intersecan en la mitad, puede que left y mid sean iguales cuando no, or slt
// - tratar de insertar una funcion que ya esta (aunque esto creo q no se puede hacer)