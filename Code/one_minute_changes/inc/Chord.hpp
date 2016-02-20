#pragma once

#include <string>
#include <map>
#include <stdexcept>
#include "Tab.hpp"

namespace Guitar
{

class Chord
{
public:
  typedef std::string ChordNameType;
  typedef std::map<ChordNameType, Chord> Chords;

  class AlreadyAdded
  {
  };
  class NotExist : public std::logic_error
  {
  public:
    NotExist(const ChordNameType &name) : std::logic_error("There is no chord: " + name)
    {
    }
  };

  static size_t size();
  static void add(const ChordNameType &name, const Tab &tab);
  static const Chords& getChords();
  static void clear();
  static void changeChords(const ChordNameType &name, const Tab &tab);
  static const Chord& getChord(const ChordNameType &name);
  static void removeChord(const ChordNameType &name);
  static bool exists(const ChordNameType &name);

  Chord() = delete;
  ChordNameType getName() const;
  const Tab& getTab() const;
private:
  Chord(const ChordNameType & chord, const Tab &tab);

  static Chords chords;

  ChordNameType name;
  Tab tab;
};

std::ostream& operator<<(std::ostream &out, const Chord & chord);

}
