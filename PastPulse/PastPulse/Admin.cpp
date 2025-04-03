#include "User.h"
#include "Admin.h"
#include "Menu.h"
#include "Riddle.h" 

bool adminLogin ( string username, string password ) {
	string Admin_User = "admin";
	string Admin_Pass = "admin-123";

	return (username == Admin_User && password == Admin_Pass);

}