#include "ClientInfoList.h"
#include "ClientInfo.h"

ClientInfoList::ClientInfoList()
{
    //ctor
}

bool ClientInfoList::add(unsigned short id, ClientInfo* c)
{
    std::unique_lock<std::mutex> l(m);
    clientInfoMap.insert(std::pair<unsigned short, ClientInfo*>(id, c));
}

bool ClientInfoList::remove(unsigned int id)
{
    std::unique_lock<std::mutex> l(m);
    clientInfoMap.erase(id);
}

bool ClientInfoList::sendAllUdp(std::string &msg)
{
    std::unique_lock<std::mutex> l(m);
    for(size_t i = 0; i < clientInfoMap.size(); i++)
    {
        clientInfoMap[i]->uSend(msg);
    }
}

bool ClientInfoList::sendAllTcp(std::string &msg)
{
    std::unique_lock<std::mutex> l(m);
    for(size_t i = 0; i < clientInfoMap.size(); i++)
    {
        clientInfoMap[i]->tSend(msg);
    }
}
