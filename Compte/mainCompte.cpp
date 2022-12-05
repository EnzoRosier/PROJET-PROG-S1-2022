#include <iostream>
#include "Compte.h"

using namespace std;

int main()
{
	auto testA = Compte("23", 2);

	std::ofstream file_out("Compte.json");
	write_json(file_out, testA.generate_Ptree_Compte());
	file_out.close();
	return 0;
}