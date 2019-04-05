#include <iostream>
#include <SFML/Network.hpp>
#include "Receiver.h"
#include <thread>
#include <list>

using namespace std;

void accepter(Queue<std::string> &queue, std::list<sf::TcpSocket*> &sockets, std::mutex &m)
{
    sf::TcpListener listener;
    sf::Socket::Status status = listener.listen(4302);
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
        Receiver *r = new Receiver(socket, queue);
        std::thread([r]{r->recv_loop();}).detach();
    }
}

void runServer()
{
    Queue<std::string> queue;
    std::mutex m;
    std::list<sf::TcpSocket*> sockets;
    std::thread(accepter, std::ref(queue), std::ref(sockets), std::ref(m)).detach();

    while(1)
    {
        std::string s = queue.pop(); // Blocking!
        std::cout << "Main thread: '" << s << "' \n";
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
}

void runClient()
{
    Queue<std::string> queue;
    sf::TcpSocket* socket;
    Receiver receiver(socket, queue);
    //std::thread(receiver.recv_loop()).detach();



    /*

    step 1: queue
    step 2: receive thread(queue)
    step 3: Game game(queue)
    step 4: game.run()

    */
}

int main()
{
    char input;
    while (input != 's' && input != 'c')
    {
        std::cout << "(s)erver or (c)lient?" << std::endl;
        std::cin >> input;
    }

    if(input == 's')
    {
        runServer();
    }
    else
    {
        runClient();
    }


    return 0;
}

