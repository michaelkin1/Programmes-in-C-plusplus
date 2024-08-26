# Programmes in C++
This repository contains C++ programmes from my assignments at the university level courses "Computers and Programming" and "Basic Programming in C++" at Uppsala University and University of Skövde respectively.

## 1. Expense Tracker

This C++ program tracks and manages shared expenses among people. It allows you to record transactions, calculate total costs, and determine how much each person owes or has advanced.

### Key Features

- **Transactions Management**: Use the `Transaktion` class to handle individual transactions, including date, type, amount, and involved persons.
- **Person Management**: Use the `Person` and `PersonLista` classes to track each person’s contributions and debts.
- **Dynamic Memory**: Utilizes dynamic memory allocation with pointers for managing arrays of transactions and persons.
- **File I/O**: Reads transactions from a file and saves them back after processing.
- **Dynamic Arrays**: Implements dynamic resizing of arrays to accommodate varying numbers of transactions and persons.

### Usage

- **Load Transactions**: Import from a file or input manually.
- **Menu Options**: View transactions, calculate totals, and check individual balances.

 <br />
## 2. Language Detection Program

This C++ program analyzes the frequency distribution of letters in a given text file to determine the most likely language among four predefined options: English, French, Swedish, and German. 

### Features

- **Classes and Objects**: Uses a `Text` class to handle text processing, including histogram calculations and language interpretation.
- **Arrays**: Utilizes arrays to store letter frequencies and predefined language profiles.
- **File Handling**: Reads text files from a specified directory and processes their contents.
- **String and Character Processing**: Converts characters to uppercase and calculates frequency distributions.
- **Mathematics**: Computes squared differences between actual and expected letter distributions to infer the most likely language.

### Usage
- **Input**: Provide the filepath of the text file/text folder to be analyzed.
- **Output**: The program displays the letter frequency distribution, compares it to predefined language profiles, and outputs the most probable language along with squared differences for each language.



