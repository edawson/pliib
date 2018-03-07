#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <cstring>
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
 *
 */
//template <typename DataType, typename A>
//std::vector<DataType, A> p_vv_map( std::vector<DataType, A> v, typename std::function<DataType(DataType)> lambda);


    // Crazy hack char table to test for canonical bases
    static const int valid_dna[127] = {
        1,
        1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,1,1,1,1,1,1,
        1,1,1,1,0,1,0,1,1,1,
        0,1,1,1,1,1,1,1,1,1,
        1,1,1,0,1,1,1,1,1,1,
        1,1,1,1,1,1,0,1,0,1,
        1,1,0,1,1,1,1,1,1,1,
        1,1,1,1,1,0,1,1,1,1,
        1,1,1,1,1,1
    };

    // Reverse complement lookup table
    static char complement_array [26] = {
        84, 66, 71, 68, 69,
        70, 67, 72, 73, 74,
        75, 76, 77, 78, 79,
        80, 81, 82, 83, 65,
        85, 86, 87, 88, 89, 90
    };


    // Check a string (as a char*) for non-canonical DNA bases
    inline bool canonical(const char* x, int len){
        bool trip = false;
        for (int i = 0; i < len; ++i){
            trip |= valid_dna[x[i]];
        }
        return !trip;
    };

    inline bool canonical(string seq){
        const char* x = seq.c_str();
        int len = seq.length();
        return canonical(x, len);
    };


inline void reverse_complement(const char* seq, char* ret, int len){
    for (int i = len - 1; i >=0; i--){
        ret[ len - 1 - i ] = (char) complement_array[ (int) seq[i] - 65];
    }
}

inline char base_complement(char c){
    return (char) complement_array[ (int) c - 65];    
}

/* Capitalize all characters in a string */
    /* Capitalize a C string */
    inline void to_upper(char* seq, int length){
        for (int i = 0; i < length; i++){
            char c = seq[i];
            seq[i] = ( (c - 91) > 0 ? c - 32 : c);
        }
    };

    /* Capitalize a string */
    inline string to_upper(string& seq){
        for (int i = 0; i < seq.length(); i++){
            char c = seq[i];
            seq[i] =  ((c - 91) > 0 ? c - 32 : c);
        }
        return seq;
    };

inline void countChar(const char* s, char c, int& ret) {
    ret = 0;
    while(*s++ != '\0') { //Until the end of the string
        if(*s == c) {
            ++ret;
        }
    }
};

// Modified from: https://techoverflow.net/2017/01/23/zero-copy-in-place-string-splitting-in-c/
inline void split(char* s, char delimiter, char**& ret, int& retsize, int* split_sizes){
    int num_delim = 0;
    countChar(s, delimiter, num_delim);

    ret = new char*[num_delim + 1];
    retsize = num_delim + 1;

    ret[0] = s;

    int i = 1;
    char* hit = s;
    while((hit = strchr(hit, delimiter)) != NULL){
        *hit = '\0';
        ++hit;
        
        ret[i++] = hit;
        // Save the length of each string as well.
        *(split_sizes + (i - 1)) = strlen(ret[i - 1]); 
    }
};

inline void split(string s, char delim, vector<string>& ret){
    
    int slen = s.length();
    char s_to_split[slen + 1];
    strcpy(s_to_split, s.c_str());

    char** splitret;
    int retsz;
    int* splitsz;


    split(s_to_split, delim, splitret, retsz, splitsz);
    ret.resize(retsz);

    for (int i = 0; i < retsz; ++i){
        ret[i].assign(string( splitret[i])); 
    }

};


inline vector<string> slow_split(string s, char delim){
    vector<string> ret;
    stringstream sstream(s);
    string temp;
    while(getline(sstream, temp, delim)){
        ret.push_back(temp);
    }
    return ret;

}

inline string join(vector<string> splits, string glue){
    string ret = "";
    for (int i = 0; i < splits.size(); i++){
        if (i != 0){
            ret += glue;
        }
        ret += splits[i];
    }

    return ret;
}

template <typename DataType, typename A>
inline std::vector<DataType, A> p_vv_map(std::vector<DataType, A> v, typename std::function<DataType(DataType)> lambda){
    std::vector<DataType> results(v.size());
    int i;
    // As we guarantee synchronicity,
    //     // we should TODO something to guarantee it.
#pragma omp parallel for
    for (i = 0; i < v.size(); i++){
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
    int i;
    cerr << "Asynchronous map is currently broken" << endl;
    exit(-1);
    for (i = 0; i < v.size(); i++){
#pragma omp task 
        {results[i] = lambda(v[i]);}
    }

    return results;

}


/**
 * This function applies a lambda function L to all elements of
 * vector v, modifying the elements of v in place.
 */
template<typename DataType, typename A>
inline void p_vv_apply(std::vector<DataType, A> &v, typename std::function<DataType(DataType)> lambda){
#pragma omp parallel for //private(i)
    for (int i = 0; i < v.size(); i++){
        auto r = lambda(v[i]);

#pragma omp atomic write
        v[i] = r;
    }
}


/**
 * Takes a lambda function and applies it across v, then reduces the result
 * to a single <T> value.
 */
template<typename DataType, typename A>
inline DataType p_vv_reduce(std::vector<DataType, A> v, typename std::function<DataType(DataType)> lambda){
    cerr << "reduce is not yet implemented" << endl; exit(1);
    DataType x;
    return x;
}


/**
 * Applies a bool std::function L across elements in a vector.
 * All elements for which L returns true are return in a new vector.
 */
template<typename DataType, typename A>
std::vector<DataType, A> p_vv_filter(std::vector<DataType, A> v, typename std::function<bool(DataType)> lambda){
    std::vector<DataType, A> results;
    cerr << "p_vv_filter not implemented" << endl;
    exit(-1);
#pragma omp parallel for if (v.size() > 1000)
    for (int i = 0; i < v.size(); i++){
        if (lambda(v[i])){
#pragma omp critical
            results.push_back(v[i]);
        }
    }
    return results;
}


