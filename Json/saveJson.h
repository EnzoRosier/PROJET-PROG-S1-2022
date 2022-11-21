#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include "../Banque/Banque.h"

#ifdef _WIN32
#include <SDKDDKVer.h>
#endif

int save_json_Banque(Banque_Centrale& bq);
