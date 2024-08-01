#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

void errExit(const char *msg);

int main(int argc, char **argv)
{
    int fd;
    ssize_t bytes;

    openlog(NULL, 0, LOG_USER);
    if (argc != 3)
    {
        errExit("Wrong format.\r\n");
    }

    fd = open(argv[1], O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
    if (fd == -1)
    {
        errExit("Cannot open file\r\n");
    }
    bytes = write(fd, argv[2], strlen(argv[2]));
    close(fd);
    if (bytes == -1)
        errExit("Cannot write.\r\n");
    else
        syslog(LOG_USER, "Writing %s to %s", argv[2], argv[1]);
    closelog();

    return 0;
}

void errExit(const char *msg)
{
    syslog(LOG_ERR, "%s", msg);
    closelog();
    exit(1);
}