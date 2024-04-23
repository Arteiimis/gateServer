#include "boost/beast/core/error.hpp"
#include "cServer.h"
#include <memory>


cServer::cServer(net::io_context& ioc, port_t port)
    : _acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _ioc(ioc), _socket(ioc) { }

void cServer::start() {
    auto self = shared_from_this();
    _acceptor.async_accept(_socket, [self](beast::error_code code) {
        try {
            if ( code ) {
                self->start();
                return;
            }
        }
        catch ( const std::exception& exp ) {
        }
    });
}
