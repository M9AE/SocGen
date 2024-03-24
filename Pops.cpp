#include "Pops.h"
#include "Symetriques.h"

#include <Imagine/Graphics.h>
using namespace Imagine;


Color rouge_jeton = Color(196, 74, 141);
Color off_white = Color(220, 220, 220);




// ===========================================  POINT =========================================== //

double dist(Point p1, Point p2) {return sqrt(pow(p1.x-p2.x,2) + pow(p1.y-p2.y,2));}
double distance(Point p1, Pop p2) {return dist(p1, p2.point);}

double distMin(Point p, std::vector<Pop> listPoint) {
    double minDist = distance(p, listPoint[0]);
    for (int i=1; i<int(listPoint.size()); i++) {
        double dist = distance(p, listPoint[i]);
        if (dist < minDist) minDist = dist;
    }

    return minDist;
}

bool tooClose(Point p, std::vector<Pop> listPoint, int width, int height, double treshold) {
    return (distMin(p, listPoint) < treshold || listPoint.empty() || p.x<treshold || width-p.x<treshold || p.y<treshold || height-p.y<treshold);
}




// ===========================================  POP  =========================================== //

void Pop::display(int rayon) {
    fillCircle(point.x, point.y, rayon, off_white);
    if (clicked || is_in_list){fillCircle(point.x, point.y, (7*rayon)/9, rouge_jeton);}
}

void display(std::vector<Pop> popList, int rayon) {
    setBackGround(Color(22, 155, 227)); // background_blue
    for (int i=0; i<int(popList.size()); i++) {
        popList[i].display(rayon);
    }
}




// ===========================================  mAcHiNeRy  =========================================== //

void addNew(Point p, std::vector<Pop>& listPoint, bool check_display) {
    Pop pop;
    pop.initialize(p);
    if (check_display){pop.display(10);}
    listPoint.push_back(pop);
}

void listPointInitialize(std::vector<Pop>& listPoint, int N, int treshold, int w, int h, bool check_display) {
    Point p; Pop pop;
    addNew({rand()%w, rand()%h}, listPoint, check_display);
    for (int i=1; i<N; i++){
        p.initialize(rand()%w, rand()%h);
        int nb_while = 0;
        while (tooClose(p, listPoint, w, h, treshold)) {
            p.initialize(rand()%w, rand()%h);
            //if (nb_while%100 == 0 && nb_while!=0){std::cout << nb_while << std::endl;}
            nb_while++;
            if (nb_while>1000){return;}
        }
        addNew(p, listPoint, check_display);
    }
}

bool isIn(int val, std::vector<int>& selectedPops) {
    for (int i=0; i<int(selectedPops.size()); i++) {
        if (val == selectedPops[i]){return true;}
    }
    return false;
}

void initializeIntList(int n, int n_max, std::vector<int>& selectedPops) {
    if (n>n_max){return;}
    for (int i=0; i<n; i++) {
        int val = rand()%n_max;
        while (isIn(val, selectedPops)){
            val = rand()%n_max;
        }
        selectedPops.push_back(val);
    }
}




// =============================== JEU  =============================== //

int getClickedPop(std::vector<Pop> popList, int treshold) {
    // Récupération du clic
    Point clic;
    while (!getPositionAtClick(clic.x, clic.y)) {
        milliSleep(25);
    }

    // Recherche du pop cliqué
    for (int i=0; i<int(popList.size()); i++){
        if (distance(clic, popList[i]) < treshold){return i;}
    }
    return -1;
}

