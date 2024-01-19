

#ifndef RDEST_COMPILER_EDGEPROVIDER_H
#define RDEST_COMPILER_EDGEPROVIDER_H
namespace ast::providers {

class EdgeProvider {
  int _begin_id;
  int _end_id;

public:
  int get_begin_id() const;
  void set_begin_id(int to_set);
  int get_end_id() const;
  void set_end_id(int to_set);
};
} // namespace ast::providers
#endif // RDEST_COMPILER_EDGEPROVIDER_H
