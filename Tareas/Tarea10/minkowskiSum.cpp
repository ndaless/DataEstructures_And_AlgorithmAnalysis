#include <bits/stdc++.h>

using namespace std;

struct pt{
    long long x, y;
    pt(long long _x, long long _y) : x(_x), y(_y){}
    pt operator + (const pt & p) const {
        return pt{x + p.x, y + p.y};
    }
    pt operator - (const pt & p) const {
        return pt{x - p.x, y - p.y};
    }
    long long cross(const pt & p) const {
        return x * p.y - y * p.x;
    }
};

void reorder_polygon(vector<pt> & P){
    size_t pos = 0;
    for(size_t i = 1; i < P.size(); i++){
        if(P[i].y < P[pos].y || (P[i].y == P[pos].y && P[i].x < P[pos].x))
            pos = i;
    }
    rotate(P.begin(), P.begin() + pos, P.end());
}

vector<pt> minkowski(vector<pt> P, vector<pt> Q){
    // the first vertex must be the lowest
    reorder_polygon(P);
    reorder_polygon(Q);
    // we must ensure cyclic indexing
    P.push_back(P[0]);
    P.push_back(P[1]);
    Q.push_back(Q[0]);
    Q.push_back(Q[1]);
    // main part
    vector<pt> result;
    size_t i = 0, j = 0;
    while(i < P.size() - 2 || j < Q.size() - 2){
        result.push_back(P[i] + Q[j]);
        auto cross = (P[i + 1] - P[i]).cross(Q[j + 1] - Q[j]);
        if(cross >= 0 && i < P.size() - 2)
            ++i;
        if(cross <= 0 && j < Q.size() - 2)
            ++j;
    }
    return result;
}

void printPts(const vector<pt> points){
    for(const auto val : points){
        cout << "(" << val.x << ", " << val.y << ") ";
    }
    cout << endl;
}

int main(){
    // cout << "Caso 1: Triangulos" << endl; // (0, 0) (3, 0) (2, 2) (1, 3) (0, 2)
    // // puntos
    // pt p1(0,0), p2(2,0), p3(1,1);
    // pt q1(0,0), q2(1,0), q3(0,2);
    // // poligonos
    // vector<pt> P = {p1, p2, p3}; vector<pt> Q = {q1, q2, q3};
    // vector<pt> PQ = minkowski(P, Q);
    // // suma de minkowski
    // printPts(PQ);

    // cout << "Caso 2: Rectángulos" << endl; // (1,1) (3,1) (3,3) (1,3)
    // // puntos
    // pt p1(0,0), p2(1,0), p3(1,1), p4(0,1);
    // pt q1(1,1), q2(2,1), q3(2,2), q4(1,2);
    // // poligonos
    // vector<pt> P = {p1, p2, p3, p4}; vector<pt> Q = {q1, q2, q3, q4};
    // vector<pt> PQ = minkowski(P, Q);
    // // suma de minkowski
    // printPts(PQ);

    // cout << "Caso 3: Poligono" << endl; // (1,1) (9,1) (8,4) (5,7)
    // // puntos
    // pt p1(0,0), p2(5,0), p3(2,3);
    // pt q1(1,1), q2(4,1), q3(3,4);
    // // poligonos
    // vector<pt> P = {p1, p2, p3}; vector<pt> Q = {q1, q2, q3};
    // vector<pt> PQ = minkowski(P, Q);
    // // suma de minkowski
    // printPts(PQ);

    // cout << "Caso 4: Puntos" << endl; // (2,2)
    // // puntos
    // pt p1(0,0);
    // pt q1(2,2);
    // // poligonos
    // vector<pt> P = {p1}; vector<pt> Q = {q1};
    // vector<pt> PQ = minkowski(P, Q);
    // // suma de minkowski
    // printPts(PQ);

    // cout << "Caso 5: Poligono con lados colineales" << endl; // (1,1) (9,1) (5,5)
    // // puntos
    // pt p1(0,0), p2(4,0), p3(2,2);
    // pt q1(1,1), q2(5,1), q3(3,3);
    // // poligonos
    // vector<pt> P = {p1, p2, p3}; vector<pt> Q = {q1, q2, q3};
    // vector<pt> PQ = minkowski(P, Q);
    // // suma de minkowski
    // printPts(PQ);

    // cout << "Caso 6: Rectángulo + punto" << endl; // (1,1) (3,1) (3,2) (1,2)
    // // puntos
    // pt p1(0,0), p2(2,0), p3(2,1), p4(0,1);
    // pt q1(1,1);
    // // poligonos
    // vector<pt> P = {p1, p2, p3, p4}; vector<pt> Q = {q1};
    // vector<pt> PQ = minkowski(P, Q);
    // // suma de minkowski
    // printPts(PQ);

    cout << "Caso 7: Poligono + Triangulo" << endl; //
    // puntos
    pt p1(0,0), p2(2,-1), p3(3,0), p4(3,3), p5(2, 4), p6(0,3);
    pt q1(1,1), q2(3,-2), q3(4,0), q4(5,2), q5(3, 4), q6(1,3);
    // poligonos
    vector<pt> P = {p1, p2, p3, p4, p5, p6}; vector<pt> Q = {q1, q2, q3, q4, q5};
    vector<pt> PQ = minkowski(P, Q);
    // suma de minkowski
    printPts(PQ);

    // cout << "Caso 8: Line + Line" << endl; // (0, 0) (1, 0) (2, 0) (2, 1) (2, 2) (0, 2) 
    // // puntos
    // pt p1(0,0), p2(1,0), p3(2,0);
    // pt q1(0,0), q2(0,1), q3(0,2);
    // // poligonos
    // vector<pt> P = {p1, p2, p3}; vector<pt> Q = {q1, q2, q3};
    // vector<pt> PQ = minkowski(P, Q);
    // // suma de minkowski
    // printPts(PQ);

}

  