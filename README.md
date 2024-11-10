
# Binary Tree

This program was developed for educational purposes. The goal was to mix basic C programming knowledge with advanced concepts such as Binary Search Trees (BST) and AVL balancing.
## Installation

The program does not need to be installed. However, you can generate a new binary file by running `make` in the project root folder or using the shell script "build.sh".
## Features and Usage

Binary Tree allows you to create a list containing the first name and last name of an individual using SQL-like queries such as SELECT, INSERT, DELETE, and more.

The SQL table includes 3 columns:
1. **primaryKey**: This ID is an integer used for search purposes and in the binary search tree system.
2. **first_name**: This column contains the first name of the individual.
3. **last_name**: This column contains the last name of the individual.

### Starting Program
You can start the program using the binary file "binarytree":
___./binarytree___

When starting, the program seeks for an existing save file and directory. If none is found, new ones are created in the same location as the "binarytree" file.

The CLI will prompt if you want to load data from the save file. At this moment, you should answer by typing ___yes___ or continue by pressing the ___enter___ key.

### Command Line Interface
When the prompt ___"binarytree >"___ appears, you can type several commands:

- `?` : Display available commands.
- `clear` : Clear the console.
- `save` : Save data to file.
- `load` : Load data from file.
- `reset` : Reset all data in RAM.
- `showtree` : Display the binary tree.
- `color` : Change the color of the prompt.
- `quit` : Exit the program.
- `SELECT` : Display specific column(s) of the table.
- `INSERT` : Insert a new row.
- `DELETE WHERE` : Remove an existing row.

### _showtree_
- `showtree <type>` 
`showtree` allows you to display the binary tree structure, including node heights. To use this command, you must include one of the available tree traversal types:
1. **preorder**: The binary tree is shown, starting with the root, followed by the left subtree and then the right subtree.
2. **inorder**: The binary tree is shown, starting with the left subtree, followed by the root, and then the right subtree.
3. **postorder**: The binary tree is shown, starting with the left subtree, followed by the right subtree, and then the root.

### _color_
- `color <color>` 
`color` allows you to change the color of the prompt. To use this command, you must include one of the available colors:
1. **red**: This is the default color.
2. **cyan**
3. **green**

### _SELECT_
- `SELECT <column1> <column2> <column3>`
- `SELECT *` 
`SELECT` allows you to display desired columns of the table. You can display 1 to 3 columns or all columns using the ___*___ character.
1. **primaryKey**: This ID is an integer used for search purposes and in the binary search tree system.
2. **first_name**: This column contains the first name of the individual.
3. **last_name**: This column contains the last name of the individual.

### _INSERT_
- `INSERT <first_name> <last_name>` 
`INSERT` allows you to insert a new individual into the table. The program searches for a free primaryKey to insert data into the binary tree. To use this command, you must include the first name and the last name of the new individual:
1. **first_name**: This column contains the first name of the individual.
2. **last_name**: This column contains the last name of the individual.

### _DELETE_
- `DELETE WHERE <column>='<value>'`
- Example: `DELETE WHERE first_name='john'`
`DELETE WHERE` allows you to delete data from the table by specifying a column as the criterion. To use this command, you must include one column and the targeted content:
1. **primaryKey**: This ID is an integer used for search purposes and in the binary search tree system.
2. **first_name**: This column contains the first name of the individual.
3. **last_name**: This column contains the last name of the individual.

### Qutting Program
You can quit the program using the command `quit`.

The CLI will prompt if you want to save data into the save file. At this moment, you should answer by typing ___yes___ or continue by pressing the ___enter___ key.

If the table is empty, The CLI will prompt if you want to reset the save file. At this moment, you should answer by typing ___yes___ or continue by pressing the ___enter___ key.
## 🔗 Links
[![portfolio](https://img.shields.io/badge/my_portfolio-000?style=for-the-badge&logo=ko-fi&logoColor=white)](https://sachadelval.nexgate.ch/)
[![linkedin](https://img.shields.io/badge/linkedin-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/delvalsacha/)
[![github](https://img.shields.io/badge/github-1DA1F2?style=for-the-badge&logo=github&logoColor=white)](https://github.com/delvals/)
