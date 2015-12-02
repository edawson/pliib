#include "pliib.hpp"

int main(){
    std::vector<int> x;
    x.push_back(4);
    x.push_back(3);
    x.push_back(2);
    x.push_back(1);

    std::vector<int> ret = p_vv_map(x, [](int zed){
        return zed * zed;
            };);
    return 0;
}
