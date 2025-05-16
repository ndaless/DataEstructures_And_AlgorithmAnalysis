#include <bits/stdc++.h>

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
};

struct vec{
    double x, y;
    vec(const double&_x, const double&_y) : x(_x), y(_y) {}
};

struct fight{
    vector<point> points;
    int N;
    point pivot;

    fight(vector<point> &_points){
        points = _points;
        N = points.size();

        // rearange the points, so the first one is the pivot
        sortPoints();
        pivot = points[0];

    }

    void sortPoints(){
        vector<point> points2;
        points2 = points;
        points2.insert(points2.end(), points.begin(), points.end());

        int pivIdx = getPivIdx(); // obtenemos el idx del pivote

        for(int i = 0; i < points.size(); i++){
            points[i] = points2[pivIdx + i];
        }
    }

    int getPivIdx(){
        point piv;
        int idx = 0;

        for(int i = 0; i < points.size(); i++){
            point p = points[i];
            // we keep the pivot as the smallest x and largest y
            if(p.y <= piv.y){
                if(p.y == piv.y && p.x < piv.x){
                    continue;
                } else {
                    piv = p;
                    idx = i;
                }
            }
        }

        return idx; // return pMin; // for getMinPoint()
    }

    vec toVec(const point &a, const point &b){
        vec newVec = vec(b.x - a.x, b.y - a.y);
        return newVec;
    }

    int crossProd(const vec &a, const vec &b){
        double x1 = a.x, x2 = b.x;
        double y1 = a.y, y2 = b.y;
        return x1*y2 - x2*y1;
    }

    int getBoundaryPoints(int leftIdx, const vec &bombVec){ // se cicla? y cuando?
        vec v1 = toVec(pivot, points[leftIdx]);
        vec v2 = toVec(pivot, points[leftIdx-1]);

        if(crossProd(v1, bombVec) == 0 || crossProd(v2, bombVec) == 0) // si la bomba cae en un punto del poligono
            return true;

        if(crossProd(v1, bombVec) < 0){ // si esta a la derecha del vector pivote
            if(crossProd(v2, bombVec) > 0){ // pero a la izquierda del anterior
                return leftIdx; // nos quedamos con ese vector
            }
            leftIdx = getBoundaryPoints(leftIdx - leftIdx/2, bombVec); // si no, buscamos uno mas cerca
        } else{ // si esta a la izquierda del vector pivote
            leftIdx = getBoundaryPoints(leftIdx + leftIdx/2, bombVec); // buscamos uno que este a la derecha
        }

        return leftIdx;
    }

    bool isInside(const point &bomb){
        vec bombVec = toVec(pivot, bomb); 
        if(bombVec.x == 0 && bombVec.y == 0) // si la bomba cae en el punto pivote
            return true;

        // case when the point is outside of the main angle
        vec fisrtVec = toVec(pivot, points[1]), lastVec = toVec(pivot, points[N-1]);
        if(crossProd(fisrtVec, bombVec) < 0 || crossProd(lastVec, bombVec) > 0)
            return false;

        // get the points corresponding to the vectors of the surrounding triangle
        int leftIdx = getBoundaryPoints(N-1, bombVec); // idx of the point in the poligon
        int rightIdx = leftIdx - 1;

        // chech if its inside the triangle
        point p1 = points[leftIdx], p2 = points[rightIdx];
        vec v1 = toVec(p1, p2), v2 = toVec(p1, bomb);
        if(crossProd(v1, v2) <= 0)
            return true;
        
        return false;
    }
        
    void printPoints(){
        for(const auto val : points){
            cout << "(" << val.x << ", " << val.y << ") ";
        }
        cout << endl;
    }

};

int main(){
    point p0(1, 2);
    point p1(0, 4);
    point p2(-1, 2);
    point p3(-1, -1);
    point p4(1, -1);

    vector<point> P = {p0, p1, p2, p3, p4}; // the poligon

    fight myFight(P);

    point b1(0, 1), b2(2, 3), b3(-2, 1), b4(0, 4), b5(1, -1), b6(-1/2, 3); // falta el punto que es uno de los del poligono 
    cout << myFight.isInside(b1) << endl; // 1, dentro completamente
    cout << myFight.isInside(b2) << endl; // 0, fuera completamente
    cout << myFight.isInside(b3) << endl; // 0, fuera completamente
    cout << myFight.isInside(b4) << endl; // 1, punto del poligono (p1)
    cout << myFight.isInside(b5) << endl; // 1, punto pivote
    cout << myFight.isInside(b6) << endl; // 1, punto en frontera

    return 0;
}

// 5 4 2
// 1 -1
// 1 2
// 0 4
// -1 2
// -1 -1
// -2 -1
// 1 -1
// 0 1
// 2 3