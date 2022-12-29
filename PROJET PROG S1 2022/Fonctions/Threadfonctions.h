#pragma once
#include "../includer.h"
#include "../../Client/Client.h"
#include "../../Banque/Banque.h"
#include "../../Json/load_save_Json.h"

#ifndef __THREADFONCTIONS
#define __THREADFONCTIONS

void epargneThread(Banque_Centrale& bq);
void saveThread(Banque_Centrale& bq);
void updateThread(Banque_Centrale& bq);

#endif