#pragma once
#include <boost/property_tree/json_parser.hpp>
#include "../../Client/Client.h"
#include "../../Compte/Compte.h"
#include "../../Banque/Banque.h"

#ifndef __DEF_ID
#define __DEF_ID
string generateIDCompte(string pays, Client& cl, bool isEpargne);
#endif