 #include <stdio.h>
 #include <mysql.h>
 int main(int argc,char *argv[])
 {
	 MYSQL conn;
	 int res;   
	 mysql_init(&conn);//初始化 连接
	 if(mysql_real_connect(&conn,"localhost","root","940407","test",0,NULL,CLIENT_FOUND_ROWS))
	 {
		printf("数据库连接成功/n");
		res = mysql_query(&conn,"insert into test values('user','123456')");//插入语句，成功返回0，失败返回1
		if(res)
		{
			printf("语句执行失败/n");
			mysql_close(&conn);//记得关闭连接
		}
		else
		{
			printf("语句执行成功/n");
			mysql_close(&conn);
		}
	 }       
	 return 0;
 }
