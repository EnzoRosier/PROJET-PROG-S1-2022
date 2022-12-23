#pragma once
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include "../Banque/Banque.h"
#include "../PROJET PROG S1 2022/Fonctions/Transaction.h"


using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

#ifdef _WIN32
#include <SDKDDKVer.h>
#endif

int save_json_registre(Banque_Centrale& bq); //sauvegarde le registre principal
Compte Compte_from_ptree(ptree& pt); // Convertie un Compte en Ptree
Client Client_from_ptree(ptree& pt); // Convertie un Client en Ptree
Banque_Centrale Banque_from_ptree(ptree& pt); // Convertie une Banque en Ptree
