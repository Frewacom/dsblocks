#include "shared.h"

#define COL_NORM                        "\x0b"
#define COL_SEL                         "\x0c"
#define COL_TITLE                       "\x0d"
#define COL_SUCCESS                     "\x0e"
#define COL_SUCCESS_BG                  "\x0f"
#define COL_CRITICAL                    "\x10"
#define COL_CRITICAL_BG                 "\x11"

#define LABEL(X)                        X COL_NORM
#define ICON_EMPTY                      " "
#define ICON(C1,X,C2)                   C1 " " X C2
#define ICON_NORM(X)                    ICON(COL_NORM, X, COL_NORM)
#define ICON_SUCCESS(X)                 ICON(COL_SUCCESS, X, COL_SUCCESS)
#define ICON_CRITICAL(X)                ICON(COL_CRITICAL, X, COL_CRITICAL)
#define ICON_SUCCESS_BG(X)              ICON(COL_SUCCESS_BG, X, COL_SUCCESS_BG)
#define ICON_CRITICAL_BG(X)             ICON(COL_CRITICAL_BG, X, COL_CRITICAL_BG)

#define TERMCMD(cmd)                    cspawn((char *[]){ "/usr/bin/st", "-e", cmd, NULL })

void cspawn(char *const *arg);
void csigself(int signal, int sigval);
ssize_t getcmdout(char *const *arg, char *cmdout, size_t cmdoutlen);
int readint(const char *path, int *var);
void uspawn(char *const *arg);
