# PROJECT REPORT: SPARSE MATRIX SYSTEM

**Project:** Sparse Matrix Implementation and Manipulation  
**Language:** C++  

---

## 1. SYSTEM FUNCTIONALITY EXPLANATION

### 1.1 Overview
The developed system implements a complete **Sparse Matrix** in C++, providing an interactive interface for manipulation and processing of matrices with few non-zero elements. A sparse matrix is an efficient data structure that stores only non-zero elements, saving memory and improving performance in operations with large and sparse matrices.

### 1.2 System Architecture
The project is organized into three main components:

- **Node.h**: Represents an individual node of the sparse matrix
- **SparseMatrix.h**: Implements the matrix structure and its operations
- **main.cpp**: Main interface with interactive menu

### 1.3 Implemented Algorithms

#### 1.3.1 Insertion
1. Position validation (row, column)
2. Location of correct position in structure
3. Node creation/update
4. Maintenance of circular lists by row and column

#### 1.3.2 Search
1. Navigation through structure using sentinel nodes
2. Traversal of circular lists
3. Value return (0.0 if not found)

#### 1.3.3 Matrix Operations
1. **Addition**: Traversal of both matrices and value combination
2. **Multiplication**: Scalar product between rows and columns
3. Compatible dimension validation

---

## 2. IMPLEMENTED FEATURES

### 2.1 Required Features ✅

#### ✅ Matrix Creation
- Creation of sparse matrices with MxN dimensions
- Automatic structure initialization with sentinel nodes
- Input validation for positive dimensions

#### ✅ Value Insertion
- Efficient insertion maintaining sparse structure
- Automatic removal of zero elements
- Update of existing values

#### ✅ Matrix Visualization
- **Complete Display**: Shows complete matrix including zeros
- **Matrix Listing**: Shows all created matrices with indices
- Readable and organized format

#### ✅ Matrix Operations
- **Matrix Addition**: Addition of two compatible matrices
- **Matrix Multiplication**: Product of compatible matrices
- Automatic dimension validation

#### ✅ File Reading
- Loading matrices from text files
- Format: first line with dimensions, followed by triplets (row, column, value)
- File error handling

### 2.2 Extra Features ✅

#### ✅ Complete Interactive Interface
- Intuitive menu with textual commands
- Integrated help system
- Robust input validation

#### ✅ Multiple Matrix Management
- Storage of multiple matrices in vector
- Operations by matrix index
- Individual copy and removal

#### ✅ Advanced Features
- **Matrix Copy**: Complete matrix duplication
- **Selective Cleanup**: Removal of specific matrices
- **Total Cleanup**: Removal of all matrices

---

## 3. EXECUTION EXAMPLES

### 3.1 Creation and Insertion Example

```
-----------------------------------------------
         Welcome to the Matrix System!     
-----------------------------------------------
>> criar 3 3
Created matrix[0] with size 3x3

>> atualizar 0 1 1 5.5
Matrix[0] updated at position (1, 1) with 5.5

>> atualizar 0 2 3 3.2
Matrix[0] updated at position (2, 3) with 3.2

>> mostrar 0
5.5 0 0 
0 0 3.2 
0 0 0 
```

### 3.2 Matrix Addition Example

```
>> criar 2 2
Created matrix[1] with size 2x2

>> atualizar 1 1 1 2
Matrix[1] updated at position (1, 1) with 2

>> atualizar 1 2 2 4
Matrix[1] updated at position (2, 2) with 4

>> criar 2 2
Created matrix[2] with size 2x2

>> atualizar 2 1 1 3
Matrix[2] updated at position (1, 1) with 3

>> atualizar 2 1 2 1
Matrix[2] updated at position (1, 2) with 1

>> somar 1 2
Sum result stored as matrix[3]

>> mostrar 3
5 1 
0 4 
```

### 3.3 File Reading Example

```
>> ler
Enter filename: m1.txt
Enter matrix dimensions (rows columns): 3 3
Matrix successfully read from file m1.txt and stored as matrix [4]

>> mostrar 4
1 2 3 
2 3 1 
1 4 5 
```

### 3.4 Matrix Listing Example

```
>> listar
Created matrices:
Matrix[0] - Size: 3x3
Matrix[1] - Size: 2x2
Matrix[2] - Size: 2x2
Matrix[3] - Size: 2x2
Matrix[4] - Size: 3x3
```

