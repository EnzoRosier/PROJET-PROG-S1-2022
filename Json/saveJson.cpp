#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <fstream>
#include "../Banque/Banque.h"

#ifdef _WIN32
#include <SDKDDKVer.h>
#endif


using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

ptree save_json_Banque(const Banque_Centrale& bq) {
    ptree pt;
    std::ofstream file_out("BanqueCentral.json");
    
    pt.put("BanqueNumber", bq.nb_banque_decentralise);
    write_json(file_out, pt_write);
    file_out.close();
    return pt;
}