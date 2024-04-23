#ifndef CHTTPCONNECTION_H
#define CHTTPCONNECTION_H

#include "boost/beast/http/dynamic_body.hpp"
#include "boost/beast/http/message.hpp"
#include "consts.h"
#include <memory>

class httpConnection : public std::enable_shared_from_this<httpConnection>
{
public:
    explicit httpConnection(tcp::socket socket);
    ~httpConnection();

    void start();

private:
    void checkDeadLine();
    void writeResponse();
    void handleRequest();

private:
    tcp::socket                        _socket;    // 用于处理客户端连接的socket
    beast::flat_buffer                 _buffer;    // 用于存储请求数据
    http::request<http::dynamic_body>  _request;   // 用于存储请求数据
    http::response<http::dynamic_body> _response;  // 用于存储响应数据

    // 用于设置超时时间
    net::steady_timer _dead_line{ _socket.get_executor(), std::chrono::seconds(60) };
};
#endif
