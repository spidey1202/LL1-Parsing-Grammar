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

