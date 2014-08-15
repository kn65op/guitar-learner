#include "one_minute_changes/inc/DatabaseFileWriterVer1.hpp"
#include <one_minute_changes/inc/OneMinuteChangesSet.hpp>
#include "TabMock.hpp"
#include <OneMinuteChangeMock.hpp>
#include <gtest/gtest.h>

using namespace ::testing;
using Guitar::DatabaseFileWriterVer1;
using Guitar::Chord;
using Guitar::ut::TabMock;
using OneMinuteChanges::ut::OneMinuteChangeMock;
using OneMinuteChanges::OneMinuteChangesSet;

struct DatabaseFileWriterVer1Test : public Test
{
  OneMinuteChanges::OneMinuteChangesSet omcs;
  
  void TearDown() override
  {
    Chord::clear();
    omcs.clear();
  }
};

TEST_F(DatabaseFileWriterVer1Test, WriterVer1ShouldWriteChordsAndChangesToOStream)
{
  const std::string format_header = "Ver: 1\n";
  const std::string format_chord_size = "2\n";
  const std::string format_chord1 = "A\n";
  const std::string format_tab1 = "tabformat1\n";
  const std::string format_chord2 = "B\n";
  const std::string format_tab2 = "tabformat2\n";
  const std::string format_changes_size = "2\n";
  const std::string format_change1 = "Change1\n";
  const std::string format_change2 = "Change2\n";
  
  const std::string format = format_header + format_chord_size + format_chord1 + format_tab1 + format_chord2 + format_tab2 + format_changes_size + format_change1 + format_change2;
  
  TabMock tab1;
  Chord::add("A", tab1);
  TabMock tab2;
  Chord::add("B", tab2);
  
  OneMinuteChangeMock *omc1Mock = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omc1{omc1Mock};
  OneMinuteChangeMock *omc2Mock = new OneMinuteChangeMock();
  OneMinuteChangesSet::Element omc2{omc2Mock};
  omcs.add(omc1);
  omcs.add(omc2);
  
  DatabaseFileWriterVer1 writer;
  std::stringstream oss;
  
  EXPECT_CALL(tab1, print()).WillOnce(Return(format_tab1));
  EXPECT_CALL(tab2, print()).WillOnce(Return(format_tab2));
  EXPECT_CALL(*omc1Mock, print()).WillOnce(Return(format_change1));
  EXPECT_CALL(*omc2Mock, print()).WillOnce(Return(format_change2));
  
  writer.write(Chord::getChords(), omcs, oss);
  EXPECT_EQ(format, oss.str());
}
