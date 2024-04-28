#include "cServer.hh"

cServer::cServer(net::io_context& ioc, port_t port)
    : _acceptor(ioc, tcp::endpoint(tcp::v4(), port)), _ioc(ioc), _socket(ioc) { }

void cServer::start() {
    auto self = shared_from_this();
    // _acceptor.async_accept(_socket, [self](beast::error_code ec_code) {
    //     try {
    //         // 出错时放弃本次链接，继续监听其他链接
    //         if ( ec_code ) {
    //             self->start();
    //             return;
    //         }
    //         // TODO: 为新的连接创建一个httpConnection对象
    //         std::make_shared<httpConnection>(std::move(_socket))->start();
    //         // 继续监听其他链接
    //         self->start();
    //     }
    //     catch ( const std::exception& exp ) {
    //     }
    // });
}
