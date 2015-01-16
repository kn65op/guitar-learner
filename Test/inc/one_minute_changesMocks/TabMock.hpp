#include "one_minute_changes/inc/Tab.hpp"
#include <gmock/gmock.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

namespace Guitar
{
namespace ut
{

class TabMock : public ITab
{
public:
  MOCK_CONST_METHOD0(print,
                     std::string());
};

#pragma GCC diagnostic pop
}
}