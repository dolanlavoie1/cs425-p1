#define _POSIX_C_SOURCE 200809L

#include "lab.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifdef TEST
#define main main_exclude
#endif

static void print_usage()
{
    printf("Usage: %s -f <from> -t <to> [-s subject] [-b body] [-p port]\n"
           "          [-H helo-host] <server>\n\n"
           "  -f <from>       envelope sender, for example you@example.com\n"
           "  -t <to>         envelope recipient\n"
           "  -s <subject>    subject line (default: empty)\n"
           "  -b <body>       message body (default: read from stdin)\n"
           "  -p <port>       port or service name (default: 25)\n"
           "  -H <helo-host>  host name sent with HELO (default: localhost)\n"
           "  <server>        host name or address of the mail server\n");
}

int main(int argc, char *argv[])
{
    const char *from = NULL;
    const char *to = NULL;
    const char *subject = "";
    const char *body = NULL;
    const char *port = "25";
    const char *helo_host = "localhost";
    const char *server = NULL;
    int opt;

    if (argc == 1)
    {
        print_usage();
        return 0;
    }

    opterr = 0;
    while ((opt = getopt(argc, argv, ":f:t:s:b:p:H:")) != -1)
    {
        switch (opt)
        {
        case 'f':
            from = optarg;
            break;
        case 't':
            to = optarg;
            break;
        case 's':
            subject = optarg;
            break;
        case 'b':
            body = optarg;
            break;
        case 'p':
            port = optarg;
            break;
        case 'H':
            helo_host = optarg;
            break;
        case ':':
            fprintf(stderr, "Option -%c requires an argument.\n", optopt);
            print_usage();
            return 1;
        case '?':
            fprintf(stderr, "Unknown option: -%c.\n", optopt);
            print_usage();
            return 1;
        default:
            return 1;
        }
    }

    if (optind != argc - 1 || from == NULL || to == NULL)
    {
        fprintf(stderr, "Options -f, -t, and <server> are required.\n");
        print_usage();
        return 1;
    }

    server = argv[optind];

    
    return 0;
}