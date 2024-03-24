#include <iostream>
#include <random>
#include <ctime>   // Pour time()
#include <chrono>

#include "Symetriques.h"
#include "Menu.h"

#include <Imagine/Graphics.h>
using namespace Imagine;




// =======================================================================================================//

void initializeDisplayBool(std::vector<std::vector<bool>>& displayBool, int N1, int N2, std::bernoulli_distribution& dis, std::mt19937& gen) {
    // Ajout des valeurs de display
    for (int n = 0; n < N2; n++) {
        std::vector<bool> displayListe;
        for (int i = 0; i < N1; i++) {displayListe.push_back(dis(gen));}
        displayBool.push_back(displayListe);
    }
}

void displayCout(std::vector<std::vector<bool>> displayBool) {
    for (const auto& liste : displayBool) {
        for (bool val : liste) {
            std::cout << val << " ";
        }
        std::cout << std::endl;
    }
}

void displayCenterLine(int w, int h) {
    drawLine(w/2, 0, w/2, h, RED);
}

void displayPiece(bool displayBool, int x, int y, int a) {
    if (displayBool) {
        fillRect(x-a, y-a, 2*a, 2*a, RED);
    } else {
        fillRect(x-a/2, y-a/2, a, a, RED);
    }
}




// =======================================================================================================//

void Symetrique::display(int w, int h, int a) {
    if (symetrique) {displaySym(w,h,a);} else {displayNonSym(w,h,a);}
}

void Symetrique::displaySym(int w, int h, int a) {
    displayCenterLine(w,h);

    for (int i=0; i<int(displayBool1.size()); i++) {
        std::vector<bool> displayListe = displayBool1[i];
        for (int j=0; j<int(displayListe.size()); j++) {
            displayPiece(displayListe[j], w/2-(2+3*i)*a, (3+3*j)*a, a);
            displayPiece(displayListe[j], w/2+(2+3*i)*a, (3+3*j)*a, a);
        }
    }
}

void Symetrique::displayNonSym(int w, int h, int a) {
    displayCenterLine(w,h);

    for (int i=0; i<int(displayBool1.size()); i++) {
        std::vector<bool> displayListe = displayBool1[i];
        for (int j=0; j<int(displayListe.size()); j++) {
            displayPiece(displayListe[j], w/2-(2+3*i)*a, (3+3*j)*a, a);
        }
    }

    for (int i=0; i<int(displayBool2.size()); i++) {
        std::vector<bool> displayListe = displayBool2[i];
        for (int j=0; j<int(displayListe.size()); j++) {
            displayPiece(displayListe[j], w/2+(2+3*i)*a, (3+3*j)*a, a);
        }
    }
}




// ================================================  BUTTON  ================================================ //

void displayButton(int w, int h) {
    display(w/2-120, h, srcPath("greenButton.png"));
    display(w/2+10, h, srcPath("redButton.png"));
}




// ================================================  Signs  ================================================= //

void blueScreen(int w, int h) {
    fillRect(0, 0, w, h, Color(22, 155, 227)); // background_blue
}



// =================================================  GAME  ================================================= //

void displayGame(int w, int h, int N1, int N2, std::bernoulli_distribution& dis, std::mt19937& gen, bool typeBool) {
    setBackGround(Color(22, 155, 227)); // background_blue

    std::vector<std::vector<bool>> refVector1, refVector2;
    initializeDisplayBool(refVector1, N1, N2, dis, gen);
    initializeDisplayBool(refVector2, N1, N2, dis, gen);

    Symetrique Game1(typeBool,N1,N2,refVector1,refVector2);
    Game1.display(w,h,9);
    displayButton(w,h);
}

bool getPositionAtClick(int& x, int& y) {
    Event ev;
    getEvent(0,ev); // No timeout
    switch (ev.type) {
    case EVT_BUT_ON:
        x = ev.pix.x();
        y = ev.pix.y();
        return true;
    default:
        return false;
    }
}

bool waitForClick(int& x, int& y, double delta_t) {
    // Initialisation temps
    double t0 = time(0);

    // Boucle principale pour tester la fonction
    while (time(0) - t0 < delta_t) {
        if (getPositionAtClick(x, y)) {return true;}
        milliSleep(20);
    }
    return false;
}

bool getAnswerButton(int x, int w) {
    return (x<w/2);
}

void displayTextAnswer(bool is_sym, bool check, bool answered) {
    if (answered) {
        if (check == is_sym){
            std::cout << "Tu as vu juste, ";
        }else{
            std::cout << "Eh non... ";
        }

        std::cout << "c'est ";

        if (is_sym){
            std::cout << "symetrique";
        }else{
            std::cout << "non-symetrique";
        }
    } else {
        std::cout << "Pas de réponse.";
    }
    std::cout << std::endl;
}

