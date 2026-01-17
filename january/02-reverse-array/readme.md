# in-place array reversal logic

### technical overview
this implementation demonstrates a low-level approach to array manipulation in c++ by utilizing raw pointer arithmetic. instead of allocating auxiliary buffers or using standard library wrappers, the algorithm operates directly on the memory stack, swapping elements via two converging pointers.

### core logic (the hft way)
* **spatial complexity**: $o(1)$ - zero-copy mechanism. no additional memory is allocated regardless of array size.
* **temporal complexity**: $o(n/2)$ - optimized traversal that terminates exactly at the midpoint.
* **pointer arithmetic**: utilizes `ptr++` and `ptr--` to navigate memory addresses rather than relying on index-based access.

### execution flow
1. initialize pointer `s` at the base address of the array.
2. initialize pointer `e` at the address offset `n - 1`.
3. execute a `while` loop predicated on `s < e` (address comparison).
4. perform a bitwise-safe swap using a temporary register.
5. increment `s` and decrement `e` to converge towards the median.

### how to build
```
g++ reverse_array.cpp -o reverse_engine
./reverse_engine
```

### terminal output snippet

```
rodada 0: 50 20 30 40 10 
rodada 1: 50 40 30 20 10
```

### what i learned today in practice:

- **direct addressing: you didn’t use vetor[i], you worked with physical memory addresses.**

- **converging pointers: a classic technique for high-performance algorithms.**

- **stack management: how to swap values without allocating extra memory.**
