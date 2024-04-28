#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>
#include <spdlog/spdlog.h>
#include <fmt/core.h>

namespace beast = boost::beast;
namespace http  = beast::http;
namespace net   = boost::asio;
using tcp       = boost::asio::ip::tcp;