//header for tuples
#include <iostream>
#include <vector>
#include <string>

class Scheme {

private:

  std::vector<std::string> names;


public:

  Scheme(std::vector<std::string> names) : names(names) { } 

  Scheme() {}

  size_t size() const {
    return names.size();
  }

  const std::string& at(int index) const {
    return names.at(index); 
  }

  const std::vector<std::string>& getNames() const {
    return names;
  }

  void addName(const std::string& name) {
    names.push_back(name);
  }

};
