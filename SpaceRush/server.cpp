//#include "server.h"
//#include <iostream>
//Server::Server() : m_listenThread(&Server::Listen, this) //, m_broadcastThread(&Server::Broadcast, this), get_positionThread(&Server::ReceivePosition, this)
//{
//    s_socket.bind(port);
//}
//
////void Server::setPlayers(int l_players)
////{
////    m_players = l_players;
////}
//
//void Server::ReceiveConnection()
//{
//    //cout << "Listening: ";
//    sf::IpAddress l_Ip;
//    unsigned short l_port;
//    sf::Socket::Status value;
//    value = s_socket.receive(m_buffer, sizeof(m_buffer), s_received, l_Ip, l_port);
//    //std::cout << "from ip : " << l_Ip << "from port : " << l_port << endl;
//    if (s_received > 0)
//    {
//        for (int i = 0; i < m_playerno; i++)
//        {
//            if (players[i].getIp() == l_Ip && players[i].getPort() == l_port)
//            {
//                std::cout << "The port and Ip address you chose already belongs to some other players." << endl;
//                break;
//            }
//        }
//        m_computer.setIp(l_Ip);
//        m_computer.setPort(l_port);
//        players.push_back(m_computer);
//
//        cout << "Received connection from Ip: " << l_Ip << " Port: " << l_port << endl;
//        m_playerno++;
//        //ConfirmConnection(l_Ip, l_port);
//    }
//}
//
////void Server::ConfirmConnection(sf::IpAddress l_ip, unsigned short l_port)
////{
////    sf::Packet packet;
////    std::string confirmation = "Connection Received by Server. ";
////    packet << confirmation << m_players << m_playerno;
////    s_socket.send(packet, l_ip, l_port);
////}
//
//void Server::SendPlaySignal()
//{
//    int playnumber = -2;
//    sf::Packet packet;
//    packet << playnumber;
//    for (int i = 0; i < m_playerno; i++)
//    {
//        s_socket.send(packet, players[i].getIp(), players[i].getPort());
//    }
//}
//
//void Server::Listen()
//{
//    sf::IpAddress tempip;
//    unsigned short tempport;
//    while (1)
//    {
//        sf::Packet packet;
//        s_socket.receive(packet, tempip, tempport);
//        if (s_received > 0)
//        {
//            SendtoOthers(tempip, tempport, packet);
//        }
//    }
//}
//
//void Server::SendtoOthers(sf::IpAddress l_ip, unsigned short l_port, sf::Packet packet)
//{
//    sf::IpAddress ip;
//    unsigned short port;
//
//    float x, y;
//    int playerid;
//    packet >> playerid >> x >> y;
//    for (int i = 0; i < m_playerno; i++)
//    {
//        ip = players[i].getIp();
//        port = players[i].getPort();
//
//        if (ip == l_ip && port == l_port)
//        {
//            continue;
//        }
//        // std::cout << "Received position of PLAYER " << playerid << playerid << "  (" << x << ", " << y << ")" << std::endl;
//        s_socket.send(packet, ip, port);
//    }
//}
//
//void Server::Thread()
//{
//    m_listenThread.launch();
//    // m_broadcastThread.launch();
//    // get_positionThread.launch();
//}