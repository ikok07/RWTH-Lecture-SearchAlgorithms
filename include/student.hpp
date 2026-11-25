#ifndef INCLUDE_STUDENT
#define INCLUDE_STUDENT

#include <iostream>

class Student {
public:
  int id;
  std::string name;
  Student() = default;
  Student(int id, std::string name) : id(id), name(name) {}

  bool operator>(const Student &other) { return this->id > other.id; }
  bool operator<(const Student &other) { return this->id < other.id; }
  bool operator==(const Student &other) { return this->id == other.id; }

  friend std::ostream &operator<<(std::ostream &out, const Student &c) {
    out << c.id << " : " << c.name << std::endl;
    return out;
  };
};

#endif /* INCLUDE_STUDENT */
