#include <stdlib.h>
#include <stdio.h>
#include "mysql/mysql.h"

int main (int argc, char *argv[])
{

        MYSQL *conn_ptr;
        MYSQL_RES *res_ptr;
        MYSQL_ROW sqlrow;
        int res;
        conn_ptr=mysql_init(NULL); //连接初始化
        mysql_options(conn_ptr, MYSQL_SET_CHARSET_NAME, "utf8");
        if(!conn_ptr){
                fprintf(stderr, "mysql_init failed\n");
                return EXIT_FAILURE;
        }

        conn_ptr = mysql_real_connect(conn_ptr, "localhost", "onter","980909","test", 0, NULL, 0); //建立实际连接
        //参数分别为：初始化的连接句柄指针，主机名（或者IP），用户名，密码，数据库名，0，NULL，0）后面三个参数在默认安装mysql>的情况下不用改
        if(conn_ptr){
                printf("Connection success\n");
                }
        else {
                printf("Connection failed\n");
        }
        res = mysql_query(conn_ptr, "use test");
        res = mysql_query(conn_ptr, "select * from ts;");
        if (res)
        {
          printf("select error: %s \n", mysql_error(conn_ptr));
        }
        else
        {
          res_ptr = mysql_store_result(conn_ptr);
          if (res_ptr)
          {
            printf("Retrieved %lu row\n",(unsigned long)mysql_num_rows(res_ptr));
          }
          while (sqlrow = mysql_fetch_row(res_ptr))
          {
            unsigned int filed_count;
            filed_count = 0;
            while (filed_count < mysql_field_count(conn_ptr))
            {
              printf("%s ",sqlrow[filed_count]);
              filed_count++;
            }
            printf("\n");
          }
          mysql_free_result(res_ptr);
        }
        mysql_close(conn_ptr); //关闭连接
        return EXIT_SUCCESS;
}
