#ifndef TAB_H
#define TAB_H

#include <ostream>
#include <array>

namespace Guitar
{
  
class ITab
{
};

class Tab : public ITab
{
public:
  Tab();
  explicit Tab(int fret1, int fret2, int fret3, int fret4, int fret5, int fret6);
private:
  friend std::ostream & operator<<(std::ostream & out, const Tab &tab);
  
  std::array<int, 6> frets;
};

std::ostream & operator<<(std::ostream & out, const Tab &tab);

}

#endif // TAB_H
