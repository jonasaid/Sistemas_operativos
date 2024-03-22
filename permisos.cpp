#include<stdio.h>
#include<stdlib.h>

int main(int argc, char **argv)
{
char mode[] = "0777";
char buf[100] = "/home/user/example.txt";
int i;
i = strtol(mode, 0, 8);
chmod (buf,i);
{
fprintf(stderr, "%s: error in chmod(%s, %s) - %d (%s)\n",
argv[0], buf, mode, errno, strerror(errno));
exit(1);
}
return(0);
}