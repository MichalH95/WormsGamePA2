#ifndef HELPER_H
#define HELPER_H

#include "worm.h"

void printFrame();

void printError(const char * err);

bool isFirstWorm(int c);

bool isSecondWorm(int c);

void endOfGameScreen(const Worm & w1, const Worm & w2);

void controlsScreen();

#endif /* HELPER_H */