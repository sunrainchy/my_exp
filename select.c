#include <sys/time.h>
#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>
/* 标准输入的文件描述符数值 */
#define STDIN 0
main()
{
struct timeval tv;
fd_set readfds;
/* 设置等待时间为 2 秒零 500,000 微秒 */
tv.tv_sec = 2;
tv.tv_usec = 500000;
FD_ZERO(&readfds);
FD_SET(STDIN, &readfds);
/* 因为我们只想等待输入,所以将 writefds 和 execeptfds 设为 NULL */
/* 程序将会在这里等待 2 秒零 500,000 微秒,除非在这段时间中标准输入有操作 */
select(STDIN+1, &readfds, NULL, NULL, &tv);
/* 测试 STDIN 是否在 readfds 集合中 */
if (FD_ISSET(STDIN, &readfds))
{
/* 在,则在标准输入有输入 */
printf("A key was pressed!\n");
}
else
{
/* 不在,则在标准输入没有任何输入 */
printf("Timed out.\n");
}
}

