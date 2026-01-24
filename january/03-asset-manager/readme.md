# 03-asset-manager

Overview
--------
This project implements a basic financial asset management system. It focuses on using C++ classes to move away from simple structs, ensuring data integrity through encapsulation and local file persistence (.db).

Technical Overview
-----------------------------------

### 1. Encapsulation & Class Architecture

- **Private layer:** the class `asset` stores `ticker`, `price`, and `quantity` as private members. this prevents external unauthorized memory modification.

- **Constructor:** initializes the object state. mapped parameters from the stack to the private heap-like members.

- **Getters:** public methods implemented to provide read-only access to the internal state. this allows data visualization without compromising the original variables.

### 2. Persistence Layer (Filesystem)

- **ofstream & std::ios::app:** used to open `portfolio.db`. the app flag (append) ensures that new data is written at the end of the file, preventing the truncation of previous sessions.

- **Delimiters:** data is stored using the `;` character. this creates a structured flat-file database that simplifies parsing during the loading phase.

### 3. Memory Reconstruction (Parsing)

- **ifstream:** reads the raw byte stream from the disk.

- **getline & string manipulation:** the `memory()` function uses `.find()` to locate delimiters and `.substr()` to slice the string into tokens.

- **Type conversion:** `std::stod` (string to double) and `std::stoi` (string to int) are used to cast the text back into numerical data.

- **Vector storage:** reconstructed objects are pushed into a `std::vector<asset>`, creating a dynamic array in RAM for fast iteration.

### 4. Iteration & Optimization

- **auto&:** used in the range-based loop to deduce the type and access the vector elements by reference.

- **Efficiency note:** by using references (`&`), we avoid the overhead of calling the copy constructor for each asset object during output, which is critical for low-latency logic.

AI Adjustments & Improvements
------------------------------------------

- **Initialization lists:** instead of assigning values inside the constructor body, use `: ticker(t), price(p), quantity(q)`. it is faster because it initializes members directly.

- **RAII & file handles:** in the `memory()` function, ensure `prt.close()` is called before the return statement. however, in C++, the file destructor handles this automatically when the scope ends.

- **Const correctness:** getters should be marked as `const` (e.g., `double getPrice() const`) to guarantee they don't modify the object.

How to Run
----------

- Compile using:
  
  ```
  g++ asset_manager.cpp -o manager
  ```
  
  `./manager`
