#pragma once
#include "pch.h"
#ifndef USER_H
#define USER_H

using json = nlohmann::json;

extern json users;
void initUsers();

int userRegister(json& users);
bool userLogin(const json& users);
json readUsersFromJson(const string& filename);
#endif