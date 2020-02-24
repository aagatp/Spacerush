//#pragma once
//
//#include <SFML/Network.hpp>
//#include <SFML/Graphics.hpp>
//#include <SFML/Window.hpp>
//class Server
//{
//private:
//
//    unsigned short port = 8000;
//    sf::IpAddress serverIp;
//    sf::UdpSocket s_socket;
//
//    char m_buffer[200];
//    std::size_t s_received;
//
//    sf::Thread m_listenThread;
//
//    sf::Vector2f m_position;
//
//public:
//    Server();
//
//    //void setPlayers(int);
//    void ReceiveConnection(); 
//    void ConfirmConnection(sf::IpAddress, unsigned short); 
//    void SendPlaySignal(); 
//
//    void SendtoOthers(sf::IpAddress, unsigned short, sf::Packet); //Send packet to all players except by whom the packet has been sent
//    void Listen(); 
//
//    void Thread();
//
//};
