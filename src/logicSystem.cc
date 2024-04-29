#include "logicSystem.hh"
#include <boost/beast/core/ostream.hpp>
#include <utility>

logicSystem::logicSystem() {
    // 在这里注册所有的 get 请求
    registGet("/get_test", [](std::shared_ptr<httpConnection> conn) {
        beast::ostream(conn->_response.body()) << "get_test";
    });
}

/**
 * @brief 将指定的 url 和 handler 注册到 _get_handlers 中
 * 
 * @param url
 * @param handler 
 */
auto logicSystem::registGet(std::string url, httpHandler handler) -> void {
    _get_handlers.insert(std::make_pair(url, handler));
}

auto logicSystem::handleGet(std::string url, std::shared_ptr<httpConnection> conn) -> bool {
    // 查找是否有对应的 handler
    if ( _get_handlers.find(url) == _get_handlers.end() ) {
        return false;
    }
    // 调用注册的 handler
    _get_handlers[url](conn);
    return true;
}
