#include "pliib.hpp"

int main(){
    std::vector<int> x;
    x.push_back(4);
    x.push_back(3);
    x.push_back(2);
    x.push_back(1);

    std::function<int(int)> zed = [](int z){ return (int) z * z; }; 
    std::vector<int> ret = p_vv_map(x, zed);
    return 0;
}
