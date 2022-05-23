#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char **argv)
{
    DIR *dp;
    struct dirent *sd = NULL;
    dp = opendir(argv[1]);
    if (dp == NULL) {
        perror("open testdir111");
        exit(1);
    }

    while (sd = readdir(dp)) {
        printf("%s\n", sd->d_name);
    }

    printf("------------\n");

    closedir(dp);

    return 0;
}

