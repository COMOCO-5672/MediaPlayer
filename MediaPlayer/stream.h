#include "stream_base.h"

class stream
{
private:
    /* data */
public:
    stream();
    ~stream();

    bool openByUrl(const std::string url);
};
