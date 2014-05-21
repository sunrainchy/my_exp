#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <algorithm>
#include <iostream>
using namespace std;
#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD "940407"
#define DATABASE "student_1104"
void query_sql(char* sql) 
{
    MYSQL my_connection; /*这是一个数据库连接*/
    int res; /*执行sql語句后的返回标志*/
    MYSQL_RES *res_ptr; /*指向查询结果的指针*/
    MYSQL_FIELD *field; /*字段结构指针*/
    MYSQL_ROW result_row; /*按行返回的查询信息*/

    int row, column; /*查询返回的行数和列数*/
    int i, j; /*只是控制循环的两个变量*/

    /*初始化mysql连接my_connection*/
    mysql_init(&my_connection);

    /*这里就是用了mysql.h里的一个函数，用我们之前定义的那些宏建立mysql连接，并
    返回一个值，返回不为空证明连接是成功的*/
    if (mysql_real_connect(&my_connection, HOST, USERNAME, PASSWORD,
               DATABASE, 0, NULL, CLIENT_FOUND_ROWS)) 
	{
		/*连接成功*/
        printf("数据库查询query_sql连接成功！\n");
        /*这句话是设置查询编码为utf8，这样支持中文*/
        mysql_query(&my_connection, "set names utf8");
		
        /*下面这句话就是用mysql_query函数来执行我们刚刚传入的sql語句，
        这会返回一个int值，如果为0，证明語句执行成功*/
        res = mysql_query(&my_connection, sql);

        if (res) 
		{ /*现在就代表执行失败了*/
            printf("Error： mysql_query !\n");
            /*不要忘了关闭连接*/
            mysql_close(&my_connection);
        }
		else 
		{ 
			/*现在就代表执行成功了*/
            /*将查询的結果给res_ptr*/
            res_ptr = mysql_store_result(&my_connection);

            /*如果结果不为空，就把结果print*/
            if (res_ptr) 
			{
                /*取得結果的行数和*/
                column = mysql_num_fields(res_ptr);
                row = mysql_num_rows(res_ptr) + 1;
                printf("查询到 %lu 行 \n", row);

                /*输出結果的字段名*/
                for (i = 0; field = mysql_fetch_field(res_ptr); i++)
                    printf("%s\t", field->name);
                printf("\n");

                /*按行输出結果*/
                for (i = 1; i < row; i++)
				{
                    result_row = mysql_fetch_row(res_ptr);
                    for (j = 0; j < column; j++)
                        printf("%s\t", result_row[j]);
                    printf("\n");
                }

            }

            /*不要忘了关闭连接*/
            mysql_close(&my_connection);
        }
    }
}
#define maxn 1024
char sql[maxn];
int main(){
	strcpy(sql,"select * from basic_info;");
	query_sql(sql);
	return 0;
}
