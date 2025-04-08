#pragma once
#include "pch.h"
using json = nlohmann::json;

extern json users;
void initUsers();

int userRegister(json& users);
bool userLogin(const json& users);
json readUsersFromJson(const string& filename);