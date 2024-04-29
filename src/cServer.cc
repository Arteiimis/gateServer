#include "cServer.hh"
#include "httpConnection.hh"

cServer::cServer(net::io_context& ioc, port_t port)
    : _acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _ioc(ioc), _socket(ioc) { }

void cServer::startListen() {
    auto self = shared_from_this();
    spdlog::info("cServer::startListen() start listening...");
    _acceptor.async_accept(_socket, [self, this](beast::error_code ec_code) {
        try {
            // 出错时放弃本次链接，继续监听其他链接
            if ( ec_code ) {
                self->startListen();
                return;
            }
            std::make_shared<httpConnection>(std::move(_socket))->startListen();
            spdlog::info("cServer::startListen() new connection");
            // 继续监听其他链接
            self->startListen();
        }
        catch ( const std::exception& exp ) {
            spdlog::error("cServer::startListen() exception: {}", exp.what());
        }
    });
}
