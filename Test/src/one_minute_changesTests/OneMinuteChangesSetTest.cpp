#include "one_minute_changes/inc/OneMinuteChangesSet.hpp"
#include <gtest/gtest.h>

using namespace ::testing;
using OneMinuteChanges::OneMinuteChangesSet;

struct OneMinuteChangesSetTest : public Test
{
  OneMinuteChangesSet omcs;
  virtual void TearDown()
  {
    omcs.clear();
  }
};

TEST_F(OneMinuteChangesSetTest, ChangeCanBeAdded)
{
  
}
