#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "make_log.h"

#define MODULE_NAME "fdfs_client_test"
#define PROC_NAME   "fdfs_client_test_main"
#define FILE_NAME_LEN   (256)

int main(int argc, char *argv[])
{
    char *file_name = NULL;
    char file_id[FILE_NAME_LEN] = { 0 };
    int pid;
    int pfd[2] = { 0 };

    if(argc < 2)
    {
        printf("argc error: fdfs_client_test filename\n");
        return 1;
    }

    file_name = argv[1];
    if(pipe(pfd) < 0)
    {
        LOG(MODULE_NAME, PROC_NAME, "[error] pipe error");
        return 1;
    }

    pid = fork();
    if(pid < 0)
    {
        LOG(MODULE_NAME, PROC_NAME, "[error] fork error");
        return 1;
    }

    if(pid == 0)
    {
        //child
        close(pfd[0]);
        dup2(pfd[1], STDOUT_FILENO);
        execlp("fdfs_upload_file", "fdfs_upload_file", "./conf/client.conf", file_name, NULL);
        LOG(MODULE_NAME, PROC_NAME, "[error] exec fdfs_upload_file error");
    }
    else if(pid > 0)
    {
        //parent
        close(pfd[1]);
        wait(NULL);
        read(pfd[0], file_id, FILE_NAME_LEN);
        printf("exec fdfs_upload_file succ: file_name = %s", file_id);
    }

    return 0;
}
