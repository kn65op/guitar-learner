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
  typedef std::map<std::string, Chord> Chords;
  class AlreadyAdded
  {
  };
  
  static size_t size();
  static void add(const std::string &name, const ITab & tab);
  static const Chords& getChords();
  static void clear();
  
  Chord() = delete;
  std::string getName() const;
private:
  Chord(const std::string & chord, const ITab &tab);
  
  static Chords chords;
  
  std::string name;
};

}

#endif // CHORD_H
