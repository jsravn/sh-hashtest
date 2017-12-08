#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

static inline unsigned int
ip_vs_sh_hashkey(const struct in_addr *addr, uint16_t port)
{
    uint32_t r;
    r = (ntohs(port) + ntohl((uint32_t) addr->s_addr))*UINT32_C(2654435761);
    return r & ((1<<8)-1);
}

int main(int argc, char** argv) {
    char *ip_arg;
    char *port_arg;
    int table[256];
    const int entries = 3;
    const int weight = 3;
    int i, cur_weight, cur_backend;
    uint16_t port;
    unsigned int hashkey;
    struct in_addr *addr;

    port_arg = argv[1];
    ip_arg = strsep(&port_arg, ":");

    addr = malloc(sizeof(struct in_addr));
    inet_pton(AF_INET, ip_arg, addr);
    port = (uint16_t) atoi(port_arg);

    hashkey = ip_vs_sh_hashkey(addr, port);

    i = 0;
    cur_weight = weight;
    cur_backend = 0;
    while (i < 256) {
        table[i] = cur_backend;
        i++;
        cur_weight--;
        if (cur_weight == 0) {
            cur_backend = (cur_backend + 1) % entries;
            cur_weight = weight;
        }
    }
        
    printf("%d\n", table[hashkey] + 1);
}

