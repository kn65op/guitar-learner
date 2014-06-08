#include "../inc/Chord.hpp"

using Guitar::Chord;
using Guitar::ITab;

Chord::Chords Chord::chords;

Chord::Chord(const std::string & chord, const ITab &tab) :
  name{chord}
{
}

size_t Chord::size()
{
  return chords.size();
}

void Chord::add(const std::string &name, const ITab &tab)
{
  if (chords.find(name) != chords.end())
  {
    throw AlreadyAdded();
  }
  chords.insert(std::make_pair(name, Chord{name, tab}));
}

const Chord::Chords& Chord::getChords()
{
  return chords;
}

void Chord::clear()
{
  chords.clear();
}

std::string Chord::getName() const
{
  return name;
}