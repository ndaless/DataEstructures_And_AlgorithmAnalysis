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

    void jaula(int left, int right){
        
    }

    bool isInside(const point &bomb){

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