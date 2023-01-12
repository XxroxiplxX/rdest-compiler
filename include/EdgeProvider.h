#include <vector>

struct EdgeProvider {
        int _begin_id;
        std::vector<int> _end_ids;
        int get_begin_id() {
                return _begin_id;
        }
        void set_begin_id(int to_set) {
                _begin_id = to_set;
        }
};