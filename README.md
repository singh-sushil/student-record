# student-record
This is a simple console based CRUD application developed as a dbms project using <br/>
[C API](https://dev.mysql.com/doc/c-api/8.0/en/c-api-function-overview.html) provided by Oracle.<br/>
This project is completely written in C.

## installation
**clone the repo, compile and link using following syntax or u can refer Makefile** <br/> 
gcc compiler is used here. different compiler might be used on respective system.<br/>
gcc -c `mysql_config --cflags` student-record.c;  for compilation.<br/>
gcc -o student_record student-record.o `mysql_config --libs`; for linking after compilation.<br/>
here *student-record.o* is file generated after compilation.<br/>
*student_record* is executable file generated after linking.<br/>

## license
student record is written by sushil singh and is released  under <br/>
[MIT](https://choosealicense.com/licenses/mit/)license.