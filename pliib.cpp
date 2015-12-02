#include "pliib.hpp"

template <typename T, typename A>
std::vector<T, A> p_vv_map(const std::vector<T, A>& v, std::function lambda){
    std::vector<T, A> results(v.size());
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

