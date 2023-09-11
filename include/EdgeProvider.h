#ifndef COMPILER_EDGEPROVIDER
#define COMPILER_EDGEPROVIDER



#include <vector>

struct EdgeProvider {
  int _begin_id;
  int _end_id;
  int get_begin_id() { return _begin_id; }
  EdgeProvider &set_begin_id(int to_set) {
    _begin_id = to_set;
    return *this;
  }

  int get_end_id() { return _end_id; }
  EdgeProvider &set_end_id(int to_set) {
    _end_id = to_set;
    return *this;
  }
};

class TreeConfigurationProvider {
  std::vector<EdgeProvider> providers_vector;

public:
  void addConfiguration(EdgeProvider edgeProvider) {
    providers_vector.push_back(edgeProvider);
  }
};

#endif