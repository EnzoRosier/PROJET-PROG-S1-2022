#include "Threadfonctions.h"

std::mutex locks;

void saveThread(Banque_Centrale& bq)
{
	while (true) {
		int n = 20;
		time_t start, end;
		start = time(0);
		while (1)
		{

			if (time(0) - start >= n)
			{
				locks.lock();
				save_json_registre(bq);
				start = time(0);
				locks.unlock();
			}
		}
	}
}