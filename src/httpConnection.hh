#pragma once

#include "boost/beast/http/dynamic_body.hpp"
#include "const.hh"

class httpConnection: public std::enable_shared_from_this<httpConnection>
{
    friend class logicSystem;

public:
    httpConnection(tcp::socket&& socket);
    auto startListen() -> void; 

private:  // private member functions
    auto checkDeadline() -> void;
    auto writeResponse() -> void;
    auto handleRequest() -> void;

private:  // private member variables
    tcp::socket                        _socket;
    beast::flat_buffer                 _buffer{ 8192 };
    http::request<http::dynamic_body>  _request;
    http::response<http::dynamic_body> _response;
    net::steady_timer _deadline{ _socket.get_executor(), std::chrono::seconds(60) };
};
