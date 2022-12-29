#include "Threadfonctions.h"

void update() {
	//Tes sockets ici Olivier
}

void updateThread(Banque_Centrale& bq)
{
	while (true) {
		int n = 30;
		time_t start, end;
		start = time(0);
		while (1)
		{

			if (time(0) - start >= n)
			{
				update();
			}
		}
	}
}

