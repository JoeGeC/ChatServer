#include "ClientInfo.h"
#include <iostream>
#include <cstring>
#include <SFML/Network.hpp>

ClientInfo::ClientInfo(sf::TcpSocket *s, Queue<std::string> &q)
{
    //ctor
}

bool ClientInfo::connect()
{
    sf::Socket::Status status = tSocket->connect(address, tPort);
    if (status != sf::Socket::Done)
    {
        perror("tConnect");
        std::cerr << "tConnect: " << status << std::endl;
        return false;
    }
    else
    {
        return true;
    }
}

bool ClientInfo::tSend(std::string msg)
{
    sf::Socket::Status status = tSocket->send(msg.c_str(), msg.length());
    if (status != sf::Socket::Done)
    {
        perror("tSend");
        std::cerr << "tSend: " << status << std::endl;
        return false;
    }
    else
    {
        return true;
    }
}

bool ClientInfo::tRecvLoop()
{
    char buffer[256];
    while(1)
    {
        std::memset(buffer, 0, 256);
        std::size_t received;
        sf::Socket::Status status = tSocket->receive(buffer, 256, received);

        if (status != sf::Socket::Done)
        {
            perror("Receive");
            std::cerr << "Receive: " << status << std::endl;
            return false;
        }

        q.push(std::string(buffer));
    }
}

bool ClientInfo::uSend(std::string msg)
{
    sf::Socket::Status status = uSocket->send(msg.c_str(), msg.length(), address, uPort);
    if (status != sf::Socket::Done)
    {
        perror("uSend");
        std::cerr << "uSend: " << status << std::endl;
        return false;
    }
    else
    {
        return true;
    }
}

bool ClientInfo::uRecvLoop()
{
    char buffer[256];
    while(1)
    {
        std::memset(buffer, 0, 256);
        std::size_t received;
        sf::Socket::Status status = uSocket->receive(buffer, 256, received, address, uPort);

        if (status != sf::Socket::Done)
        {
            perror("Receive");
            std::cerr << "Receive: " << status << std::endl;
            return false;
        }

        q.push(std::string(buffer));
    }
}

void ClientInfo::push(std::string& msg)
{
    q.push(std::string(msg));
}

std::string ClientInfo::pop()
{
    return q.pop();
}
