
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>

static bool flag = true;
void handler(int);

int main(int argc, char *argv[])
{
    time_t t;

    for (size_t i = 0; i < argc; i++)
    {
        if (strcmp("--daemon", argv[i]) == 0)
        {
            if (-1 == daemon(0, 0))
            {
                printf("daemon error\n");
                exit(1);
            }
            struct sigaction act;
            act.sa_handler = handler;
            sigemptyset(&act.sa_mask);
            act.sa_flags = 0;
            if (sigaction(SIGQUIT, &act, NULL))
            {
                printf("sigaction error.\n");
                exit(0);
            }
        }
    }
    while (flag)
    {
        int fd = open("/tmp/daemon.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd == -1)
        {
            printf("open error\n");
        }
        t = time(0);
        char *buf = asctime(localtime(&t));
        write(fd, buf, strlen(buf));
        close(fd);
        sleep(5);
    }
    return 0;
}
void handler(int sig)
{
    printf("I got a signal %d\nI'm quitting.\n", sig);
    char buf[100];
    int fd = open("/tmp/daemon.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        printf("open error\n");
    }
    sprintf(buf, "I got a signal %d\nI'm quitting.\n", sig);
    write(fd, buf, strlen(buf));
    close(fd);
    flag = false;
}
