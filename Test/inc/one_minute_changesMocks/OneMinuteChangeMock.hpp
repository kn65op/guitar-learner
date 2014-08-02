#pragma once

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"

#include <gmock/gmock.h>
#include "one_minute_changes/inc/OneMinuteChange.hpp"

namespace OneMinuteChanges
{
namespace ut
{
class OneMinuteChangeMock : public IOneMinuteChange {
 public:
  MOCK_METHOD1(addResult,
      void(int result));
  MOCK_CONST_METHOD0(bestResult,
      int());
  MOCK_CONST_METHOD0(lastResult,
      int());
  MOCK_CONST_METHOD0(getResults,
      const Results&());
};

#pragma GCC diagnostic pop
}
}