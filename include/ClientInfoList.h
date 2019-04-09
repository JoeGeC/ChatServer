#ifndef CLIENTINFOLIST_H
#define CLIENTINFOLIST_H

#include <map>
#include <mutex>
#include "ClientInfo.h"

class ClientInfoList
{
    public:
        ClientInfoList();

        bool add(unsigned short id, ClientInfo* c);
        bool remove(unsigned int id);
        bool sendAllUdp(std::string &msg); //Can use ID to avoid sending
        bool sendAllTcp(std::string &msg); //to the originator.

    private:
        std::map<unsigned short, ClientInfo*> clientInfoMap;
        std::mutex m;
};

#endif // CLIENTINFOLIST_H
