#ifndef MENU_H
#define MENU_H

#include <Imagine/Graphics.h>
using namespace Imagine;

void display(int x, int y, const std::string& name);
bool developInfos(int w, int h, int dh, int x, int y);
void displayMenu(int w);
int getIndex(int x, int y);
int updatePassage(int w, int h, int dh, int index);

#endif // MENU_H
