#include <gtest/gtest.h>
#include "Main/inc/ProgramOptions.h"

using namespace ::testing;
using namespace Main;

struct ProgramOptionsTest : public Test
{
};

TEST_F(ProgramOptionsTest, DefaultOptionsDontShowHelp)
{
  int argc = 1;
  char *args[] = {"program"};
  ProgramOptions po(argc, args);
  EXPECT_FALSE(po.isHelp());
}

TEST_F(ProgramOptionsTest, WithhOptionsPrintHelpShouldBeTrue)
{
  int argc = 2;
  char *args[] = {"program", "-h"};
  ProgramOptions po(argc, args);
  EXPECT_TRUE(po.isHelp());
}

TEST_F(ProgramOptionsTest, WithhelpOptionsPrintHelpShouldBeTrue)
{
  int argc = 2;
  char *args[] = {"program", "--help"};
  ProgramOptions po(argc, args);
  EXPECT_TRUE(po.isHelp());
}