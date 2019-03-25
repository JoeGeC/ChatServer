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
        bool sendAllUdp(Message &m); //Can use ID to avoid sending
        bool sendAllTcp(Message &m); //to the originator.

    protected:

    private:
        std::map<unsigned short, ClientInfo*> list;
        std::mutex m;
};

#endif // CLIENTINFOLIST_H
