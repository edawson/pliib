#include <iostream>
#include <list>
#include <vector>
#include <functional>
#include <omp.h>
#include <functional>

using namespace std;
/**
 * This function takes a vector v and applies a lambda
 * function L to each of its elements. It returns a vector v'
 * of |v| where v'[i] = L(v[i]). It computes results synchronously
 * (i.e. v'[1] is computed before [v'2].
 */
//template <typename DataType, typename A>
//std::vector<DataType, A> p_vv_map( std::vector<DataType, A> v, typename std::function<DataType(DataType)> lambda);

template <typename DataType, typename A>
inline std::vector<DataType, A> p_vv_map(std::vector<DataType, A> v, typename std::function<DataType(DataType)> lambda){
    std::vector<DataType> results(v.size());
    int i;
    // As we guarantee synchronicity,
    //     // we should TODO something to guarantee it.
    //#pragma omp parallel for
    for (i = 0; i < v.size(); i++){
        #pragma omp task
        auto r = lambda(v[i]);
        //#pragma omp critical
        results[i] = r;
    }
    return results;
}


/**
 * This function follows the same pattern as above but permits asynchronous
 * computation (i.e. there is not guarantee that v'[1] is computed before v'[2].
 */
template <typename DataType, typename A>
inline std::vector<DataType, A> p_vv_map_async(std::vector<DataType, A> v, typename std::function<DataType(DataType)> lambda){
    std::vector<DataType, A> results(v.size());
    
    return results;

}


/**
 * This function applies a lambda function L to all elements of
 * vector v, modifying the elements of v in place.
 */
//void p_vv_apply(std::vector<T> v, std::function lambda);


/**
 * Takes a lambda function and applies it across v, then reduces the result
 * to a single <T> value.
 */
//<T> p_v_reduce(std::vector<T> v, std::function lambda);


/**
 * Applies a bool std::function L across elements in a vector.
 * All elements for which L returns true are return in a new vector.
 */
//std::vector<T> p_vv_filter(std::vector<T> v, std::function lambda);


