#include "saveJson.h"



int save_json_registre(Banque_Centrale& bq) {
    std::ofstream file_out("RegistrePrincipale.json");
    write_json(file_out, bq.GeneratePtreeBanque());
    file_out.close();
    return 1;
}