

struct EdgeProvider {
        int _begin_id;
        int _end_id;
        int get_begin_id() {
                return _begin_id;
        }
        void set_begin_id(int to_set) {
                _begin_id = to_set;
        }

        int get_end_id() {
                return _end_id;
        }
        void set_end_id(int to_set) {
                _end_id = to_set;
        }
};