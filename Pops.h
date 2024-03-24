#ifndef POPS_H
#define POPS_H

#include <Imagine/Graphics.h>
using namespace Imagine;


struct Point {
    int x,y;
// Fonctions
    void initialize(int _x_, int _y_) {
        x = _x_;
        y = _y_;
    }
};


struct Pop {
    Point point;
    bool is_in_list; int list_index;
    bool clicked;
// Function
    void initialize(Point _point_) {
        point = _point_;
        is_in_list = false;
        clicked = false;
    }
    void display(int rayon);
};

double dist(Point p1, Point p2);
double distance(Point p1, Pop p2);
double distMin(Point p, std::vector<Pop> listPoint);
bool tooClose(Point p, std::vector<Pop> listPoint, int height, int width, double treshold);
void addNew(Point p, std::vector<Pop>& listPoint, bool check_display);
void listPointInitialize(std::vector<Pop>& listPoint, int N, int treshold, int w, int h, bool check_display);

bool isIn(int val, std::vector<int>& selectedPops);
void initializeIntList(int n, int n_max, std::vector<int>& selectedPops);
void display(std::vector<Pop> popList, int rayon);

int getClickedPop(std::vector<Pop> popList, int treshold);

#endif // POPS_H
