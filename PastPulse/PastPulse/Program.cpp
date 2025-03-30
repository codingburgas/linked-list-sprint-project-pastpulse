#include "User.h"
#include "Admin.h"
#include "Menu.h"
#include "Riddle.h"



using namespace std;

void gotoxy(int x, int y) {
	COORD coord = { static_cast<SHORT>(x),static_cast<SHORT>(y) };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}


json readUsersFromJson(const string& filename) {
	ifstream file(filename);
	json j;
	if (file.is_open()) {
		file >> j;
		file.close();


	}
	else {
		j = { {"users", json::array()} };
	}
	return j;
}

void hideCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);

}

int main() {
	string filename = "riddles.json";
	Riddle* riddlesHead = loadRiddlesFromFile(filename);
	menu();
}
