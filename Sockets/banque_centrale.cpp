#include "tools.cpp"


/*
Types de requ�tes :
    - Update : la banque centrale met � jour sa base de donn�e en collectant la base de donn�e de la banque d�centralis�e
               envoie un string ("Update") et recoit une banque_decentralisee
    - Find : Pour retrouver un compte,recoit un id de compte, renvoie un client 
    - Exit : Pour fermer l'executable et sauvegarder le registre, recoit un string ("Exit") et ne renvoie rien

*/



int main() {
    // On initialise le registre � partir d'un .Json sauvegarder au pr�alable
    // Et on actualise �galement le ragistre pour mettre � jour les �ventuelles modifications non enregistr�es

    Banque_Centrale BC;
    // A compl�ter (ptree)

    bool exit = false;
    while (exit == false) {

        // On commence par se mettre en attente de reception d'un socket

        boost::asio::io_service io_service;
        tcp::acceptor acceptor_(io_service, tcp::endpoint(tcp::v4(), 1234));
        socket_ptr socket(new tcp::socket(io_service));
        acceptor_.accept(*socket);
        char demande[10000] = {};
        boost::system::error_code error;
        size_t length = socket->read_some(boost::asio::buffer(demande), error);

        // Hourra on a re�u un socket, il faut maintenant analyser la demande
   
        if (demande == "Exit") { // Si c'est pour finir
            exit = true;
        }
        else { // Sinon c'est que c'est une demande de recherche de compte

            
        }
        
    }
    //Sauvegarde du registre
    return 0;
}