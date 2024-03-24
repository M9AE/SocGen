#ifndef SYMETRIQUES_H
#define SYMETRIQUES_H

#include <random>

#include "Pops.h"

#include <Imagine/Graphics.h>
using namespace Imagine;



void initializeDisplayBool(std::vector<std::vector<bool>>& displayBool, int N1, int N2, std::bernoulli_distribution& dis, std::mt19937& gen);
void displayCout(std::vector<std::vector<bool>> displayBool);

struct Symetrique {
public:
    std::vector<std::vector<bool>>& displayBool1;
    std::vector<std::vector<bool>>& displayBool2;
    bool symetrique;
// Functions :
    Symetrique(bool _symetrique_, int N1, int N2, std::vector<std::vector<bool>>& refVector1, std::vector<std::vector<bool>>& refVector2)
        : displayBool1(refVector1), displayBool2(refVector2), symetrique(_symetrique_) {
    }
    void display(int w, int h, int a);
    void displaySym(int w, int h, int a);
    void displayNonSym(int w, int h, int a);
};

void displayGame(int w, int h, int N1, int N2, std::bernoulli_distribution& dis, std::mt19937& gen, bool typeBool);
void displayButton(int w, int h);

bool getPositionAtClick(int& x, int& y);
bool waitForClick(int& x, int& y, double delta_t);
bool getAnswer(int x, int w);
void displayAnswer(bool is_sym, bool check, bool answered);

void blueScreen(int w, int h);

void simplePopsGame(std::vector<Pop> popList, std::vector<int> selectedPops,
                    int w, int h, int dh, int nb_rounds);

void JeuDesSymetriques(std::vector<Pop> popList, std::vector<int> selectedPops,
                       int w, int h, int dh, int N1, int N2, double p, double p2, int nb_rounds);

#endif // SYMETRIQUES_H
