#pragma once
#include "../includer.h"
#include "../../Client/Client.h"
#include "../../Banque/Banque.h"

#ifndef __TRANSACTION
#define __TRANSACTION

Transaction doTransaction(string date, string debiteur, string crediteur, int montant, Banque_Centrale& Banque);

#endif