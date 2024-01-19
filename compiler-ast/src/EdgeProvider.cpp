#include "EdgeProvider.h"

namespace ast::providers {
int EdgeProvider::get_begin_id() const { return _begin_id; }
void EdgeProvider::set_begin_id(int to_set) { _begin_id = to_set; }

int EdgeProvider::get_end_id() const { return _end_id; }
void EdgeProvider::set_end_id(int to_set) { _end_id = to_set; }
} // namespace ast::providers