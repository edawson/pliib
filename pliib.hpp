#include <iostream>
#include <list>
#include <vector>
#include <omp.h>
#include <functional>

/**
 * This function takes a vector v and applies a lambda
 * function L to each of its elements. It returns a vector v'
 * of |v| where v'[i] = L(v[i]). It computes results synchronously
 * (i.e. v'[1] is computed before [v'2].
 */
template <typename T, typename A>
std::vector<T, A> p_vv_map(const std::vector<T, A>& v, std::function<T(T)> lambda);

//template <typename T, typename U> T<U> p_tt_map(T<U> v, std::function lambda);
/**
 * This function follows the same pattern as above but permits asynchronous
 * computation (i.e. there is not guarantee that v'[1] is computed before v'[2].
 */
//std::vector<T> p_vv_map_async(std::vector<T> v, std::function lamda);

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


