#include "pliib.hpp"

std::vector<typename T> p_vv_map(const std::vector<typename T>& v, std::function lambda){
    std::vector<typename T> results(v.size());
    int i;
    // As we guarantee synchronicity,
    // we should TODO something to guarantee it.
    #pragma omp for
    for (i = 0; i < v.size(); i++){
        auto r = lambda(v[i]);
        #pragma omp critical
        results[i] = r;
    }
    return results;
}

