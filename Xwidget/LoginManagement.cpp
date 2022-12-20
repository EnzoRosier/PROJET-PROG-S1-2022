#include "../PROJET PROG S1 2022/includer.h"
#include "LoginManagement.h"

using namespace std;

bool verification_password(int login, string password, map <int, string, greater<>> m){

	for (auto itr = m.begin(); itr != m.end(); ++itr) {
		while (itr->first == login) {
			if (itr->second == password) {
				return true;
			}
			else {
				return false;
			}
		}
	}

	return false;
}