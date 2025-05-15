#include <bits/stdc++.h>

using namespace std;

double EPS = 10e-9;

struct point_i{ // integer point
    int x, y;
    point_i() {x = y = 0;}
    point_i(int _x, int _y) : x(_x), y(_y) {}
};

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
public:
    vector<point> P; // original poligon
    vector<point> Psort; // poligon for new order

    int minIdx; point pMin;
    vector<vec> vectors;

    fight(vector<point> &_P){
        P = _P;
        // pMin = _pMin;
        // como los resorteo?
        Psort = P;
        Psort.insert(Psort.end(), P.begin(), P.end());

        minIdx = getMinIdx();
        pMin = P[minIdx];

        getVectors();
    }

    vec toVec(const point &a, const point &b){
        vec newVec = vec(b.x - a.x, b.y - a.y);
        return newVec;
    }

    void getVectors(){
        for(int i = 1; i <= P.size(); i++){
            vectors.push_back(toVec(Psort[minIdx], Psort[minIdx + i]));
        }
    }

    int getMinIdx(){ // do we need this?
        point pMin;
        int idx = 0;

        for(int i = 0; i < P.size(); i++){
            point p = P[i];
            // we keep the pivot as the smallest x and largest y
            if(p.y <= pMin.y){
                if(p.y == pMin.y && p.x < pMin.x){
                    continue;
                } else {
                    pMin = p;
                    idx = i;
                }
            }
        }
        return idx; // return pMin; // for getMinPoint()
    }

    int crossProd(const vec &a, const vec &b){
        double x1 = a.x, x2 = b.x;
        double y1 = a.y, y2 = b.y;
        return x1*y2 - x2*y1;
    }

    // int findLastVector(int idxPoint, const vec &bombVec){ // siempre entro sabiendo q el punto esta dentro del angulo
    //     if(crossProd(vectors[idxPoint], bombVec) < 0){
    //         cout << "no funcionó para el vector " << idxPoint << ". Correspondiente al punto" << P[idxPoint].x << ',' << P[idxPoint].y << endl;
    //         idxPoint = findLastVector(idxPoint - idxPoint/2, bombVec);
    //     }
    //     else{
    //         if(crossProd(vectors[idxPoint + 1], bombVec) < 0)
    //             return idxPoint;
    //         idxPoint = findLastVector(idxPoint + idxPoint/2, bombVec);
    //     }
    //     return idxPoint;
    // }

    // si para cuando deberia? no se cicla en ningún momento?
    // siempre entro sabiendo q el punto esta dentro del main angulo
    int findLastVector(int pIdx, const vec &bombVec){ // idx del punto en el vector de puntos, vector de bomba respecto al punto pivote
        vec v1 = toVec(pMin, P[pIdx]);
        if(crossProd(v1, bombVec) < 0){
            cout << "no funcionó para el vector " << pIdx << ". Correspondiente al punto" << P[pIdx].x << ',' << P[pIdx].y << endl;
            pIdx = findLastVector((pIdx - pIdx/2) & P.size(), bombVec);
        }
        else{
            cout << "funcionó para el vector " << pIdx << ". Correspondiente al punto" << P[pIdx].x << ',' << P[pIdx].y << endl;
            vec v2 = toVec(pMin, P[pIdx+1]);
            if(crossProd(v2, bombVec) < 0)
                return pIdx;
            pIdx = findLastVector((pIdx + pIdx/2) % P.size(), bombVec);
        }
        return pIdx;
    }

    void printVec(vec v){
        cout << "(" << v.x << ", " << v.y << ") " << endl;
    }

    bool isInside(const point &bomb){
        // the point is outside the main angles (those from the starting point)
        // cout << "para ver si esta afuera derecha hago cp de: "; printVec(vectors[0]); printVec(toVec(pMin, bomb));  
        // cout << "y para ver si esta afuera izquierda hago cp de: "; printVec(vectors[vectors.size()-2]); printVec(toVec(pMin, bomb));  
        
        if(crossProd(vectors[0], toVec(pMin, bomb)) < 0 || crossProd(vectors[vectors.size()-2], toVec(pMin, bomb)) > 0)
            return false;

        // binary rearch the vectors
        int idx = findLastVector((minIdx + 1)  % P.size(), toVec(pMin, bomb)); // el 0 es el vector del punto pivote // no estoy buscando en los que estan antes del punto pivote
        point p1 = P[idx];
        point p2 = P[idx + 1];

        vec p1p2 = toVec(p1, p2);
        int cp = crossProd(p1p2, toVec(p1, bomb)); 

        if(cp > 0)
            return true;

        return false;
    }

public:
    void printPoints(){
        for(const auto val : P){
            cout << "(" << val.x << ", " << val.y << ") ";
        }
        cout << endl;
    }

    void printSortedPoints(){
        for(const auto val : Psort){
            cout << "(" << val.x << ", " << val.y << ") ";
        }
        cout << endl;
    }
    
    void printVectors(){
        for(const auto val : vectors){
            cout << "(" << val.x << ", " << val.y << ") ";
        }
        cout << endl;
    }

};

int main(){
    vector<point> pol;
    int N; cin >> N;

    int x, y;
    for(int i = 0; i < N; i++){
        // we save the point
        cin >> x >> y;
        point newPoint(x, y);
        pol.push_back(newPoint);
    }

    // queries
    fight myFight(pol);

    point bomb(0,1);

    vec v1 = myFight.toVec(pol[0], pol[1]);
    vec v2 = myFight.toVec(pol[0], bomb);

    int cp = myFight.crossProd(v1, v2);

    // cout << "crossProd((" << v1.x << ',' << v1.y << "), (" << v2.x << ',' << v2.y << ")) = " << cp << endl;

    myFight.printPoints();
    myFight.printSortedPoints();
    myFight.printVectors();

    // cout << myFight.minIdx << ' ' << myFight.P[myFight.minIdx].x << ',' << myFight.P[myFight.minIdx].y << '=' << myFight.pMin.x << ',' << myFight.pMin.y << endl;

    point bomb1(0,1);
    point bomb2(2,3);

    cout << "is inside: (0,1) - " << myFight.isInside(bomb1) << endl;
    cout << "is inside: (2,3) - " << myFight.isInside(bomb2) << endl;

    return 0;
}

// int main(){
//     vector<point> pol;
//     int N, M, K; cin >> N >> M >> K;

//     int x, y;
//     for(int i = 0; i < N; i++){
//         // we save the point
//         cin >> x >> y;
//         point newPoint(x, y);
//         pol.push_back(newPoint);
//     }

//     // queries
//     fight myFight(pol);

//     int goodExp = 0; int m = 0;

//     while(m < M){
//         cin >> x >> y;
//         point bomb(x, y);
//         if(myFight.isInside(bomb)){
//             goodExp++;
//             if(goodExp == K){
//                 cout << "YES" << endl;
//             }
//         }
//         m++;
//     }

//     cout << "NO" << endl;
//     // cout << myFight.minIdx << ' ' << myFight.P[myFight.minIdx].x << ',' << myFight.P[myFight.minIdx].y << endl;

//     // myFight.printPoints();
//     // myFight.printSortedPoints();
//     // myFight.printVectors();

//     return 0;
// }

// Test Cases
// 5 4 2
// 1 2
// 0 4
// -1 2
// -1 -1
// 1 -1 
// -2 -1
// 1 -1
// 0 1
// 2 3
