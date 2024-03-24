// This project has as purpose to train the people to the games proposed for the Société Générale recruitment.
// It has as goal to spread qualifications for these tests that the author estimates non-representative.

#include <cstdlib> // Pour srand() et rand()
#include <ctime>   // Pour time()
#include <chrono>
#include <iostream>
#include <random>

#include "Pops.h"
#include "Menu.h"
#include "Symetriques.h"

#include <Imagine/Graphics.h>
using namespace Imagine;

const int N = 35;
const int w = 800, h = 300, dh=80;
const int nb_rounds_[4][3] = {{2, 5, 10}, {2, 4, 6}, {2, 4, 6}, {2, 4, 6}};

int main() {
    // ==================  INITIALISATION  ================== //
    srand(time(0)); // Initialise le générateur de nombres aléatoires
    enableMouseTracking(true);
    openWindow(w,h+dh); // Fenêtre graphique
    blueScreen(w,h); // background_blue

    while (true) {
        // =======================  MENU  ======================= //
        int x_clic, y_clic, index, zone=-1;
        displayMenu(w);

        while (zone == -1) {
            getMouse(x_clic, y_clic);
            index = getIndex(x_clic,y_clic);
            std::cout << "  index : " << index << std::endl;

            if (!developInfos(w,h,dh,x_clic,y_clic)) {
                zone = updatePassage(w, h, dh, index);
                std::cout << "  zone : " << zone << std::endl;
            }
        }

        // ===================  OBJETS DE JEU  ==================== //
        const int nb_rounds = nb_rounds_[index][zone];

        std::vector<Pop> popList; // Liste des Pops cliquables
        listPointInitialize(popList, N, 38, w, h, false);

        std::vector<int> selectedPops;
        initializeIntList(nb_rounds, int(popList.size()), selectedPops);

        // =======================  JEUX  ======================== //
        if (index == 0) {  //  JEU DES POPS SIMPLES
            simplePopsGame(popList, selectedPops, w, h, dh, nb_rounds);
        }

        if (index == 1) {  //  JEU DES SYMETRIQUES
            const int N1=10, N2=5;
            const double p=0.5, p2=0.5;
            JeuDesSymetriques(popList, selectedPops, w, h, dh, N1, N2, p, p2, nb_rounds);
        }

        if (index == 2) {

        }

        // =======================  FIN  ======================== //
        blueScreen(w,h); // background_blue
    }

    endGraphics();
    return 0;
}
