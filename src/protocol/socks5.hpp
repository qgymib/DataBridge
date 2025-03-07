#ifndef DB_PROTOCOL_SOCKS5_HPP
#define DB_PROTOCOL_SOCKS5_HPP

#include <string>
#include <memory>
#include <result.h>
#include "__init__.hpp"

namespace DB
{

class Socks5 : public Channel
{
public:
    struct Option
    {
        Option();

        int         port;
        std::string addr;
        std::string username;
        std::string password;
    };

public:
    explicit Socks5(const Option& option);
    ~Socks5() override;

public:
    Result<int, std::string> Start() override;
    Result<int, std::string> Stop() override;

private:
    struct Data;
    Data* m_data = nullptr;
};

} // namespace DB

#endif // DB_PROTOCOL_SOCKS5_HPP
