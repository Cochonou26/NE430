#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include "Tests/MyAlgo.h1"

#define MAXLEN 100

Node *root = NULL;

// This function must not be modified !!! 
int loadFile(char *path) {
    FILE *fi;
    char s[MAXLEN], *p, *start;
    struct in_addr c;
    unsigned int addr, netmask, gw;

    // first sanity check
    if (!path) return 0;
    if ((fi = fopen(path, "r")) == NULL) return 0;

    // read file line by line (max = MAXLEN )
    while (fgets(s, MAXLEN, fi) != NULL) {
        s[MAXLEN - 1] = 0;
        p = start = s;
        // seek for blank char
        while (*p && (*p != ' ')) p++;
        if (p > start) {
            *p = 0;
            p++;
            if (inet_aton(start, &c) == 0) continue;
            addr = htonl(c.s_addr);
        }
        // skip remaining blank char
        while (*p && (*p == ' ')) p++;

        // stat a new search for blank char
        start = p;
        while (*p && (*p != ' ')) p++;
        if (p > start) {
            *p = 0;
            p++;
            if (inet_aton(start, &c) == 0) continue;
            netmask = htonl(c.s_addr);
        }
        // skip remaining blank char
        while (*p && (*p == ' ')) p++;

        // stat a new search for blank '\n' char
        start = p;
        while (*p && (*p != '\n')) p++;
        if (p > start) {
            *p = 0;
            p++;
            if (inet_aton(start, &c) == 0) continue;
            gw = htonl(c.s_addr);
        }

        // call your function to insert entry to routing table
        insertMyAlgo(addr, netmask, gw);
    }
    fclose(fi);
    return 1;
}

// only for debug purpose might be modified !
int main(int argc, char *argv[]) {
    char s[MAXLEN];
    int addr;
    struct in_addr a;

    initMyAlgo();
    if (loadFile("routes")) {
        while (fgets(s, MAXLEN, stdin) != NULL) {
            s[MAXLEN - 1] = 0;
            if (inet_aton(s, &a) == 0) continue;
            addr = htonl(a.s_addr);
            a.s_addr = htonl(lookupMyAlgo(addr));
            printf("%s\n", inet_ntoa(a));
        }
    }
    return 0;
}