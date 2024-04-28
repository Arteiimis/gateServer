#include "logicSystem.hh"
#include <boost/beast/core/ostream.hpp>
#include <utility>

logicSystem::logicSystem() {
    registGet("/get_test", [](std::shared_ptr<httpConnection> conn) {
        beast::ostream(conn->_response.body()) << "get_test";
    });
}

auto logicSystem::registGet(std::string url, httpHandler handler) -> void {
    _get_handlers.insert(std::make_pair(url, handler));
}

auto logicSystem::handleGet(std::string url, std::shared_ptr<httpConnection> conn) -> bool {
    if ( _get_handlers.find(url) == _get_handlers.end() ) {
        return false;
    }
    // 调用注册的 handler
    _get_handlers[url](conn);
    return true;
}
