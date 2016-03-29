template-indenter
=================

A very basic script to indent templates in C++ compilers' error messages.
Tested with **gcc** and **clang**.

Example
-------
`template-indenter` transforms this error message:

```
src/utils/mapped_container.hpp:17:36: error: 'OrigT' is a private member of 'mapped_iterator<class_diagram::Item &, __gnu_debug::_Safe_iterator<__gnu_cxx::__normal_iterator<const std::unique_ptr<class_diagram::Item, std::default_delete<class_diagram::Item> > *, std::__cxx1998::vector<std::unique_ptr<class_diagram::Item, std::default_delete<class_diagram::Item> >, std::allocator<std::unique_ptr<class_diagram::Item, std::default_delete<class_diagram::Item> > > > >, std::__debug::vector<std::unique_ptr<class_diagram::Item, std::default_delete<class_diagram::Item> >, std::allocator<std::unique_ptr<class_diagram::Item, std::default_delete<class_diagram::Item> > > > > >'
```

into this:

```
src/utils/mapped_container.hpp:17:36: error: 'OrigT' is a private member of 'mapped_iterator<
    class_diagram::Item &,
    __gnu_debug::_Safe_iterator<
        __gnu_cxx::__normal_iterator<
            const std::unique_ptr<
                class_diagram::Item,
                std::default_delete<
                    class_diagram::Item>>*,
            std::__cxx1998::vector<
                std::unique_ptr<
                    class_diagram::Item,
                    std::default_delete<
                        class_diagram::Item>>,
                std::allocator<
                    std::unique_ptr<
                        class_diagram::Item,
                        std::default_delete<
                            class_diagram::Item>>>>>,
        std::__debug::vector<
            std::unique_ptr<
                class_diagram::Item,
                std::default_delete<
                    class_diagram::Item>>,
            std::allocator<
                std::unique_ptr<
                    class_diagram::Item,
                    std::default_delete<
                        class_diagram::Item>>>>>>'
```

Compiling
---------
Just run `make`. The only dependency is a C++11 compiler.

Usage
-----
`template-indenter` simply reads from the standard input and writes the
reformatted error messages to the standard output. So, for example, you can
run:

```
g++ [...] |& template-indenter
```

or

```
clang++ -fcolor-diagnostics [...] |& template-indenter
```

(`-fcolor-diagnostics` is necessary to have `clang` output colour codes
despite its output not being a terminal.)
