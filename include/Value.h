#include <string>
#include <map>
enum type_of_value {
    _NUM = 1,
    _ID = 2
};
enum state {
    _DECL,
    _INIT,
};

struct Value {
    int type;
    std::string load;
    Value(std::string _load) {
        if (_load[0] == 'I') {
            type = type_of_value::_ID;
            for (int i = 3; i < _load.length(); i++) {
                load += _load[i];
            }
        } else {
            type = type_of_value::_NUM;
            for (int i = 4; i < _load.length(); i++) {
                load += _load[i];
            }
        }
    }
};
struct ValueTracer {
    std::map<Value*, std::string> id_tracer;
    void resolve_ranges(std::string proc_id) {
        for (auto node : id_tracer) {
            if (node.second == "tmp") {
                node.second = proc_id;
            }
        }
    }
};