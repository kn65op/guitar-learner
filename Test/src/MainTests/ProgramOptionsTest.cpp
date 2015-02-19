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
  const char *args[] = {"program"};
  ProgramOptions po(argc, args);
  EXPECT_FALSE(po.isHelp());
}

TEST_F(ProgramOptionsTest, WithhOptionsPrintHelpShouldBeTrue)
{
  int argc = 2;
  const char *args[] = {"program", "-h"};
  ProgramOptions po(argc, args);
  EXPECT_TRUE(po.isHelp());
}

TEST_F(ProgramOptionsTest, WithhelpOptionsPrintHelpShouldBeTrue)
{
  int argc = 2;
  const char *args[] = {"program", "--help"};
  ProgramOptions po(argc, args);
  EXPECT_TRUE(po.isHelp());
}

TEST_F(ProgramOptionsTest, HelpShouldRetunNotEmptyHelp)
{
  int argc = 1;
  const char *args[] = {"program"};
  ProgramOptions po(argc, args);
  EXPECT_NE("", po.help());
}

TEST_F(ProgramOptionsTest, ForUnrecognizedOptionPrintHelpShouldBeTrue)
{
  int argc = 2;
  const char *args[] = {"program", "--zzzzaaqqqqqhasd"};
  ProgramOptions po(argc, args);
  EXPECT_TRUE(po.isHelp());
}

TEST_F(ProgramOptionsTest, ForAddChordOptionGetCommandShouldReturnAddChordCommand)
{
  int argc = 2;
  const char *args[] = {"program", "--add_chord"};
  ProgramOptions po(argc, args);
  EXPECT_EQ(CommandType::AddChord, po.getCommand());
}

TEST_F(ProgramOptionsTest, ForListChordsOptionGetCommandShouldReturnListCommand)
{
  int argc = 2;
  const char *args[] = {"program", "--list_chords"};
  ProgramOptions po(argc, args);
  EXPECT_EQ(CommandType::ListChords, po.getCommand());
}

TEST_F(ProgramOptionsTest, ForChangeChordOptionGetCommandShouldReturnChangeChordCommand)
{
  int argc = 2;
  const char *args[] = {"program", "--change_chord"};
  ProgramOptions po(argc, args);
  EXPECT_EQ(CommandType::ChangeChord, po.getCommand());
}

TEST_F(ProgramOptionsTest, ForRemoveChordOptionGetCommandShouldReturnRemoveChordCommand)
{
  int argc = 2;
  const char *args[] = {"program", "--remove_chord"};
  ProgramOptions po(argc, args);
  EXPECT_EQ(CommandType::RemoveChord, po.getCommand());
}
