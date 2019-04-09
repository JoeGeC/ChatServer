#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include <SFML/Network.hpp>
#include "Queue.h"

struct Message
{
    enum class Type
    {
        Disconnect,
        Standard
        //could add position, attack, spell, etc...
    };

    Type type = Type::Standard;
    unsigned short senderID;
    char payload[];
};

class ClientInfo
{
    public:
        unsigned short id;
        std::string username;
        ClientInfo(sf::TcpSocket *s, Queue<std::string> &q);
        void setUdp(sf::UdpSocket *s, sf::IpAddress a, unsigned short p);
        bool connect(); //TCP
        bool tSend(std::string msg);
        bool tRecv(std::string &s); // optional
        bool tRecvLoop(); // thread
        bool uSend(std::string msg);
        bool uRecv(std::string &s); // optional
        bool uRecvLoop(); //Runs in a thread
        void push(std::string &s); //Enqueues
        std::string pop(); //Dequeues

    protected:

    private:
        sf::TcpSocket *tSocket; //Could use smart pointers
        sf::UdpSocket *uSocket;
        sf::IpAddress address = "152.105.67.102"; //For TCP connect and UDP send
        unsigned short uPort; //For UDP send
        unsigned short tPort = 4302; //For TCP connect
        Queue<std::string> &q; //Message to be defined
};

#endif // CLIENTINFO_H
