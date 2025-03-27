#ifndef USER_H
#define USER_H
#include "json.hpp"
using json = nlohmann::json;

int userRegister(json& users);

#endif