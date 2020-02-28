#include "server.h"
#include <iostream>
Server::Server():listenThread(&Server::listen, this)
{
	s_socket.bind(port);
    //serverIp = "127.0.0.1";
    serverIp = sf::IpAddress::getLocalAddress();
    //s_socket.setBlocking(false);
}
void Server::recieveConnection()
{
    std::string test;
    int a;
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
    packet >> test >> a;
    std::cout << test << a;
}
void Server::listen()
{
    sf::IpAddress tempip;
    unsigned short tempport;
    while (1)
    {
        sf::Packet packet;
        
        s_socket.receive(packet, tempip, tempport); // Received upto this point.
        
        send(packet, tempip,tempport); 
    }
}

void Server::send(sf::Packet packet, sf::IpAddress ip, unsigned short port)
{
    
    float xpos, ypos, angle;
    unsigned int health;
    int playerid;
    bool shoot;
    packet >> playerid >> xpos >> ypos >> angle >> health >> shoot ; 
    //std::cout << playerid << ": " << xpos << " " << ypos << "\n"; //Recieved upto this point.
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