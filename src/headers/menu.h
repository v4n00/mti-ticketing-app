#pragma once
#include <iostream>
#include "file.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Menu {
public:
	File file;

	void start(int argc, char** argv);
	void end();

	int node0(int choice);

	void option1();
	void option11(Location* location);
	void option12(Event* event);

	void option2();

	void option3();

	void option4();
	void option41(Location* location);
	void option42(Event* event);
	
	void option5();
	void option51(Location* location);
};