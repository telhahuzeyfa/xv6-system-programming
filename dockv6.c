#include "user.h"
#include "jsmn.h"
#include "fcntl.h"

int main(int argc, char **argv) {
    printf(0,"Hello World\n");

    // int pipes[2];
    // pipe(&pipes[0]);


    // int fdarray[2]; /* File descriptors, fdarray[0] for read, fdarray[1] for write */
    // char buf[512];  /* Buffer to store chars */
    // int n;

    // pipe(fdarray);  /* creates pipes? */
    // write(fdarray[1], "hello", 5); /* writes "hello" to buf */
    // n = read(fdarray[0], buf, sizeof(buf));
    // // buf[] now contains 'h', 'e', 'l', 'l', 'o'

    exit();
}

void
create(void) 
{
    // int fd;
    // fd = open(/* "container_spec.json", O_RDWR */);
    return 0;
    /* dockv6 create container_spec.json */
    /* dockv6 is first argument, create second, and container_spec.json third, so argc, argv[0], and argv[1] respectively */
    /* Open .json file using fd */
}

/* Communicate with container to send .json file */
/* Use pipes? Does that mean dockv6 must fork for container.c to be child process then send the information that way? */
/* Take the argument of the .json file and make sure its valid, then parse and print */