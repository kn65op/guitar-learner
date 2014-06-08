#include "one_minute_changes/inc/Chord.hpp"
#include "TabMock.hpp"
#include <gtest/gtest.h>

using namespace ::testing;
using Guitar::Chord;
using Guitar::ut::TabMock;

struct ChordTest : public Test
{
  void TearDown() override
  {
    Chord::clear();
  }
};

TEST_F(ChordTest, ChordListShouldBeEmptyAtStart)
{
  EXPECT_EQ(Chord::size(), 0);
}

TEST_F(ChordTest, AfterChordAdditionShouldHaveOneElement)
{
  TabMock tab;
  Chord::add("A", tab);
  EXPECT_EQ(1, Chord::size());
}

TEST_F(ChordTest, AfterClearChordsShouldBeEmpty)
{
  TabMock tab;
  Chord::add("A", tab);
  ASSERT_EQ(1, Chord::size());
  Chord::clear();
  EXPECT_EQ(0, Chord::size());
}
  

TEST_F(ChordTest, GetChordsShouldReturnAddedChords)
{
  TabMock tab;
  Chord::add("A", tab);
  Chord::add("B", tab);
  ASSERT_EQ(2, Chord::size());
  
  Chord::Chords chords = Chord::getChords();
  EXPECT_EQ("A", chords.at("A").getName()); 
  EXPECT_EQ("B", chords.at("B").getName()); 
}

TEST_F(ChordTest, AddingAlreadyAddedChordShouldThrow)
{
  TabMock tab;
  Chord::add("A", tab);
  ASSERT_THROW(Chord::add("A", tab), Chord::AlreadyAdded);
}
