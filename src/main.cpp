
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include "hdfs.h"

static bool flag = true;
char __log_path__[100];
void handler(int);



int hdfs_demo(const char* writePath,char* content,int len) {
	char buff[100];
	char* ret=NULL;
    hdfsFS fs = hdfsConnect("127.0.0.1", 9000); 
    hdfsFile writeFile = hdfsOpenFile(fs, writePath, O_WRONLY | O_CREAT , 0, 0, 0);
	ret=hdfsGetWorkingDirectory(fs,buff,100);
	printf("buff %s return %s\n",buff,ret);
    if(!writeFile) {
          fprintf(stderr, "Failed to open %s for writing!\n", writePath);
          exit(-1);
    }
    char* buffer = "Hello, World!";
    tSize num_written_bytes = hdfsWrite(fs, writeFile, (void*)buffer, strlen(buffer)+1);
	printf("%d writed\n",num_written_bytes);
    if (hdfsFlush(fs, writeFile)) {
           fprintf(stderr, "Failed to 'flush' %s\n", writePath);
          exit(-1);
    }
    hdfsCloseFile(fs, writeFile);
}



int deamon_demo(int argc, char *argv[]){
	time_t t;
    getcwd(__log_path__, 100);
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGQUIT, &act, NULL);
    sigaction(SIGUSR1, &act, NULL);
    sigaction(SIGUSR2, &act, NULL);
    sigaction(50, &act, NULL);

    for (size_t i = 0; i < argc; i++)
    {
        if (strcmp("--log-data", argv[i]) == 0)
        {
            memset(__log_path__, '\0', 100);
            strncpy(__log_path__, argv[i + 1], 100);
        }
        if (strcmp("--daemon", argv[i]) == 0)
        {
            if (-1 == daemon(0, 0))
            {
                printf("daemon error\n");
                exit(1);
            }
        }
    }
    while (flag)
    {
        int fd = open(__log_path__, O_WRONLY | O_CREAT | O_APPEND, 0644);
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

    int fd = open(__log_path__, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1)
    {
        printf("open error\n");
    }
    getcwd(buf, 100);
    write(fd, buf, strlen(buf));
    memset(buf, '\0', 100);
    sprintf(buf, "I got a signal %d\nI'm quitting.\n", sig);
    write(fd, buf, strlen(buf));
    close(fd);
}

int main(int argc, char *argv[])
{
    char* content="Hello Hadoop C API!!!";
	hdfs_demo("/usr1/txt.txt",content,strlen(content));
	return 0;
}

