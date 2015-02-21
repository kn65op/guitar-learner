#include "../inc/Chord.hpp"

using Guitar::Chord;
using Guitar::ITab;
using Guitar::Tab;

Chord::Chords Chord::chords;

Chord::Chord(const ChordNameType & chord, const Tab &chord_tab) :
    name {chord} ,
    tab(chord_tab) { }

size_t Chord::size()
{
  return chords.size();
}

void Chord::add(const ChordNameType &name, const Tab &tab)
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

Chord::ChordNameType Chord::getName() const
{
  return name;
}

std::ostream& Guitar::operator<<(std::ostream &out, const Chord & chord)
{
  out << chord.getName() << "\n";
  out << chord.getTab();
  return out;
}

const Tab & Chord::getTab() const
{
  return tab;
}

const Chord& Chord::getChord(const ChordNameType &name)
{
  try
  {
    return chords.at(name);
  }
  catch (std::out_of_range &)
  {
    throw NotExist {name};
  }
}

void Chord::changeChords(const ChordNameType &name, const Tab &tab)
{
  try
  {
    chords.at(name) = Chord {name, tab};
  }
  catch (std::out_of_range &)
  {
    throw NotExist {name};
  }
}

void Chord::removeChord(const ChordNameType &name)
{
  if (!chords.erase(name))
  {
    throw NotExist{name};
  }
}