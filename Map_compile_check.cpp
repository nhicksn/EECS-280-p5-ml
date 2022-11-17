// Project UID db1f506d06d84ab787baf250c265e24e

#include <string>
#include <iostream>
#include "Map.h"

using namespace std;

class Duck {
public:
  Duck() : wealth(0) {} // tree requires default-constructible
  Duck(int wealth_in) : wealth(wealth_in) {}
  int getWealth() const { return wealth; }

private:
  int wealth;

};

class DuckWealthLess {
public:
  bool operator() (const Duck &d1, const Duck &d2) const {
    return d1.getWealth() < d2.getWealth();
  }

};

ostream &operator<<(ostream &os, const Duck &duck) {
  return os << "Duck: $" << duck.getWealth();
}

int main() {
  cout << "This test doesn't do anything interesting." << endl;
  cout << "It is just here to check for compilation issues." << endl;

  Map<string, int> map;
  cout << "test 1" << endl;
  const Map<string, int> &const_map = map;
  cout << "test 2" << endl;

  Map<Duck, string, DuckWealthLess> duck_map;
  cout << "test 3" << endl;
  const Map<Duck, string, DuckWealthLess> &const_duck_map = duck_map;
  cout << "test 4" << endl;

  // Dummy variables
  bool b;
  size_t st;

  // Dummy iterators - should be default constructible as end iterator
  Map<string, int>::Iterator it;
  cout << "test 5" << endl;
  Map<Duck, string, DuckWealthLess>::Iterator duck_it;
  cout << "test 6" << endl;

  // Big Three
  auto map_copy(const_map);
  cout << "test 7" << endl;
  auto duck_map_copy(const_duck_map);
  cout << "test 8" << endl;

  map_copy = const_map;
  cout << "test 9" << endl;
  duck_map_copy = const_duck_map;
  cout << "test 10" << endl;

  // destructor tested implicitly at end of function



  // Functions that can be applied to a const map
  b = const_map.empty();
  cout << "test 11" << endl;
  b = const_duck_map.empty();
  cout << "test 12" << endl;

  st = const_map.size();
  cout << "test 13" << endl;
  st = const_duck_map.size();
  cout << "test 14" << endl;

  it = const_map.begin();
  cout << "test 15" << endl;
  duck_it = const_duck_map.begin();
  cout << "test 16" << endl;

  it = const_map.end();
  cout << "test 17" << endl;
  duck_it = const_duck_map.end();
  cout << "test 18" << endl;

  it = const_map.find("");
  cout << "test 19" << endl;
  duck_it = const_duck_map.find(Duck());
  cout << "test 20" << endl;



  // Functions that can't be called on a const tree
  it = map.insert({"", 1}).first;
  cout << "test 21" << endl;
  b = map.insert({"quack", 2}).second;
  cout << "test 22" << endl;
  duck_it = duck_map.insert({Duck(), "Donald"}).first;
  cout << "test 23" << endl;
  b = duck_map.insert({Duck(1000000), "Scrooge"}).second;
  cout << "test 24" << endl;

  int &x = map["wat"];
  cout << x << endl;
  string &x2 = duck_map[Duck(-200)];
  cout << x2 << endl;

  // Using iterators

  it = map.begin();
  duck_it = duck_map.begin();

  (*it).second = 200;
  (*duck_it).second = "another duck name";

  ++++it;
  ++++duck_it;

  it = it++;
  duck_it = duck_it++;

  b = map.end() == map.end();
  b = duck_map.end() == duck_map.end();

  b = map.end() != map.end();
  b = duck_map.end() != duck_map.end();

  const auto &const_it = it;
  const auto &const_duck_it = duck_it;

  Map<string, int>::Iterator it_copy(const_it);
  Map<Duck, string, DuckWealthLess>::Iterator duck_it_copy(const_duck_it);

  cout << (*it_copy).first << (*duck_it_copy).second << endl;

  cout << b << st << endl;

}
