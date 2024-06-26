#include "boost/beast/core/error.hpp"
#include "boost/beast/http/field.hpp"
#include "boost/beast/http/verb.hpp"
#include "boost/beast/http/write.hpp"
#include "boost/core/ignore_unused.hpp"
#include "httpConnection.hh"
#include "logicSystem.hh"
#include "spdlog/spdlog.h"


httpConnection::httpConnection(tcp::socket&& socket)
    : _socket(std::move(socket)) { }

auto httpConnection::startListen() -> void {
    auto self = shared_from_this();

    auto handler = [self](beast::error_code ec_code, std::size_t bytes_transferred) {
        try {
            if ( ec_code ) {
                spdlog::error("httpConnection::startListen() error: {}", ec_code.message());
                return;
            }
            boost::ignore_unused(bytes_transferred);
            self->handleRequest();
            self->checkDeadline();
        }
        catch ( const std::exception& exp ) {
            spdlog::error("httpConnection::startListen() exception: {}", exp.what());
        }
    };
    http::async_read(_socket, _buffer, _request, handler);
}


auto httpConnection::writeResponse() -> void {
    auto self = shared_from_this();

    _response.content_length(_response.body().size());
    auto handler = [self](beast::error_code ec_code, std::size_t bytes_transferred) {
        self->_socket.shutdown(tcp::socket::shutdown_send, ec_code);
        self->_deadline.cancel();
    };
    http::async_write(_socket, _response, handler);
}

auto httpConnection::handleRequest() -> void {
    _request.version(_request.version());
    _response.keep_alive(false);

    if ( _request.method() == http::verb::get ) {
        bool success = logicSystem::getInstence()->handleGet(_request.target(), shared_from_this());
        if ( !success ) {                                            // 没有找到对应的 url
            _response.result(http::status::not_found);               // 404
            _response.set(http::field::content_type, "text/plain");  // 设置返回的数据类型为纯文本
            beast::ostream(_response.body()) << "url not found\r\n";  // 设置返回的数据
            writeResponse();                                          // 发送返回的数据
            return;
        }

        _response.result(http::status::ok);                // 200
        _response.set(http::field::server, "gateServer");  // 设置服务器名称
        writeResponse();                                   // 发送返回的数据
        return;
    }
}

auto httpConnection::checkDeadline() -> void {
    auto self = shared_from_this();

    _deadline.async_wait([self](beast::error_code ec_code) {
        if ( !ec_code ) {
            // TODO: 避免 time wait 状态
            self->_socket.close(ec_code);
            spdlog::info("httpConnection::checkDeadline() close socket");
            return;
        }
    });
}
