# LL(1) Parsing Grammar

This program implements an LL(1) parsing algorithm for a given context-free grammar in C++. It utilizes a parsing table constructed from the grammar's production rules, along with the First and Follow sets of the variables involved. The algorithm parses an input string to determine whether it is valid under the grammar or not.

## Features

- Reads the grammar rules, variables, terminals, and input string from a file.
- Constructs the First and Follow sets for the variables in the grammar.
- Generates a parsing table based on the First and Follow sets.
- Parses an input string using the constructed parsing table.
- Outputs the parsing process, including the stack, input, and actions taken.

## Usage

1. Make sure you have a C++ compiler installed on your system.
2. Clone this repository:
`git clone <repository_url>`
3. Navigate to the project directory:
`cd LL1-Parsing-Grammar`
4. Compile the code:
`g++ ll1_parsing_grammar.cpp -o ll1_parsing_grammar`
5. Run the program:
`./ll1_parsing_grammar`

6. Follow the on-screen instructions to enter the filename containing the grammar and input string.

## Grammar File Format

The grammar and input string are read from a file. The file should follow the specified format:
### Format 
`
start_symbol
production_1
production_2
...
production_n
input_string
`

- The `start_symbol` is a single character representing the start symbol of the grammar.
- Each `production_i` is a production rule in the form `variable -> expression`, where `variable` is a single uppercase character and `expression` is a sequence of variables and terminals separated by spaces.
- The `input_string` is the string to be parsed by the LL(1) parsing algorithm.

## Example

An example grammar file (`grammar.txt`) and input string (`input.txt`) are provided in the repository for reference. You can use these files to test the program.





