#include "client.h"
#include <iostream>
#include <fstream>
Client::Client() : listenThread(&Client::listen, this)
{
    std::string sIp;
    c_socket.bind(sf::Socket::AnyPort);
    std::ifstream infile;
    infile.open("ip.txt");
    infile >> sIp;
    std::cout << sIp;
    sf::IpAddress send(sIp);
    serverIp = send;
    infile.close();
}

Client::Client(sf::IpAddress l_ip) : listenThread(&Client::listen, this)
{
    c_socket.bind(sf::Socket::AnyPort);
    serverIp = l_ip;
    sendConnection();
}


void Client::sendConnection()
{
    sf::Packet packet;
    std::string test = "Connection Sent to Server\n";
    packet << test;
    c_socket.send(packet, serverIp, 8000);
}

void Client::send(sf::Packet packet)
{
    c_socket.send(packet, serverIp, 8000);
}
void Client::listen()
{
    float xpos, ypos, angle;
    unsigned int health;
    bool shoot;
    int playerid;
    sf::Socket::Status value;
    sf::IpAddress tempip;
    unsigned short tempport;
    sf::Packet packet;
    while (1)
    {
        value = c_socket.receive(packet, tempip, tempport);
        if (value == 0)
        {
            packet >> playerid >> xpos >> ypos >> angle >> health >> shoot;
            playerId = playerid;
            positions[playerId] = sf::Vector2f{ xpos, ypos };
            healths[playerId] = health;
            directions[playerId] = angle;
            shoots[playerId] = shoot;
        }
    }
}

sf::Vector2f Client::getPosition(int playerid)
{
    return positions[playerid];
}
unsigned int Client::getHealth(int playerid)
{
    return healths[playerid];
}
float Client::getDirection(int playerid)
{
    return directions[playerid];
}
bool Client::isShooting(int playerid)
{
    return shoots[playerid];
}

void Client::thread()
{
    listenThread.launch();
}