---

## 4. DEVELOPMENT REPORT

### 4.1 Methodology Used
The development followed an incremental approach:

1. **Requirements Analysis**: Clear definition of functionalities
2. **Structure Design**: Creation of node and circular list architecture
3. **Gradual Implementation**: Development by functionality
4. **Continuous Testing**: Validation at each stage
5. **Refinement**: Interface and documentation improvements

### 4.2 Design Decisions

#### 4.2.1 Data Structure
- **Circular Doubly Linked Lists**: For efficient navigation by rows and columns
- **Sentinel Nodes**: Simplification of insertion and removal operations
- **Non-Zero Only Storage**: Significant memory savings

#### 4.2.2 Internal Representation
```
Structure with sentinel nodes:
- Main sentinel (0,0)
- Row sentinels (i,0) for each row i
- Column sentinels (0,j) for each column j
- Data nodes (i,j) only for non-zero values
```

#### 4.2.3 User Interface
- **Textual Commands**: More intuitive interface than numbered menus
- **Robust Validation**: Handling of all types of invalid input
- **Clear Feedback**: Informative messages for all operations

### 4.3 Extra Features Implemented

1. **Advanced Command System**: Rich interface with multiple commands
2. **Multiple Matrix Management**: Ability to work with several matrices simultaneously
3. **Robust Error Handling**: Complete input validation and error recovery
4. **Copy Operations**: Efficient matrix duplication
5. **File Reading**: Complete support for external data loading

### 4.4 Highlighted Technical Aspects

#### 4.4.1 Memory Management
- Automatic destructor that frees all allocated memory
- Copy constructor for safe duplication
- Assignment operator for deep copy

#### 4.4.2 Efficiency
- O(min(m,n)) complexity for insertion/search
- Storage proportional only to non-zero elements
- Matrix operations optimized for sparse matrices

#### 4.4.3 Robustness
- Validation of all user inputs
- Exception handling in file operations
- Graceful error recovery without program crash

---

## 5. FILE STRUCTURE

```
sparse-matrix/
├── main.cpp           # Main interface and command logic
├── SparseMatrix.h     # Sparse matrix class implementation
├── Node.h             # Node structure definition
├── README.md          # Project documentation
└── output/            # Example files for testing
    ├── m1.txt
    ├── m2.txt
    ├── m3.txt
    ├── m4.txt
    └── m5.txt
```

---

## 6. HOW TO COMPILE AND RUN

### 6.1 Compilation
```bash
g++ -o main main.cpp
```

### 6.2 Execution
```bash
./main
```

### 6.3 Available Commands
- `ajuda` - Display command list
- `criar m n` - Create MxN matrix
- `mostrar n` - Display matrix n
- `atualizar n i j v` - Update position (i,j) of matrix n with value v
- `somar a b` - Add matrices a and b
- `multiplicar a b` - Multiply matrices a and b
- `listar` - List all matrices
- `ler` - Load matrix from file
- `copiar n` - Copy matrix n
- `limpar n` - Remove matrix n
- `apagarTudo` - Remove all matrices
- `sair` - Exit program

---

## 7. TECHNICAL SPECIFICATIONS

### 7.1 Data Structure Details
The sparse matrix uses a sophisticated circular doubly linked list structure:

- **Sentinel Node System**: Each row and column has a sentinel node for simplified operations
- **Circular Lists**: Both row and column lists are circular, eliminating special cases
- **Efficient Storage**: Only non-zero elements are stored, dramatically reducing memory usage

### 7.2 Algorithm Complexity
- **Insertion**: O(min(rows, cols)) - navigates to correct position
- **Search**: O(min(rows, cols)) - follows row or column list
- **Matrix Addition**: O(nnz1 + nnz2) where nnz = number of non-zeros
- **Matrix Multiplication**: O(rows × cols × min(cols1, rows2))

### 7.3 Memory Efficiency
For a matrix with dimensions m×n and k non-zero elements:
- **Dense matrix**: O(m×n) space complexity
- **Sparse matrix**: O(m + n + k) space complexity
- **Space savings**: Significant when k << m×n

---

The final result is a complete and functional system that meets all specified requirements, with extra features (advanced interactive interface, multiple matrix management) that significantly enrich the user experience.