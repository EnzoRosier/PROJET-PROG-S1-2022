#include "Threadfonctions.h"



void saveThread(Banque_Centrale& bq)
{
	while (true) {
		int n = 100;
		time_t start, end;
		start = time(0);
		while (1)
		{

			if (time(0) - start >= n)
			{
				save_json_registre(bq);
				start = time(0);
				cout << "Registre saved sucessfully" << endl;
				
			}
		}
	}
}