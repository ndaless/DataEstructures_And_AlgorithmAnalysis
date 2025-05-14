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

    int minIdx; // point pMin;
    vector<vec> vectors;

    fight(vector<point> &_P){
        P = _P;
        // pMin = _pMin;
        // como los resorteo?
        Psort = P;
        Psort.insert(Psort.end(), P.begin(), P.end());

        minIdx = getMinIdx();

        getVectors();
    }

    vec toVec(const point &a, const point &b){
        vec newVec = vec(b.x - a.x, b.y - a.y);
        return newVec;
    }

    void getVectors(){
        for(int i = 0; i < P.size(); i++){
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

    bool isInside(const point &p){
        ///???

        return false;
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

    // fight myFight(pol);

    // cout << myFight.minIdx << ' ' << myFight.P[myFight.minIdx].x << ',' << myFight.P[myFight.minIdx].y << endl;

    // myFight.printPoints();
    // myFight.printSortedPoints();
    // myFight.printVectors();

    return 0;
}

// Test Cases
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
