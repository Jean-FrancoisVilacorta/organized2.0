
# Organized 2.0

**Organized 2.0** is a tag-based data manager that allows you to store, organize, and encrypt information. The program is developed in C, with the encryption handled by a Python script called `103cypher`.

## Features

- **User management**: Create and authenticate users with a username and password.
- **Add and delete data**: Add or delete information associated with tags.
- **Filter data**: Print stored data by name or type.
- **Sort data**: Organize data by ID, type, or name.
- **Encrypted messages**: Write and read encrypted messages using a Python encryption system.
- **Advanced commands**: Several options for managing data flexibly.

## Requirements

### Dependencies:

- **Python 3.x**: Required for the `103cypher` encryption script.

To install the necessary library, run:

```bash
sudo apt install python3.13
```

C Compiler: The program is written in C and must be compiled using a compatible C compiler.

## Installation
Clone the repository or download the source code.
Install the Python dependencies (if not already installed):


Compile the program: The C program is compiled using a Makefile. To compile it, simply run:

```bash
make
```
Run the program: After compiling, the executable will be generated. To run it, use:
```bash

./organized
```

# Available Commands
Here are the commands you can use to interact with the program. Each command has its own flags that you can use to customize its behavior.

## add (type) (data name) ...
Add data associated with a specific type. You can add multiple items in a single execution.

#### Example:

```bash
add work "Sales report" "Meeting with client"
```

## del (id)
Delete a data entry identified by its ID within a specific type.

#### Example:

```bash
del work 2
```


## disp ("_" | "-n NAME" "-t TYPE")
Print stored data. You can use filters to display only data with a specific name or type.

#### Flags:

    -n NAME: Filters by the specified name.
    -t TYPE: Filters by the specified type (tag).
    \0: Displays all data.

#### Example:

```bash
disp -n "Report"
disp -t "work"
disp "_"
```
## sort ("ID | TYPE | NAME ... -r")
Sort the data by ID, type, or name. You can use the -r flag to sort in descending order.

#### Flags:

- ID: Sort by ID.
- TYPE: Sort by type.
- NAME: Sort by name.
- -r: Sort in descending order.

#### Example:

```bash
sort ID -r
sort NAME
```

## type (...)
Create new types (tags) to organize the data.

#### Example:

```bash
    type work health personal
```


## remove ("type", ...)
Remove one or more types. If data is associated with the type, it is not recommended to remove it.

####Example:

```bash
remove work
```


## write ("id" "message")
Write an encrypted message associated with an ID.

####Example:

```bash
write 1 "Confidential message"
```

## read ("id")
Read the encrypted message associated with an ID.

#### Example:

```bash
    read 1
```

## help
Displays a quick guide for the available commands.

#### Example:

```bash
    help add
    help disp
```


## Message Encryption
The program uses the Fernet encryption system from the cryptography library in Python to ensure that messages remain confidential. The messages are encrypted before being stored and can only be read by those with access to the encryption key.

The script 103cipher handles the encryption and decryption of messages.

## Using Makefile

#### Make Commands:
    make: Compiles the project and generates the executable.
    make re: Recompiles the project from scratch (uses clean first).
    make clean: Removes files generated during compilation.
    make fclean: Removes both the compilation files and the generated executable.

### Example usage:

### Compile the project:
```bash
make
```

#### Recompile the project (clean first):
```bash
make re
```

#### Remove compilation files:
```bash
make clean
```

#### Remove the executable:
~~~bash
make fclean
~~~

### Contributing
## Authors

- [@Jean-F](https://github.com/Jean-FrancoisVilacorta)

## Used By

This project is used by the following companies:

- by me
- and my friend Paco
