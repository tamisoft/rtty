/*
 * MIT License
 *
 * Copyright (c) 2019 Jianhui Zhao <zhaojh329@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "utils.h"
#include <stdio.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <uwsc/log.h>

static const char *port2str(int port)
{
    static char buffer[sizeof("65535\0")];

    if (port < 0 || port > 65535)
        return NULL;

    snprintf(buffer, sizeof(buffer), "%u", port);

    return buffer;
}

int parse_address(const char *host, int port, int socktype, struct sockaddr *addr, int *addr_len)
{
    struct addrinfo *result, *rp;
    struct addrinfo hints = {
        .ai_family = AF_INET,
        .ai_socktype = socktype,
        .ai_flags = AI_ADDRCONFIG
    };

    if (getaddrinfo(host, port2str(port), &hints, &result))
        return -1;

    for (rp = result; rp != NULL; rp = rp->ai_next) {
        if (rp->ai_family == AF_INET) {
            memcpy(addr, rp->ai_addr, sizeof(struct sockaddr));
            *addr_len = rp->ai_addrlen;
            break;
        }
    }

free_addrinfo:
    freeaddrinfo(result);
    return 0;
}

int find_login(char *buf, int len)
{
    FILE *fp = popen("which login", "r");
    if (fp) {
        if (fgets(buf, len, fp))
            buf[strlen(buf) - 1] = 0;
        pclose(fp);

        if (!buf[0])
            return -1;
        return 0;
    }

    return -1;
}

bool valid_id(const char *id)
{
    while (*id) {
        if (!isalnum(*id) && *id != '-' && *id != '_')
            return false;
        id++;
    }

    return true;
}

