#include<bits/stdc++.h>

using namespace std;

double EPS = 10e-9;

struct point{ // general point
    double x, y;
    point() {x = y = 0.0;}
    // default constructor
    point(double _x, double _y) : x(_x), y(_y) {}
    // copy constructor (for making a point from a point?)
    point(const point &p) : x(p.x), y(p.y) {}

    bool operator == (const point &other) const {
        return ((fabs(x - other.x) < EPS) && (fabs(y - other.y) < EPS));
    }

    point operator + (const point &other) const {
        point sum(x+other.x, y+other.y);
        return sum;
    }
};

struct vec{
    double x, y;
    vec(const double&_x, const double&_y) : x(_x), y(_y) {}
};

int getPivIdx(const vector<point> points){ // O(N)
    point piv = points[0];
    int idx = 0;

    for(int i = 0; i < points.size(); i++){
        point p = points[i];
        // we keep the pivot as the smallest x and largest y
        if(p.y < piv.y || (p.y == piv.y && p.x < piv.x)){
            piv = p;
            idx = i;
        }
    }

    return idx;
}

void sortPoints(vector<point> &points){ // O(N)
    vector<point> points2;
    points2 = points;
    points2.insert(points2.end(), points.begin(), points.end());

    int pivIdx = getPivIdx(points); // obtenemos el idx del pivote

    for(int i = 0; i < points.size(); i++){
        points[i] = points2[pivIdx + i];
    }
}

double polar(const point& a, const point &b){
    return atan2(b.y - a.y, b.x - a.x);
}

void printPoints(const vector<point> points){
    for(const auto val : points){
        cout << "(" << val.x << ", " << val.y << ") ";
    }
    cout << endl;
}

vector<point> minkowski(vector<point>& P, vector<point>& Q){
    int N = P.size(), M = Q.size();
    int i = 0, j = 0;

    // a) lowest at the begining
    sortPoints(P); sortPoints(Q);

    P.push_back(P[0]);
    Q.push_back(Q[0]);

    vector<point> PQ;
    while(i < N || j < M){ // O(M + N)
        // cout << i << ' ' << j << endl;

        // b) agregamos P[i]+Q[j] a la suma
        PQ.push_back(P[i] + Q[j]);
        
        // c) comparamos los angulos
        double angP = polar(P[i], P[(i + 1) % N]);
        double angQ = polar(Q[j], Q[(j + 1) % M]);
        
        // d) aumentamos indice segun los ángulos
        if (i == N) j++;
        else if (j == M) i++;
        else if(angP < angQ) i++;
        else if(angQ < angP) j++;
        else{i++; j++;}
    }
    return PQ;
}

int main(){

    cout << "Caso 1: Triangulos" << endl; // (0, 0) (3, 0) (2, 2) (1, 3) (0, 2)
    // puntos
    point p1(0,0), p2(2,0), p3(1,1);
    point q1(0,0), q2(1,0), q3(0,2);
    // poligonos
    vector<point> P = {p1, p2, p3}; vector<point> Q = {q1, q2, q3};
    vector<point> PQ = minkowski(P, Q);
    // suma de minkowski
    printPoints(PQ);

    // cout << "Caso 2: Rectángulos" << endl; // (1,1) (3,1) (3,3) (1,3) YES
    // // puntos
    // point p1(0,0), p2(1,0), p3(1,1), p4(0,1);
    // point q1(1,1), q2(2,1), q3(2,2), q4(1,2);
    // // poligonos
    // vector<point> P = {p1, p2, p3, p4}; vector<point> Q = {q1, q2, q3, q4};
    // vector<point> PQ = minkowski(P, Q);
    // // suma de minkowski
    // printPoints(PQ);

    // cout << "Caso 3: Poligono" << endl; // (1,1) (9,1) (8,4) (5,7)
    // // puntos
    // point p1(0,0), p2(5,0), p3(2,3);
    // point q1(1,1), q2(4,1), q3(3,4);
    // // poligonos
    // vector<point> P = {p1, p2, p3}; vector<point> Q = {q1, q2, q3};
    // vector<point> PQ = minkowski(P, Q);
    // // suma de minkowski
    // printPoints(PQ);

    // cout << "Caso 4: Puntos" << endl; // (2,2) YES
    // // puntos
    // point p1(0,0);
    // point q1(2,2);
    // // poligonos
    // vector<point> P = {p1}; vector<point> Q = {q1};
    // vector<point> PQ = minkowski(P, Q);
    // // suma de minkowski
    // printPoints(PQ);

    // cout << "Caso 5: Poligono con lados colineales" << endl; // (1,1) (9,1) (5,5) YES
    // // puntos
    // point p1(0,0), p2(4,0), p3(2,2);
    // point q1(1,1), q2(5,1), q3(3,3);
    // // poligonos
    // vector<point> P = {p1, p2, p3}; vector<point> Q = {q1, q2, q3};
    // vector<point> PQ = minkowski(P, Q);
    // // suma de minkowski
    // printPoints(PQ);

    // cout << "Caso 6: Rectángulo + punto" << endl; // (1,1) (3,1) (3,2) (1,2) YES
    // // puntos
    // point p1(0,0), p2(2,0), p3(2,1), p4(0,1);
    // point q1(1,1);
    // // poligonos
    // vector<point> P = {p1, p2, p3, p4}; vector<point> Q = {q1};
    // vector<point> PQ = minkowski(P, Q);
    // // suma de minkowski
    // printPoints(PQ);

    // cout << "Caso 7: Poligonos" << endl; // (5, -3) (6, -2) (7, 0) (8, 2) (8, 5) (5, 8) (3, 7) (1, 4) (1, 1) (3, -2) 
    // // puntos
    // point p1(0,0), p2(2,-1), p3(3,0), p4(3,3), p5(2, 4), p6(0,3);
    // point q1(1,1), q2(3,-2), q3(4,0), q4(5,2), q5(3, 4), q6(1,3);
    // // poligonos
    // vector<point> P = {p1, p2, p3, p4, p5, p6}; vector<point> Q = {q1, q2, q3, q4, q5};
    // vector<point> PQ = minkowski(P, Q);
    // // suma de minkowski
    // printPoints(PQ);

    // cout << "Caso 8: Line + Line" << endl; // (0, 0) (1, 0) (2, 0) (2, 1) (2, 2) (0, 2) 
    // // puntos
    // point p1(0,0), p2(1,0), p3(2,0);
    // point q1(0,0), q2(0,1), q3(0,2);
    // // poligonos
    // vector<point> P = {p1, p2, p3}; vector<point> Q = {q1, q2, q3};
    // vector<point> PQ = minkowski(P, Q);
    // // suma de minkowski
    // printPoints(PQ);

    return 0;
}

