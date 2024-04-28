#pragma once

#include "const.hh"
#include "httpConnection.hh"
#include "singleton.hh"
#include <functional>
#include <map>
#include <memory>
#include <string>

using httpHandler = std::function<void(std::shared_ptr<httpConnection>)>;

class logicSystem: public singleton<logicSystem>
{
    friend class singleton<logicSystem>;

public:  // public member functions
    ~logicSystem() = default;

    auto registGet(std::string url, httpHandler handler) -> void;
    auto handleGet(std::string url, std::shared_ptr<httpConnection> conn) -> bool;

private:  // private member functions
    logicSystem();
    std::map<std::string, httpHandler> _post_handlers;
    std::map<std::string, httpHandler> _get_handlers;
};
