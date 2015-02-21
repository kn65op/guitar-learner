#pragma once

#include <string>
#include <map>
#include "Tab.hpp"

namespace Guitar
{

class Chord
{
public:
  typedef std::string ChordNameType;
  typedef std::map<std::string, Chord> Chords;

  class AlreadyAdded
  {
  };
  class NotExist
  {
    ChordNameType chord;
  public:
    NotExist(const ChordNameType &name) :
        chord(name)
    {
    }
    ChordNameType getChord() const noexcept
    {
      return chord;
    }
  };

  static size_t size();
  static void add(const std::string &name, const Tab &tab);
  static const Chords& getChords();
  static void clear();
  static void changeChords(const std::string &name, const Tab &tab);
  static const Chord& getChord(const std::string &name);

  Chord() = delete;
  std::string getName() const;
  const Tab& getTab() const;
private:
  Chord(const std::string & chord, const Tab &tab);

  static Chords chords;

  ChordNameType name;
  Tab tab;
};

std::ostream& operator<<(std::ostream &out, const Chord & chord);

}
