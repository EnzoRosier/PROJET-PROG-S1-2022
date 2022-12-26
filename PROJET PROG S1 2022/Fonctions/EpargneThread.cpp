#include "Threadfonctions.h"

void epargneCalcule(Banque_Centrale& bq) {
    for (int i = 0; i < ; i++)
    {

    }
}

void epargneThread(Banque_Centrale& bq) 
{
    while (true) {
        int n = 5;
        int milli_seconds = 5000;
        time_t start, end;
        start = time(0);
        while (1)
        {

            if (time(0) - start == n)
            {
                epargneCalcule(bq);
                start = start + n;
            }
        }
    }
}

