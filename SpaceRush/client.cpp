#include "client.h"
#include <iostream>
Client::Client() : listenThread(&Client::listen, this) //, m_readytoplayThread(&Client::PlaySignal, this)
{
    std::string sIp;
    c_socket.bind(sf::Socket::AnyPort);
    //c_socket.setBlocking(false);
    std::cout << "Enter server ip: ";
    std::cin >> sIp;
    sf::IpAddress send(sIp);
    serverIp = send;
}

Client::Client(sf::IpAddress l_ip) : listenThread(&Client::listen, this)
{
    c_socket.bind(sf::Socket::AnyPort);
    //c_socket.setBlocking(false);
    serverIp = l_ip;
    sendConnection();
}
void Client::sendConnection()
{
    sf::Packet packet;
    int a;
    std::cout << "Type anything to send: ";
    std::cin >> a;
    std::string test = "Connection Sent to Server\n";
    packet << test << a ;
    c_socket.send(packet, serverIp, 8000);
}

void Client::send(sf::Packet packet)
{
    float xpos, ypos, angle;
    unsigned int health;
    int playerid;
    packet >> playerid>> xpos>> ypos>> angle >> health;
    c_socket.send(packet, serverIp, 8000);
}
void Client::listen()
{
    float xpos, ypos, angle;
    unsigned int health;
    int playerid;
    sf::Socket::Status value;
    sf::IpAddress tempip;
    unsigned short tempport;
    sf::Packet packet;
    while (1)
    {
        value = c_socket.receive(packet, tempip, tempport); // Not recieved here.
        if (value == 0)
        {
            packet >> playerid >> xpos >> ypos >> angle >> health;
            //std::cout << playerid << ": " << xpos << " " << ypos << "\n";
            playerId = playerid;
            positions[playerId] = sf::Vector2f{ xpos, ypos };
            healths[playerId] = health;
            directions[playerId] = angle;
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

void Client::thread()
{
    listenThread.launch();
}