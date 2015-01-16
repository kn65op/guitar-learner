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
}

class OneMinuteChangesSet
{
public:
  typedef std::shared_ptr<IOneMinuteChange> Element;
  typedef std::set<Element> SetType;
  typedef SetType::size_type size_type;

  OneMinuteChangesSet();
  OneMinuteChangesSet(std::istream & in);

  void clear() noexcept;
  void add(Element omcMock);
  size_type size() const noexcept;

  Element findWorstChord() const;
  Element findLastWorstChord() const;
  std::string print() const;

private:
  typedef SetType::iterator SetIterator;
  static SetType changes;
};

}

#endif // ONEMINUTECHANGESSET_H
