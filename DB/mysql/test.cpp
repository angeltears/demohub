#include <stdlib.h>
#include <stdio.h>
#include "mysql/mysql.h"

MYSQL *conn_ptr;
MYSQL_RES *res_ptr;
MYSQL_ROW sqlrow;

void display_header()
{
  MYSQL_FIELD *field_ptr;
  printf("column details; \n");
  while ((field_ptr = mysql_fetch_field(res_ptr))!= NULL)
  {
    printf("\t Name: %s\n",field_ptr->name);
    printf("\t Type :");
    if (IS_NUM(field_ptr->type))
    {
      printf("Numeric filed\n");
    }
    else
    {
      switch (field_ptr->type) {
        case FIELD_TYPE_VAR_STRING:
            printf("VARCHAR\n");break;
        case FIELD_TYPE_LONG:
            printf("LONG\n");break;
        default:
            printf("Type is %d, check in mysql_com.h\n", field_ptr->type);
      }
    }
    printf("\t Max width %ld\n", field_ptr->length);
    if (field_ptr->flags /*ATUO_INCREMENT_FLAG*/)
      printf("\t Auto incremet\n");
      printf("\n");
  }
}

void display_row()
{
  unsigned int field_count;
  field_count = 0;
  while (field_count < mysql_field_count(conn_ptr))
  {
    if(sqlrow[field_count])
        printf("%s ",sqlrow[field_count]);
    else
        printf("NULL");
    field_count++;
  }
  printf("\n");
}

int main (int argc, char *argv[])
{
        int res;
        int first_row =1;
        conn_ptr = mysql_init(0); //连接初始化
        mysql_options(conn_ptr, MYSQL_SET_CHARSET_NAME, "utf8");
        if(!conn_ptr){
                fprintf(stderr, "mysql_init failed\n");
                return EXIT_FAILURE;
        }

        conn_ptr = mysql_real_connect(conn_ptr, "123.207.40.210", "root","123456qwe","test",3306, 0, 0); //建立实际连接
        //参数分别为：初始化的连接句柄指针，主机名（或者IP），用户名，密码，数据库名，0，NULL，0）后面三个参数在默认安装mysql>的情况下不用改
        if(conn_ptr){
                printf("Connection success\n");
                }
        else {
                printf("Connection failed\n");
                fprintf(stderr, "error: %s",mysql_error(conn_ptr));
        }
//         res = mysql_query(conn_ptr, "use test");
//         res = mysql_query(conn_ptr, "select * from ts;");
//         if (res)
//         {
//           printf("select error: %s \n", mysql_error(conn_ptr));
//         }
//         else
//         {
//           res_ptr = mysql_use_result(conn_ptr);
//           if (res_ptr)
//           {
//             display_header();
//             while((sqlrow = mysql_fetch_row(res_ptr))){
//             if(first_row)
//             {
//                 display_header();
//                 first_row = 0;
//             }
//             display_row();
//           }
// /*          if(mysql_error(conn_ptr))
//               fprintf(stderr, "Retrive error: %s\n", mysql_error(conn_ptr));*/
//         }
//           mysql_free_result(res_ptr);
//         }
//         mysql_close(conn_ptr); //关闭连接
//         return EXIT_SUCCESS;
}
