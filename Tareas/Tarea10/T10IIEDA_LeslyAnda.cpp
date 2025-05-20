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

    // int count;


    fight(vector<point> &_points){
        points = _points;
        N = points.size();

        // rearange the points, so the first one is the pivot
        sortPoints();
        pivot = points[0];
        // count = 0;
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
        point piv = points[0];
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

        return idx;
    }

    vec toVec(const point &a, const point &b){
        vec newVec = vec(b.x - a.x, b.y - a.y);
        return newVec;
    }

    double crossProd(const vec &a, const vec &b){
        double x1 = a.x, x2 = b.x;
        double y1 = a.y, y2 = b.y;
        return x1*y2 - x2*y1;
    }

    double dist(const point &a, const point &b){
        return sqrt(pow(a.x-b.x, 2) + pow(a.y - b.y, 2));
    }
    // int getBoundaryPoints(int leftIdx, const vec &bombVec){ // se cicla? y cuando?
    //     // cout << pivot.x << ',' << pivot.y << endl;
    //     // count ++;
    //     // if(count == 10) return 0;
    //     vec v1 = toVec(pivot, points[leftIdx]); // cout << points[leftIdx].x << ',' << points[leftIdx].y << endl;
    //     vec v2 = toVec(pivot, points[leftIdx-1]); // cout << points[leftIdx-1].x << ',' << points[leftIdx-1].y << endl;

    //     if(crossProd(v1, bombVec) == 0 || crossProd(v2, bombVec) == 0) // si la bomba cae en un punto del poligono
    //         return true;

    //     if(crossProd(v1, bombVec) < 0){ // si esta a la derecha del vector pivote
    //         if(crossProd(v2, bombVec) > 0){ // pero a la izquierda del anterior
    //             return leftIdx; // nos quedamos con ese vector
    //         }
    //         leftIdx = getBoundaryPoints(leftIdx - leftIdx/2, bombVec); // si no, buscamos uno mas cerca
    //     } else{ // si esta a la izquierda del vector pivote
    //         leftIdx = getBoundaryPoints(leftIdx + leftIdx/2, bombVec); // buscamos uno que este a la derecha
    //     }

    //     return leftIdx;
    // }

    int getBoundaryPoints(int leftIdx, int rightIdx, const vec &bombVec){ // se cicla? y cuando?

        // caso base
        if(leftIdx - rightIdx == 1)
            return leftIdx;
        
        vec v1 = toVec(pivot, points[leftIdx]);
        vec v2 = toVec(pivot, points[rightIdx]); 

        if(crossProd(v1, bombVec) == 0 || crossProd(v2, bombVec) == 0){ // si la bomba cae en un punto dado del poligono
            return true;
        }

        int mid = (leftIdx + rightIdx)/2;
        vec vMid = toVec(pivot, points[mid]);

        if(crossProd(vMid, bombVec) < 0){
            leftIdx = getBoundaryPoints(mid, rightIdx, bombVec);
        } else{
            leftIdx = getBoundaryPoints(leftIdx, mid, bombVec);
        }

        return leftIdx;
    }

    bool isInside(const point &bomb){
        vec bombVec = toVec(pivot, bomb); 
        if(bombVec.x == 0 && bombVec.y == 0) // si la bomba cae en el punto pivote
            return true;

        // case when the point is outside of the main angle
        vec fisrtVec = toVec(pivot, points[1]), lastVec = toVec(pivot, points[N-1]);
        if(crossProd(fisrtVec, bombVec) <= 0 || crossProd(lastVec, bombVec) >= 0)
            return false;

        // if its in the main angle
        if(crossProd(fisrtVec, bombVec) == 0 || crossProd(lastVec, bombVec) == 0){
            double dist1 = dist(pivot, points[1]), dist2 = dist(pivot, points[N-1]);
            double distBomb = dist(pivot, bomb);
            if( dist1 - distBomb > -EPS &&  dist2 - distBomb > -EPS){ // esta dentro del poligono
                return true;
            }
            return false; // esta fuera
        }

        // get the points corresponding to the vectors of the surrounding triangle
        int leftIdx = getBoundaryPoints(N-1, 1, bombVec); // idx of the point in the poligon
        int rightIdx = leftIdx - 1;

        // chech if its inside the triangle
        point p1 = points[leftIdx], p2 = points[rightIdx];
        vec v1 = toVec(p1, p2), v2 = toVec(p1, bomb);

        // si el punto esta en una arista del poligono o adentro
        if(crossProd(v1, v2) <= 0){
            return true;
        }
        
        return false;
    }

    void destroy(int M, int K){
        double x, y;
        int goodExp = 0; bool destroyed = false;
        if(K == 0)
            destroyed = true;

        for(int m = 0; m < M; m++){
            cin >> x >> y;
            point bomb(x, y);

            if(isInside(bomb)){
                // cout << "bomba " <<"(" << bomb.x << ", " << bomb.y << ") " << " en el blanco" << endl;
                goodExp++;
                if(goodExp == K){
                    destroyed = true;
                }
            }
        }
        if(destroyed)
            cout << "YES" << endl;
        else 
            cout << "NO" << endl;
    }

    void printPoints(){
        for(const auto val : points){
            cout << "(" << val.x << ", " << val.y << ") ";
        }
        cout << endl;
    }

    void printPoint(const point p){
        cout << "(" << p.x << ", " << p.y << ") ";
    }

    void printVec(const vec v){
        cout << "(" << v.x << ", " << v.y << ") ";
    }

};

int main(){
    int N, M, K; cin >> N >> M >> K;

    vector<point> P;
    int x, y;

    for(int i = 0; i < N; i++){
        // we save the point
        cin >> x >> y;
        point newPoint(x, y);
        P.push_back(newPoint);
    }

    fight myFight(P);

    myFight.destroy(M, K);
    // cout << "destuido?" << endl;

    return 0;
}

// int main(){
//     point p0(2, 1);
//     point p1(0, 3);
//     point p2(-2, 2);
//     point p3(-4, 0);
//     point p4(-3, -2);
//     point p5(0, -3);
//     point p6(2, -1);

//     vector<point> P = {p0, p1, p2, p3, p4, p5, p6}; // the poligon

//     fight myFight(P);

//     point b1(-4, 3); //b2(2, 3), b3(-2, 1), b4(0, 4), b5(1, -1), b6(-1/2, 3); 
//     cout << myFight.isInside(b1) << endl; // 1, dentro completamente
//     // cout << myFight.isInside(b2) << endl; // 0, fuera completamente
//     // cout << myFight.isInside(b3) << endl; // 0, fuera completamente
//     // cout << myFight.isInside(b4) << endl; // 1, punto del poligono (p1)
//     // cout << myFight.isInside(b5) << endl; // 1, punto pivote
//     // cout << myFight.isInside(b6) << endl; // 1, punto en frontera

//     return 0;
// }

// Case 1
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

// Case 2
// 7 7 5
// 2 1
// 0 3
// -2 2
// -4 0
// -3 -2
// 0 -3
// 2 -1
// -4 3
// -2 5
// 0 1
// -2 1
// -2 -2 
// 2 -2
// 5 4

// case 3
// 7 7 4
// 2 1
// 0 3
// -2 2
// -4 0
// -3 -2
// 0 -3
// 2 -1
// -4 3
// -2 5
// 0 1
// -2 1
// -2 -2 
// 2 -2
// 5 4

// Case 4
// 7 6 6
// 3 2
// 0 2
// -4 2
// -4 -2
// -2 -2
// 3 -2
// 3 0
// 0 0
// 3 -2
// 0 2
// -2 2
// -6 -2
// -4 1
