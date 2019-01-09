#pragma once
#include <memory>
#include "Screen.h"
#include <vector>

class Controller
{
public:
	//=================constructor===================================
	Controller();
	//====================temp_function===============================
	void run();//run the program-controller  all the window
	~Controller()=default;//destructor
private:
	//====================proprties controller===============================
	std::vector<std::shared_ptr<Screen>>m_screen;//vector of all the windows in the program
	std::shared_ptr<Screen>m_runWindow;//the window that need to run
};
