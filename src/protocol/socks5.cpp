#include <wx/wx.h>
#include <wx/socket.h>
#include "socks5.hpp"

struct DB::Socks5::Data
{
    explicit Data(const Socks5::Option& option);
    ~Data();

    Result<int, std::string> Start();
    Result<int, std::string> Stop();

    Option          option;
    wxSocketServer* server;
};

DB::Socks5::Option::Option()
{
    port = 1080;
    addr = "0.0.0.0";
}

DB::Socks5::Data::Data(const Socks5::Option& option)
{
    this->option = option;
    server = nullptr;
}

DB::Socks5::Data::~Data()
{
    if (server != nullptr)
    {
        delete server;
        server = nullptr;
    }
}

Result<int, std::string> DB::Socks5::Data::Start()
{
    if (server != nullptr)
    {
        return Err(_("Server already started").utf8_string());
    }

    wxIPV4address addr;
    addr.Hostname(wxString::FromUTF8(option.addr));
    addr.Service(option.port);
    server = new wxSocketServer(addr);

    if (server->IsOk())
    {
        return Ok(0);
    }

    const auto e = wxString::Format(_("Cannot bind to address %s:%d"), option.addr.c_str(), option.port);
    return Err(e.utf8_string());
}

Result<int, std::string> DB::Socks5::Data::Stop()
{
    if (server == nullptr)
    {
        return Err(_("Server not started").utf8_string());
    }

    delete server;
    server = nullptr;

    return Ok(0);
}

DB::Socks5::Socks5(const Option& option)
{
    m_data = new Data(option);
}

DB::Socks5::~Socks5()
{
    delete m_data;
}

Result<int, std::string> DB::Socks5::Start()
{
    return m_data->Start();
}

Result<int, std::string> DB::Socks5::Stop()
{
    return m_data->Stop();
}
