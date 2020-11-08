#include "shared.h"

#define COL_NORM                        "\x0b"
#define COL_SEL                         "\x0c"
#define COL_TITLE                       "\x0d"
#define COL_SUCCESS                     "\x0e"
#define COL_SUCCESS_BG                  "\x0f"
#define COL_CRITICAL                    "\x10"
#define COL_CRITICAL_BG                 "\x11"
#define ICON(X,C)                       C " " X

#define TERMCMD(cmd)                    cspawn((char *[]){ "/usr/bin/st", "-e", cmd, NULL })

void cspawn(char *const *arg);
void csigself(int signal, int sigval);
ssize_t getcmdout(char *const *arg, char *cmdout, size_t cmdoutlen);
int readint(const char *path, int *var);
void uspawn(char *const *arg);
