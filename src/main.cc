#include "boost/asio/io_context.hpp"
#include "boost/asio/signal_set.hpp"
#include "cServer.hh"
#include "const.hh"
#include <memory>

int main(int argc, const char** argv) {
    try {
        port_t                  port = static_cast<port_t>(8080);
        net::io_context         ioc{ 1 };
        boost::asio::signal_set signals(ioc, SIGINT, SIGTERM);

        signals.async_wait([&ioc](beast::error_code ec_code, int signal_number) {
            boost::ignore_unused(signal_number);
            if ( ec_code ) {
                spdlog::error("main() signal_set error: {}", ec_code.message());
                return;
            }
            ioc.stop();
        });

        std::make_shared<cServer>(ioc, port)->startListen();
        ioc.run();
    }
    catch ( const std::exception& exp ) {
        spdlog::error("main() exception: {}", exp.what());
    }
    return 0;
}
