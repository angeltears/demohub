#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
char *px_ipc_name(const char *name)
{
    char *dir, *des, *slath;

    if((des = (char *)malloc(PATH_MAX)) == NULL)
            return NULL;

    if((dir = getenv("PX_IPC_NAME")) == NULL)
    {
#ifdef POSIX_IPC_PREFIX
    dir = POSIX_IPC_PREFIX;
#else
    dir = "/tmp/";
#endif
    }

    slath = ((dir[strlen(dir) - 1]== '/') ? "" : "/");
    snprintf(des, PATH_MAX, "%s%s%s", dir, slath, name);

    return des;
}
