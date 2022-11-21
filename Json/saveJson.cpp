#include "saveJson.h"

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

int save_json_Banque(Banque_Centrale& bq) {
    ptree pt;
    std::ofstream file_out("BanqueCentral.json");
    pt.put("BanqueNumber", bq.Get_nb_banque_decentralise());
    write_json(file_out, pt);
    file_out.close();
    return 1;
}