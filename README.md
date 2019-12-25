# cutils

A repo for various utilities in c.

So far we just have some generic containers using macros (and gnu extensions)

## lessons learned (generic containers)

I'm not sure when I'll touch this again, so I'm going to record some things
I learned. The most peculiar thing, was the motivation for references in
c++. I found one of the benefits of writing macros was that the "return"
values could be used as lvalues. The `idx` macro in `array.h` was the best
example. The other benefits in c++ are pretty obvious, letting the compiler
check generic types and building the templates for you.

Despite the benefits, it seems like it enables poor design. The data structures
I designed are simple and easy to use, but took a while to design. In c++ I
think the resulting structures would be more natural to use and maybe cleaner
to implement, but abstraction leaks would be difficult to deal with. Not to
mention that I've tried to make data structures in c++ before, and
all the implcit casting combined with operator overloading makes things
brittle and hard to debug.
