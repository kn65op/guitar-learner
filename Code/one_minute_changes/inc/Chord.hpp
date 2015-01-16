#ifndef CHORD_H
#define CHORD_H

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
  
  static size_t size();
  static void add(const std::string &name, const Tab & tab);
  static const Chords& getChords();
  static void clear();
  
  Chord() = delete;
  std::string getName() const;
  const ITab& getTab() const;
private:
  Chord(const std::string & chord, const Tab &tab);
  
  static Chords chords;
  
  ChordNameType name;
  Tab tab;
};

std::ostream& operator<<(std::ostream &out, const Chord & chord);

}

#endif // CHORD_H
