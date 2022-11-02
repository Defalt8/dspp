# Allocator Specifications

Allocators are used to flexibly manage memory allocation for different types of data-structures.
  
Allocators:

- must define a static function that *may throw or not* called `allocate`.

```c++
    static void * allocate(size_t size, size_t align = 0);
```

- must define a static function that *cannot throw* called `deallocate`.

```c++
    static void deallocate(void * block) noexcept;
```

- do not need to inherit an interface class. They are used as template parameters.

`Allocator::allocate`:

- must return a unique valid memory block address of size `size`. Or else throw an exception or return a null pointer on failure. This applies for size zero as well.

`Allocator::deallocate`:

- must free the block of memory pointed to by `block` if `block` is not null, and must do nothing to it if it is.
