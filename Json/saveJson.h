#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>

#ifdef _WIN32
#include <SDKDDKVer.h>
#endif

#include "../Compte/Compte.h"

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;
