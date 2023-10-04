#include "services/network/IConnection.h"
#include "services/network/tcpconnection.h"




namespace Network {

    template<typename SocketType>
    std::unique_ptr<IConnection> createConnection(SocketType socket, ConnType type)
    {
        switch(type){


        case ConnType::TCP:{

            std::unique_ptr<TCPConnection> derived = std::make_unique<TCPConnection>(socket);
            return std::unique_ptr<IConnection>{std::move(derived)};

        }
        }
    }

}

