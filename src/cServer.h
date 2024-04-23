#ifndef CSERVER_H
#define CSERVER_H

#include "boost/asio/io_context.hpp"
#include "consts.h"
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>

class cServer: public std::enable_shared_from_this<cServer>
{
    using port_t = unsigned short;

public:
    cServer(net::io_context& ioc, port_t port);
    void start();

private:
    tcp::acceptor    _acceptor;  // 用于接受客户端连接的监听器
    net::io_context& _ioc;       // 用于处理客户端连接的io_context
    tcp::socket      _socket;    // 用于处理客户端连接的socket
};

#endif  // !CSERVER_H
