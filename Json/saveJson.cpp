#include "saveJson.h"



int save_json_registre(Banque_Centrale& bq) {
    ptree pt;
    std::ofstream file_out("BanqueCentrale.json");
    pt.put("BanqueNumber", bq.Get_nb_banque_decentralise());
    write_json(file_out, pt);
    file_out.close();
    return 1;
}