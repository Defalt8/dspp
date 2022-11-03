# Fixed Specifications

Fixed 'array' holds an array of values with a certain compile-time size.
  
`Fixed`:

- must take two template parameters, type `typename E` and size `size_t size_`.
- must store actual array of values and not a pointer to one.
- must be conditionally copy and move constructible and assignable.
- must be constructible by initializing list of possibly different values.
