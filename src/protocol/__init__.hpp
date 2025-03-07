#ifndef DB_PIPE_INIT_HPP
#define DB_PIPE_INIT_HPP

#include <memory>
#include <functional>
#include <result.h>

namespace DB
{

class Channel
{
public:
    typedef std::shared_ptr<Channel> Ptr;

public:
    virtual ~Channel() = default;

public:
    /**
     * @brief Start channel.
     * @return 0 if success, string for error.
     */
    virtual Result<int, std::string> Start() = 0;

    /**
     * @brief Stop
     * @return 0 if success, string for error.
     */
    virtual Result<int, std::string> Stop() = 0;
};

} // namespace DB

#endif
