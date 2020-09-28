/*This is a simple console based CRUD application written as a dbms project using C API provided by oracle.
This project is completely written in C. The project is mainly focused on explicitly execution of SQL statement.
No any inbuilt function is used for exectution of SQL statement like CREATE,DROP,UPDATE,INSERT,SELECT,SHOW,DESCRIBE,
EXPLAIN,CHECK TABLE.*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<mysql/mysql.h> //header file consisting of C API code
#define _GNU_SOURCE
/*catch_error() is error handling custom function*/
void catch_error(char *str, MYSQL *mysql )
{
    printf("%s:%u,%s\n", str, mysql_errno(mysql),mysql_error(mysql));
    mysql_close(mysql);
    exit(EXIT_FAILURE);
}
int main(){
    MYSQL *mysql = NULL;
    MYSQL_RES *res;
    MYSQL_FIELD *field;
    MYSQL_ROW row;
    char c;
    int flag;
    char *line = NULL;
    size_t len = 0;
    size_t nread;
    char hostname[15],user[10],password[15],databaseN[15];
    printf("enter the host name\n");
    scanf("%s",hostname);
    printf("enter user name\n");
    scanf("%s",user);
    printf("enter password\n");
    scanf("%s",password);
    printf("enter database name\n");
    scanf("%s",databaseN);
    while ((getchar()) != '\n');
    printf("enter sql command\n");
    nread = getline(&line, &len, stdin);
    *(line+nread-1) = '\0';
    /*mysql_library_init() initializes the MySQL client library before you call any other MySQL function.*/
    if (mysql_library_init(0, NULL, NULL) != 0 ){
        catch_error("mysql_library_init", mysql);
    }
    /*mysql_init() allocates or initializes a MYSQL object suitable for mysql_real_connect()*/
    if ((mysql = mysql_init(mysql)) == NULL){
        catch_error("mysql_init",mysql);
    }
    /*mysql_real_connect() attempts to establish a connection to a MySQL server running on host.
    Client programs must successfully connect to a server before executing any other API functions that
    require a valid MYSQL connection handler structure.*/
    if (!mysql_real_connect(mysql, hostname, user, password, databaseN, 0, NULL, CLIENT_MULTI_STATEMENTS))
    {
        catch_error("mysql_real_connect",mysql);
    }
    /*mysql_query() executes the SQL statement pointed to by the null-terminated string line.*/
    if (mysql_query(mysql,line) == 0){
        free(line);//pointer to string representing SQL statement should be freed for effieciency. 
        printf("the number of rows affected:%ld\n", mysql_affected_rows(mysql));
        /*After invoking mysql_query() or mysql_real_query(), we must call mysql_store_result()
        for every statement that successfully produces a result set (SELECT, SHOW,
        DESCRIBE, EXPLAIN, CHECK TABLE, and so forth)*/
        do{
            res = mysql_store_result(mysql);
            if(res){
                printf("mysql_store_result succedeed\n");
                int num_fields = mysql_num_fields(res);
                while (row = mysql_fetch_row(res))
                {
                    for (int i = 0; i < num_fields; i++)
                    {
                        if (i == 0)
                        {
                            while (field = mysql_fetch_field(res))
                            {
                                printf("%s", field->name);
                            }
                            printf("\n");
                        }
                        printf("%s ", row[i] ? row[i] : "NULL");
                    }
                    printf("\n");
                }
                /*mysql_free_result() frees the memory allocated for a result set by mysql_store_result()*/
                
            }else{
                /*mysql_field_count() returns the number of columns for the most recent query on the connection.*/
                if (mysql_field_count(mysql) == 0)
                    printf("empty result set\n");
                else
                    catch_error("mysql_result_store", mysql);
            }
            mysql_free_result(res);
            flag = mysql_next_result(mysql);
            if (flag > 0)
                catch_error("mysql_next_result", mysql);
        }while(flag == 0);
    }   
    else{
        free(line);
        catch_error("mysql_query", mysql);
    }
    /*mysql_close() closes a previously opened connection. mysql_close() also deallocates the connection
    handler pointed to by mysql if the handler was allocated automatically by mysql_init() or
    mysql_connect()*/
    mysql_close(mysql);
    /*mysql_library_end() finalizes the MySQL client library.calling this causes the avoidance of memory
    leaks after the application is done.*/
    mysql_library_end(); 
    return(EXIT_SUCCESS);
}