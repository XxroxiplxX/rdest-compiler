#include <string>
enum type_of_value {
    _NUM = 1,
    _ID = 2
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