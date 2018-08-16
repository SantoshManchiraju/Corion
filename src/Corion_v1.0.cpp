//============================================================================
// Name        : Corion_v1.0.cpp
// Author      : Krishna Santosh Manchiraju
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Main file for ppu controller
//============================================================================

#include <iostream>

#include "Cerebrum.h"

using namespace std;

int main(int argc, char *argv[]) {

	// main controller
	Cerebrum mainBrain(argc, argv);

	mainBrain.run();

	return 0;
}

