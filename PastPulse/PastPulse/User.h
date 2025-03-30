#pragma once
#include "pch.h"
#ifndef USER_H
#define USER_H

using json = nlohmann::json;

int userRegister(json& users);

#endif