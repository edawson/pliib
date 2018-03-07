pliib: Some common C++ utility functions for bioinformatics
-------
Eric T Dawson  
December 2015

### Functionality
There are two main kinds of functions in this library:  
  - String manipulation  
    - Capitalize a string  
    - Reverse a string  
    - Reverse compliment a string  
    - Split a string by a delimiter  
    - Join a vector of strings by a delimiter  

  - Threadpool-style work functions  
    - Apply a function to a vector of inputs

### Example Usage:
    
            #include "pliib.hpp"
            using namespace pliib;

            // Split a string:
            string s = "ACT;TGC;AAA;aNoThErString;"
            vector<string> ret;
            split(s, ';', ret);
            // ret is modified to hold the tokens of s split by semicolons.
            // ret = {"ACT", "TGC", "AAA", "aNoThErString"}


## License:
MIT

### Contact:
Eric T Dawson  
github: edawson
