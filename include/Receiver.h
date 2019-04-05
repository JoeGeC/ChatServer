#ifndef RECEIVER_H
#define RECEIVER_H

#include "Queue.h"
#include <SFML/Network.hpp>

class Receiver
{
    public:
        Receiver(sf::TcpSocket* s, Queue<std::string>& queue);
        void recv_loop();

    protected:

    private:
        sf::TcpSocket* socket;
        bool isServer = false;
        Queue<std::string> &queue;

};

#endif // RECEIVER_H
