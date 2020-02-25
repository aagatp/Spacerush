#pragma once
#include <SFML/Network.hpp>
class Computer
{
private:
    sf::IpAddress ip;
    unsigned short port;

public:
    Computer();
    //Computer(sf::IpAddress, unsigned short);
    void setPort(unsigned short);
    void setIp(sf::IpAddress);
    unsigned short getPort();
    sf::IpAddress getIp();
};

