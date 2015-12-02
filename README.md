pliib: A hacky little C++ library for replicating Python's multiprocessing functions and doing things in parallel.
-------
Eric T Dawson  
December 2015

### What is pliib?
Pliib (pronounced like "plebe") is a library that contains C++ mirrors of
Python's multiprocessing library functions. Things like Pools, parallel maps,
parallel filters, parallel applies and such are all going to be included now
or in the future.


### Why would anyone write this?  
Mostly for practice, but pliib is also pretty useful. It allows you to use
multithreading without a lot of work. It's kind of like a C++ version of 
(LaunChair){https://github.com/edawson/LaunChair} in that it encapsulates
an existing threading framework (in this case, OpenMP) to prevent the end
user from having to worry about the details.

### Why would anyone use this?  
Pliib's pretty useful if you're a really lazy programmer. You can use
thread-pool style constructs instead of writing your own OpenMP code. If
you already know a lot about OpenMP you can probably roll your own solution,
but pliib is pretty awesome if you just need a quick and dirty way to do
some basic tasks.

### Who unleashed this on the world?
Eric T Dawson  
Bugs, comments, PRs, issues: (edawson){https://github.com/edawson}
