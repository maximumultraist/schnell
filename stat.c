#include "stat.h"
 
int mystat(int argc, char **argv)
{
    if (argc!=1) {
        fprintf(stderr, "Usage: stat <file or directory>\n");
        return -1;
    }
    struct stat fileStat;
    if (stat(argv[1], &fileStat)<0) {
        fprintf(stderr, "Error: file or directory \'%s\' does not exist.\n", argv[1]);
        return -2;
    }
 
    printf("File: %s\n",argv[1]);
    printf("---------------------------\n");
    printf("Size: %d bytes\t\t",fileStat.st_size);
    printf("Blocks: %d\t",fileStat.st_blocks);
    printf("IOBlocks: %d\t\n",fileStat.st_blksize);

    printf("Device: %d\t",fileStat.st_dev);
    printf("Inode: %d\t",fileStat.st_ino);
    printf("Links: \t%d\n",fileStat.st_nlink);

    printf("Access: ");

    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf("\tUid: %d\t",fileStat.st_uid);
    printf("Gid: %d\t\n",fileStat.st_gid);

    printf("Access: %d\t",fileStat.st_atime);
    printf("Modify: %d\t",fileStat.st_mtime);
    printf("Change: %d\t\n",fileStat.st_ctime);
    return 0;
}