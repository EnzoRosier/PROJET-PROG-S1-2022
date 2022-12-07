#pragma once
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include "../Banque/Banque.h"


using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

#ifdef _WIN32
#include <SDKDDKVer.h>
#endif

int save_json_registre(Banque_Centrale& bq);
Compte Compte_from_ptree(ptree& pt);
Client Client_from_ptree(ptree& pt);
