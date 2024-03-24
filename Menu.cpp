#include "Menu.h"
#include "Pops.h"
#include "Symetriques.h"

#include <Imagine/Graphics.h>
using namespace Imagine;

void display(int x, int y, const std::string& name) {
    int w, h;
    byte* RGBA;
    loadAlphaColorImage(name,RGBA,w,h);
    putAlphaColorImage(x,y,RGBA,w,h);
    delete[] RGBA;
}

void displayInfosBouton(int w) {
    int offset = 8;
    display(w - offset - 66, offset, srcPath("infos.png"));
}

bool developInfos(int w, int h, int dh, int x, int y) {
    if (dist({x,y},{w-41,41}) < 27) {
        blueScreen(w,h+dh);
        displayInfosBouton(w);
        return true;
    }
    return false;
}

void displayMenu(int w) {
    setBackGround(Color(22, 155, 227)); // background_blue
    std::vector<std::string> picsListe = {srcPath("img1.png"), srcPath("img2.png"), srcPath("img0.png"), srcPath("img0.png")};
    std::vector<Point> coordsListe = {{120, 50}, {395, 50}, {120, 200}, {395, 200}};
    for (int i=0; i<4; i++) {
        display(coordsListe[i].x, coordsListe[i].y, picsListe[i]);
    }
    displayInfosBouton(w);
}

int getIndex(int x, int y) {
    if ((x>143 && x<382) && (y>65 && y<160)) {
        return 0;
    } else if ((x>420 && x<655) && (y>65 && y<160)) {
        return 1;
    } else if ((x>143 && x<382) && (y>215 && y<310)) {
        return 2;
    } else if ((x>420 && x<655) && (y>215 && y<310)) {
        return 3;
    } else {
        return -1;
    }
}

int updatePassage(int w, int h, int dh, int index) {
    if (index==-1){
        displayMenu(w);
        std::cout << "  index=-1" << std::endl;
        return -1;
    }

    // Initialisation
    std::vector<std::string> picsPassageListe = {srcPath("passage0.png"), srcPath("passage1.png"), srcPath("passage2.png"), srcPath("passage3.png")};
    std::vector<Point> coordsListe = {{120, 50}, {395, 50}, {120, 200}, {395, 200}};

    // Première obtention de clic
    display(coordsListe[index].x, coordsListe[index].y, picsPassageListe[0]);
    int x,y;
    getMouse(x,y);

    if (!developInfos(w,h,dh,x,y)) {
        // Calcul de l'abscisse et l'ordonnée relatives
        int x_ = x-coordsListe[index].x;
        int y_ = y-coordsListe[index].y;

        // Renvoi des resultats & afichage
        if (y_>17 && y<160) {
            if (x_>23 && x_<100) {
                display(coordsListe[index].x, coordsListe[index].y, picsPassageListe[1]);
                return 0;
            } else if (x_>107 && x_<182) {
                display(coordsListe[index].x, coordsListe[index].y, picsPassageListe[2]);
                return 1;
            } else if (x_>190 && x_<265) {
                display(coordsListe[index].x, coordsListe[index].y, picsPassageListe[3]);
                return 2;
            }
        }

        displayMenu(w);
        return -1;
    } else {
        return -1;
    }
}
