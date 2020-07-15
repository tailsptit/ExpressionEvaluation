# ExpressionEvaluation
## Introduction
- Program is designed for evaluating value of an expression, using client-server model.
- Client sends a string expression to server using TCP protocol (such as netcat). 
- Server accepts & evaluates the string expression and returns the value to client  
- TCP Socket Server using C++14
- Support 10K connection clients

## Environment
- linux
- gcc 9.3.0
- cmake 3.16.3
- make 4.2.1

## Build project
#### Get source code
    git clone https://github.com/tailsptit/ExpressionEvaluation.git
#### Build project
##### Open terminal, go to ExpressionEvaluation path, execute commands
    cmake .
    make

#### Run project
###### From ExpressionEvaluation project path, run command
    ./ExpressionEvaluation -port PORT -pool-size SIZE
            
            -port: server tcp port. Default PORT = 8081
            -pool-size: number of threads. Default SIZE = 7       
###### Example
    ./ExpressionEvaluation -port 8081 -pool-size 5
    
#### Generate data
###### From ExpressionEvaluation project path, run command
    ./ExpressionEvaluation -gen-data GEN -num-expression NUM_EXPS -num-operand NUM_OPS -min-operand MIN_OPS -max-operand MAX_OPS -allow-bracket BRACKET -operator OPS -file FILE  
        
    Parameter is optional
        -gen-data: generating data. Default GEN=true
        -num-expression: number of expressions will be generated. Default NUM_EXPS = 1
        -num-operand: numer of operands in expression. Default NUM_OPS = 10
        -min-operand: minimum of operand. Default MIN_OPS = 0. Should be positive
        -max-operand: maximum of operand. Default MAX_OPS = 1000. Should be greater than MIN_OPS 
        -allow-bracket: allow bracket in expression or not. Default BRACKET = true
        -operator: allow operators in expression, it is subset of [+, -, x, /]. Default OPS = +-x/
        -file: absolute filename
###### Example
    ./ExpressionEvaluation -gen-data true -num-expression 1 -num-operand 20 -min-operand 0 -max-operand 2000 -allow-bracket true -operator +-
    ./ExpressionEvaluation -gen-data true -num-expression 1 -num-operand 20 -min-operand 0 -max-operand 2000 -allow-bracket true -operator +-x/ -file "/home/tails/Documents/Project/C++/test0.txt"  

#### Client using netcat tool
###### Send data by typing, run command
    nc localhost PORT
        
        - PORT: TCP server port
###### Send data from file, run command
    nc localhost PORT < FILE
        
        - PORT: TCP server port
        - FILE: Data file
               
###### Example
    nc localhost 8081
    nc localhost 8081 < "/home/tails/Documents/Project/C++/test0.txt"

## Some Test
    __________________________________________________________________________________
    |              Expression                |             Result                    |
    __________________________________________________________________________________
    | 1/0                                    | ERROR: Divide by zero                 |
    ----------------------------------------------------------------------------------      
    | 11111111111111111111                   | ERROR: Overflow 11111111111111111111  |
    ----------------------------------------------------------------------------------
    | a                                      | ERROR: Invalid character: a           |
    ----------------------------------------------------------------------------------
    | a+1 -10                                | ERROR: Invalid character: a           |
    ----------------------------------------------------------------------------------
    | 1+b                                    | ERROR: Invalid character: b           |
    ----------------------------------------------------------------------------------
    | 1*(-9)                                 | -9.000000                             |
    ---------------------------------------------------------------------------------|
    | 5   - (((-2) -2))                      | 9.000000                              |
    ----------------------------------------------------------------------------------
    | 1--4                                   | 6.000000                              |           
    ----------------------------------------------------------------------------------
    | 10 + 2 * 7                             | 24.000000                             |
    ---------------------------------------------------------------------------------|                    | 1/0                                    | ERROR: Divide by zero                                   
    | 100 * ( 2 + 12 ) / 2                   | 700.000000                            |       
    ---------------------------------------------------------------------------------|                | 1/0                                    | ERROR: Divide by zero                                   
    |( 1 - (-1 )  +1)  /2 +1                 | 2.500000                              |       
    ---------------------------------------------------------------------------------
## Technical
   - N/A