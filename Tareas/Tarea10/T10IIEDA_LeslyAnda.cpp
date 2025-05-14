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

struct fight(){
    vector<point> P; // original poligon
    vector<point> Psort; // poligon for new order

    point pMin; int minIdx;
    vector<vec> vectors;

    fight(vector<point> &_P, point &_pMin){
        P = _P;
        pMin = _pMin;
        // como los resorteo?
        Psort = P;
        Psort.insert(Psort.end(), P.begin(), P.end());

        minIdx = getMinIdx();
    }

    toVec(const point &a, const point &b){
        return vec(b.x - a.x, b.y - a.y);
    }

    void getVectors(){
        for(int i = 0; i < P.size(); i++){

        }
    }

    int getMinIdx(){
        point pMin;
        int idx = 0;

        for(int i = 0; i < P.size(); i++){
            point p = P[i];
            // we keep the pivot as the smallest x and largest y
            if(p.x <= pMin.x){
                if(p.x == pMin.x && p.y < pMin.y){
                    continue;
                } else {
                    pMin = newPoint;
                    idx = i;
                }
            }
        }
        return idx; // return pMin; // for getMinPoint()
    }


}

int main(){

    vector<point> P;
    int N; cin >> N;

    int x, y;
    for(int i = 0; i < N; i++){
        // we save the point
        cin >> x >> y:
        point newPoint(x, y);
        P.push_back(newPoint);
    }


    return 0;
}