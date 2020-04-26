# Get Next Line
Reading a line on a fd is way too tedious  
Summary: The aim of this project is to make you code a function that returns a line
ending with a newline, read from a file descriptor.  

__Installation:__

* `git clone https://github.com/Hugothms/get_next_line.git`

**Usage:** 
* get next line is a function that reads a file descriptor line by line and return a line for each call

**Parameters:**  
1.`file descriptor for reading`  
2.`The value of what has been read`

**Return value:**
* `return 1 when it read a line`
* `return 0 when it finished reading a file`
* `return -1 when an error occurs`


**Return value:**
1 : A line has been read
0 : EOF has been reached
-1 : An error happened
