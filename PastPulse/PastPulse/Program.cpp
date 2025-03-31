#include "User.h"
#include "Admin.h"
#include "Menu.h"
#include "Riddle.h"

int main() 
{
	std::string filename = "riddles.json";
	Riddle* riddlesHead = loadRiddlesFromFile(filename);
	//displayRiddles(riddlesHead);
	menu();
}
