#include <iostream>
#include "saveJson.h"


using namespace std;



int main()
{
	Banque_Centrale testBanque = Banque_Centrale();
	save_json_Banque(testBanque);
	return 0;
}