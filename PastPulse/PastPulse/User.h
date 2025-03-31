#pragma once
#include "pch.h"
#ifndef USER_H
#define USER_H

using json = nlohmann::json;

int userRegister(json& users);
bool userLogin(const json& users);

#endif