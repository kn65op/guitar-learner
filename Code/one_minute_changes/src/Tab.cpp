#include "../inc/Tab.hpp"

#include <string>

using Guitar::Tab;

Tab::Tab() :
  frets{0, 0, 0, 0, 0, 0}
{
}

Tab::Tab(int fret1, int fret2, int fret3, int fret4, int fret5, int fret6) :
  frets{fret1, fret2, fret3, fret4, fret5, fret6}
{
}

Tab::Tab(std::istream & in) :Tab()
{
  parseInputStream(in);
}

std::string headerString(int n = 10)
{
  return "    1   2   3   4   5   6   7   8   9  10 \n";
}

std::string stringString(const std::string & string, int pos, int n = 10)
{
  static const std::string emptyFret = "|---";
  static const std::string pushedFret = "|-0-";
  static const std::string silentFret = "|-X-";
  std::string ret = string;
  ret += " ";
  if (pos == -1)
  {
    ret += silentFret;
    for (int i = 1; i < n; ++i)
    {
      ret += emptyFret;
    }
  }
  else
  {
    for (int i = 1; i < n + 1; ++i)
    {
      if (pos == i)
      {
        ret += pushedFret;
      }
      else
      {
        ret += emptyFret;
      }
    }
  }
  return ret + "\n";;
}

std::ostream & Guitar::operator<<(std::ostream & out, const ITab &tab)
{
  out << tab.print();
  return out;
}

std::string Tab::print() const
{
  return headerString()
    + stringString("E", frets[0])
    + stringString("H", frets[1])
    + stringString("G", frets[2])
    + stringString("D", frets[3])
    + stringString("A", frets[4])
    + stringString("E", frets[5]);
}

void Tab::parseInputStream(std::istream & in)
{
  std::string line;
  std::getline(in, line);
  std::string::size_type num_start = line.rfind(' ', line.size() - 2);
  int frets_count = std::atoi(line.substr(num_start).c_str());
  
  for (size_t string = 0; string < frets.size(); ++string)
  {
    std::getline(in, line);
    const std::streamoff string_header_size = 2;
    const int fret_size = 4;
    for (int i = 1; i < frets_count + 1; ++i)
    {
      std::string fret = line.substr(string_header_size + (i - 1) * fret_size, fret_size);
      if (fret[2] == 'X')
      {
        frets[string] = -1;
        break;
      }
      else if (fret[2] == '0')
      {
        frets[string] = i;
        break;
      }
    }
  }
}