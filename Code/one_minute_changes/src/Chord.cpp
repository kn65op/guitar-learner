#include "../inc/Chord.hpp"

using Guitar::Chord;
using Guitar::ITab;
using Guitar::Tab;

Chord::Chords Chord::chords;

Chord::Chord(const std::string & chord, const Tab &chord_tab) :
    name
{
  chord
}
,
tab(chord_tab) { }

size_t Chord::size()
{
  return chords.size();
}

void Chord::add(const std::string &name, const Tab &tab)
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

std::ostream& Guitar::operator<<(std::ostream &out, const Chord & chord)
{
  out << chord.getName() << "\n";
  out << chord.getTab();
  return out;
}

const ITab & Chord::getTab() const
{
  return tab;
}