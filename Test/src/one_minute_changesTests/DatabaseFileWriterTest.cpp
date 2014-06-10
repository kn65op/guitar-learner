#include "one_minute_changes/inc/DatabaseFileWriter.hpp"
#include "TabMock.hpp"
#include <gtest/gtest.h>

using namespace ::testing;
using Guitar::DatabaseFileWriterVer1;
using Guitar::Chord;
using Guitar::ut::TabMock;

struct DatabaseFileWriterTest : public Test
{
  void TearDown() override
  {
    Chord::clear();
  }
};

TEST_F(DatabaseFileWriterTest, WriterVer1ShouldWriteChordsToOStream)
{
  const std::string format_header = "Ver: 1\n";
  const std::string format_size = "2\n";
  const std::string format_chord1 = "A\n";
  const std::string format_tab1 = "tabformat1\n";
  const std::string format_chord2 = "B\n";
  const std::string format_tab2 = "tabformat2\n";
  
  const std::string format = format_header + format_size + format_chord1 + format_tab1 + format_chord2 + format_tab2;
  
  TabMock tab1;
  Chord::add("A", tab1);
  TabMock tab2;
  Chord::add("B", tab2);
  
  DatabaseFileWriterVer1 writer;
  std::stringstream oss;
  
  EXPECT_CALL(tab1, print()).WillOnce(Return(format_tab1));
  EXPECT_CALL(tab2, print()).WillOnce(Return(format_tab2));
  
  writer.write(Chord::getChords(), oss);
  EXPECT_EQ(format, oss.str());
}