#include <iostream>
#include <SFML/Network.hpp>
#include "Receiver.h"
#include <thread>
#include <list>

using namespace std;

void accepter(Queue<std::string> &queue, std::list<sf::TcpSocket*> &sockets, std::mutex &m)
{
    sf::TcpListener listener;
    sf::Socket::Status status = listener.listen(4300);
    if (status != sf::Socket::Done)
    {
        std::cerr << "Listen: " << status << std::endl;
        return;
    }

    while (1)
    {
        sf::TcpSocket *socket = new sf::TcpSocket;
        status = listener.accept(*socket);
        { // New!
            std::unique_lock<std::mutex> l(m);
            sockets.push_back(socket);
        }
        if (status != sf::Socket::Done)
        {
            std::cerr << "Accept: " << status << std::endl;
            return;
        }
        Receiver *r = new Receiver(socket, true, queue);
        std::thread([r]{r->recv_loop();}).detach();
    }
}

int main()
{
    Queue<std::string> queue;
    std::mutex m;
    std::list<sf::TcpSocket*> sockets;
    std::thread(accepter, std::ref(queue), std::ref(sockets), std::ref(m)).detach();

    while(1)
    {
        std::string s = queue.pop(); // Blocking!
        std::cout << "Main read: '" << s << "'\n";
        {
            std::unique_lock<std::mutex> l(m);
            for (auto socket : sockets) {
                sf::Socket::Status status = socket->send(s.c_str(), s.size());
                if (status != sf::Socket::Done) {
                    std::cout << "Sending failed: " << status << std::endl;
                }
            }
        }
    }
    return 0;
}

