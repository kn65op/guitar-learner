#ifndef ONEMINUTECHANGESSET_H
#define ONEMINUTECHANGESSET_H

#include "OneMinuteChange.hpp"
#include <set>
#include <memory>
#include <istream>

namespace OneMinuteChanges
{

namespace Exceptions
{

struct NoElements
{
};

struct NoChangeFound
{
};

}

class OneMinuteChangesSet
{
public:
  typedef std::shared_ptr<IOneMinuteChange> Element;
  typedef std::vector<Element> ContainerType;
  typedef ContainerType::size_type size_type;

  OneMinuteChangesSet();
  OneMinuteChangesSet(std::istream & in);

  void clear() noexcept;
  void add(Element omc);
  void removeAllContainingChord(const Guitar::Chord::ChordNameType &chord);
  size_type size() const noexcept;

  Element findWorstChord() const;
  Element findLastWorstChord() const;
  Element getChange(const Guitar::Chord::ChordNameType &first_chord,
                    const Guitar::Chord::ChordNameType &second_chord) const;
  std::string print() const;

private:
  typedef ContainerType::iterator SetIterator;
  static ContainerType changes;
};

}

#endif // ONEMINUTECHANGESSET_H
