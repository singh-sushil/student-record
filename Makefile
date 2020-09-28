#make compile #compile the student-record.c
#make link    #link the student-record.o after compilation
#make run_executable #run the executable file generated after linking
#make clean      #remove executable file


#.PHONY: all compile link run_executable
CC = gcc
all: compile link
compile:
	${CC} -c `mysql_config --cflags` student-record.c

link:
	${CC} -o student_record student-record.o `mysql_config --libs`

run_executable:
	./student_record
clean:
	rm student_record