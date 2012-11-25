#include <stdio.h>
#include <unistd.h>

int
main()
{
    FILE *fp;
    char buf[1024];
    char tty[32];

    ttyname_r(fileno(stdin), tty, sizeof(tty));

    fp = freopen("./freopen.c", "r", stdin);
    fgets(buf, sizeof(buf), stdin);
    printf("%s", buf);

    fp = freopen(tty, "r", stdin);
    fgets(buf, sizeof(buf), stdin);
    printf("%s", buf);

    return 0;
} 
