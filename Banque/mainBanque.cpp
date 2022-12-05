#include "Banque.h"


using namespace std;
/*
int main()
{
	
	Banque_Centrale test;

	Banque_Decentralise truc;
	Banque_Decentralise truc2;

	Compte jesaispas("FR3", 100);
	//Client Toto(2, "Tata", "Toto", "Rue machin", "Lille", 42, jesaispas);


	cout << "ID agence : " << truc.Get_ID_agence() << " Nom agence : " << truc.Get_nom_agence() << endl;
	cout << "ID agence : " << truc2.Get_ID_agence() << " Nom agence : " << truc2.Get_nom_agence() << endl;
	return 0;
}*/

#include <thread>
#include <mutex>
void display(int start, int nb)
{
	for (int i = start; i < start + nb; ++i)
		std::cout << i << ",";
}
int main() {
	std::thread t1(display, 0, 5);
	std::thread t2([]() { display(5, 5); });
	t1.join();
	t2.join();
	return 0;
}