#include "Receiver.h"
#include <cstring>
#include <iostream>

Receiver::Receiver(sf::TcpSocket* s, Queue<std::string>& queue_):
    socket(s),
    queue(queue_)
{
    //ctor
}


void Receiver::recv_loop()
{
    char buffer[256];
    while(1)
    {
        std::memset(buffer, 0, 256);
        std::size_t received;
        sf::Socket::Status status = socket->receive(buffer, 256, received);

        if (status != sf::Socket::Done)
        {
            perror("Receive");
            std::cerr << "Receive: " << status << std::endl;
            return;
        }

        queue.push(std::string(buffer));
    }
}
