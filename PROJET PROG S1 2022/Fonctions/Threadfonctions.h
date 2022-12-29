#pragma once
#include <cstdlib>
#include <iostream>
#include <boost/bind/bind.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include "../includer.h"
#include "../../Client/Client.h"
#include "../../Banque/Banque.h"
#include "../../Json/load_save_Json.h"
#include <boost/thread.hpp>
#include <thread>

using namespace std;
using boost::asio::ip::tcp;

#ifndef __THREADFONCTIONS
#define __THREADFONCTIONS

void epargneThread(Banque_Centrale& bq);
void saveThread(Banque_Centrale& bq);
void updateThread(Banque_Centrale& bq);

#endif