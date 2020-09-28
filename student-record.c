#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<mysql/mysql.h>
#define _GNU_SOURCE
void catch_error(char *str, MYSQL *mysql )
{
    printf("%s:%u,%s\n", str, mysql_errno(mysql),mysql_error(mysql));
    exit(EXIT_FAILURE);
}
int main(){
    MYSQL *mysql;
    MYSQL_RES *res;
    char c;
    char *line = NULL;
    size_t len = 0;
    size_t nread;
    printf("enter sql command\n");
/*   // while ((nread = read(STDIN_FILENO, &c, 1)) == 0);*/
    nread = getline(&line, &len, stdin);
    *(line+nread-1) = '\0';
    if (mysql_library_init(0, NULL, NULL) != 0 )
    {
        catch_error("mysql_library_init", mysql);
    }
    if ((mysql = mysql_init(mysql)) == NULL){
        catch_error("mysql_init",mysql);
    }
    if (!mysql_real_connect(mysql, "localhost", "root", "archOS", "student_record", 0, NULL, 0)){
        catch_error("mysql_real_connect",mysql);
    }
    if (mysql_query(mysql, line) != 0)
        catch_error("mysql_query", mysql);
    else
        printf("the number of rows affected:%ld\n",mysql_affected_rows(mysql));
    free(line);
    mysql_close(mysql);
    mysql_library_end();
    return(EXIT_SUCCESS);
}