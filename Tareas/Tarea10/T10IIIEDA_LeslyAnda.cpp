#include <bits/stdc++.h>

using namespace std;

double EPS = 10e-9;
double INVALID = -1e9;

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
        // point sum(x+other.x, y+other.y);
        return point{x + other.x, y + other.y};
    }
};

// point midPoint(const point &a, const point &b){
//     point mid;
//     mid.x = (a.x + b.x) / 2.0;
//     mid.y = (a.y + b.y) / 2.0;
//     return mid;
// }

pair<point, point> moveSegment(const point& ini, const point& end, const double& d){ // no esta haciendo bien esto
    point new_ini, new_end;

    // calculamos la direccion del segmento
    double dx = end.x - ini.x;
    double dy = end.y - ini.y;

    // calculamos el vector normal (perpendicular a (dx, dy))
    double nx = -dy;
    double ny = dx;

    // normalizamos vector normal
    double mag = sqrt(nx*nx + ny*ny);
    nx /= mag;
    ny /= mag;

    // desplazamos puntos en dirección del vector normal
    new_ini.x = ini.x + d*nx;
    new_ini.y = ini.y + d*ny;

    new_end.x = end.x + d*nx;
    new_end.y = end.y + d*ny;

    return make_pair(new_ini, new_end);
}

point getIntersection(const point& ini_s1, const point& end_s1, const point& ini_s2, const point end_s2){
    point intersection(INVALID, INVALID);

    // calculamos la dirección de los segmentos
    double dx1 = end_s1.x - ini_s1.x;
    double dy1 = end_s1.y - ini_s1.y;
    double dx2 = end_s2.x - ini_s2.x;
    double dy2 = end_s2.y - ini_s2.y;

    double det = dx1 * dy2 - dy1 * dx2;

    // caso: si los segmentos son paralelos
    if(fabs(det) < EPS)
        return intersection;
    
    double s = ((ini_s2.x - ini_s1.x) * dy2 - (ini_s2.y - ini_s1.y) * dx2) / det;
    double t = ((ini_s2.x - ini_s1.x) * dy1 - (ini_s2.y - ini_s1.y) * dx1) / det;

    // si el momento en el que los segmentos son iguales esta entre [0,1]
    if(s >= 0 && s <= 1 && t >= 0 && t <= 1){
        intersection.x = ini_s1.x + s * dx1;
        intersection.y = ini_s1.y + s * dy1;
        return intersection;
    }

    return intersection;
}

void printPoints(const vector<point> points){
    for(const auto val : points){
        cout << "(" << val.x << ", " << val.y << ") ";
    }
    cout << endl;
}

double area(const vector<point> &P){
    double result = 0.0, x1, y1, x2,y2;
    for (int i = 0; i < (int)P.size()-1; i++) {
        x1 = P[i].x; x2 =P[i+1].x;
        y1 = P[i].y; y2 =P[i+1].y;
        result += (x1 * y2-x2 * y1);
    }
    return fabs(result)/ 2.0;
}

void solve(const vector<point>& P, const double& d){
    vector<point> movedP;

    for(int i = 0; i < P.size()-1; i++){
        pair<point, point> movedSegment = moveSegment(P[i], P[i+1], d);
        point np1 = movedSegment.first;
        point np2 = movedSegment.second;
        movedP.push_back(np1); movedP.push_back(np2);
    } movedP.push_back(movedP[0]); movedP.push_back(movedP[1]);

    // printPoints(movedP);

    vector<point> newP;
    for(int i = 0; i < movedP.size()-3; i+=2){
        point np = getIntersection(movedP[i], movedP[i+1], movedP[i+2], movedP[i+3]);
        if(np.x != INVALID){
            newP.push_back(np);
        } else{
            cout << "ERROR_1" << endl;
        } 
    }   
    if(!newP.empty()){
        // printPoints(newP);
    } else{
        cout << "ERROR_2" << endl;
    }

    // printPoints(newP);

    cout <<  std::fixed << std::setprecision(3) << area(newP) << endl;
}

int main(){
    double d; int n; cin >> d >> n;
    while(d != 0 || n != 0){
        // caso de una linea o un punto
        if(n < 3){
            cin >> d >> n;
            continue;
        }

        vector<point> P;
        for(int i = 0; i < n; i++){
            double x, y; cin >> x >> y;
            point p(x, y);
            P.push_back(p);
        }

        // porque están en sentido horario
        reverse(P.begin(), P.end()); 
        P.push_back(P[0]);

        // movemos segmentos y calculamos area
        solve(P, d);

        cin >> d >> n;
    }

    return 0;
} // 2 4 0 0 0 5 5 5 5 0