void displayAnswer(int w, int h, bool is_sym, bool check, bool answered) {
    displayTextAnswer(is_sym, check, answered);
    if (answered) {
        if (check == is_sym){
            display((w-125)/2, (h-125)/2, srcPath("t.png"));
        }else{
            display((w-125)/2, (h-125)/2, srcPath("t.png"));
        }
    }
    milliSleep(300);
    blueScreen(w,h);
    milliSleep(300);
}

bool getAnswerPops(std::vector<Pop>& popList, std::vector<int> selectedPops, int nb_rounds) {
    std::vector<int> answeredPops;
    for (int k=0; k<nb_rounds; k++){
        int indexClickedPop = getClickedPop(popList, 15);
        answeredPops.push_back(indexClickedPop);
        popList[indexClickedPop].is_in_list = true;
        display(popList, 13);
    }
    return (answeredPops == selectedPops);
}

void displaySolutions(std::vector<Pop>& popList, std::vector<int> selectedPops, int rayon) {
    for (int i=0; i<int(popList.size()); i++) {
        if (isIn(i, selectedPops)) {
            popList[i].is_in_list = true;
        } else {
            popList[i].is_in_list = false;
        }
    }
    display(popList, 13);
}

void finish(std::vector<Pop> popList, std::vector<int> selectedPops,
            int w, int h, int dh, int nb_rounds) {
    display(popList, 13);
    bool result = getAnswerPops(popList, selectedPops, nb_rounds);
    milliSleep(500);

    displaySolutions(popList, selectedPops, 13);

    if (result) {
        display((w-125)/2, (h+dh-125)/2, srcPath("t.png"));
    } else {
        display((w-125)/2, (h+dh-125)/2, srcPath("f.png"));
    }

    milliSleep(1800);
    display(popList, 13);
}




// ====================================== bArRe dE cHaRgEmEnT ====================================== //

void displayBarre(int w, int h, int dh, double proportion) {
    fillRect(w/25, h+dh-45, proportion*((23*w)/25), 20, RED);
}

void barre(int w, int h, int dh, int N, double zeit) {
    int zeitPiece = zeit/N;
    for (int n=0; n<N; n++) {
        displayBarre(w,h,dh,n/double(N));
        milliSleep(zeitPiece);
    }
}




// =============================== JEU DES SYMETRIQUES - FINAL ===================================== //

void simplePopsGame(std::vector<Pop> popList, std::vector<int> selectedPops,
                    int w, int h, int dh, int nb_rounds) {
    // Rounds
    for (int round=0; round<nb_rounds; round++) {
        // Affichage des Pops
        if (round>0){popList[selectedPops[round-1]].is_in_list = false;}
        popList[selectedPops[round]].is_in_list = true;
        display(popList, 13);

        // Barre de chargement (null)
        barre(w,h,dh,100,2500);

        // Temps d'attente
        blueScreen(w,h+dh);
        milliSleep(1000);
    }

    popList[selectedPops[nb_rounds-1]].is_in_list = false;

    // Jeu des Pops : Réponse candidat
    finish(popList, selectedPops, w, h, dh, nb_rounds);
    int x_, y_; getMouse(x_, y_);
}

void JeuDesSymetriques(std::vector<Pop> popList, std::vector<int> selectedPops,
                       int w, int h, int dh, int N1, int N2, double p, double p2, int nb_rounds) {
    // Initialisation de la seed random
    auto now = std::chrono::high_resolution_clock::now();
    auto seed = now.time_since_epoch().count();
    std::mt19937 gen(seed);

    // Lois de Bernoulli
    std::bernoulli_distribution dis(p);
    std::bernoulli_distribution dis2(p2);

    // Rounds
    for (int round=0; round<nb_rounds; round++) {
        //========JEU DES POPS=================//
        // Affichage des Pops
        if (round>0){popList[selectedPops[round-1]].is_in_list = false;}
        popList[selectedPops[round]].is_in_list = true;
        display(popList, 13);

        // Barre de chargement (null)
        barre(w,h,dh,100,2500);

        //=========JEU DES SYMETRIQUES=========//
        // === /!\ === Clear Events === /!\ === //
        // Affichage du jeu des symetriques
        bool is_sym = dis2(gen);
        displayGame(w, h, N1, N2, dis, gen, is_sym);

        // Attente (null) et barre de chargement (null)
        int x, y;
        bool answered = waitForClick(x,y,4); // In seconds
        bool check = getAnswerButton(x,w);

        // Display Answers
        displayAnswer(w, h+dh, is_sym, check, answered);
    }
    blueScreen(w,h+dh);
    popList[selectedPops[nb_rounds-1]].is_in_list = false;

    // Jeu des Pops : Réponse candidat
    finish(popList, selectedPops, w, h, dh, nb_rounds);
    int x_, y_; getMouse(x_, y_);
}

