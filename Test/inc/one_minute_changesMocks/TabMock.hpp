#include "one_minute_changes/inc/Tab.hpp"
#include <gmock/gmock.h>

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
  
}
}