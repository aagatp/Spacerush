#include "server.h"
#include <iostream>

Server::Server():listenThread(&Server::listen, this)
{
	s_socket.bind(port);
    serverIp = sf::IpAddress::getLocalAddress();
}

void Server::recieveConnection()
{
    sf::Packet packet;
    sf::IpAddress remoteIp;
    unsigned short remotePort;
    s_socket.receive(packet, remoteIp, remotePort);
    if (serverIp != remoteIp)
    {
        otherIp = remoteIp;
        otherPort = remotePort;
    }
    else
    {
        hostPort = remotePort;
    }
    std::cout << "Connection Recived from: " << remoteIp <<"\n";
}
void Server::listen()
{
    sf::IpAddress tempip;
    unsigned short tempport;
    while (1)
    {
        sf::Packet packet;
        
        s_socket.receive(packet, tempip, tempport);
        
        send(packet, tempip,tempport); 
    }
}

void Server::send(sf::Packet packet, sf::IpAddress ip, unsigned short port)
{
    
    for (int i = 0; i < 2; i++)
    {
        if (serverIp == ip)
        {
            s_socket.send(packet, otherIp, otherPort);
        }
        else
        {
            s_socket.send(packet, serverIp, hostPort);
        }
    }
}

void Server::thread()
{
	listenThread.launch();
}