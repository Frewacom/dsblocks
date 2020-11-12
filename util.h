#include <X11/Xresource.h>
#include "shared.h"

#define COL_NORM                        "\x0b"
#define COL_SEL                         "\x0c"
#define COL_TITLE                       "\x0d"
#define COL_SUCCESS                     "\x0e"
#define COL_SUCCESS_BG                  "\x0f"
#define COL_CRITICAL                    "\x10"
#define COL_CRITICAL_BG                 "\x11"

#define NO_ICON                         ""
#define ICON(I)                         I " "
#define BLOCK(C1,I,C2,L)                C1 " " I C2 L
#define BLOCK_NORM(I,L)                 BLOCK(COL_NORM, I, COL_NORM, L)
#define BLOCK_SUCCESS(I,L)              BLOCK(COL_SUCCESS, I, COL_SUCCESS, L)
#define BLOCK_CRITICAL(I,L)             BLOCK(COL_CRITICAL, I, COL_CRITICAL, L)
#define BLOCK_SUCCESS_BG(I,L)           BLOCK(COL_SUCCESS_BG, I, COL_SUCCESS_BG, L)
#define BLOCK_CRITICAL_BG(I,L)          BLOCK(COL_CRITICAL_BG, I, COL_CRITICAL_BG, L)

#define TERMCMD(cmd)                    cspawn((char *[]){ "/usr/bin/st", "-e", cmd, NULL })

void printempty(char *str);
void cspawn(char *const *arg);
void csigself(int signal, int sigval);
ssize_t getcmdout(char *const *arg, char *cmdout, size_t cmdoutlen);
int readint(const char *path, int *var);
void uspawn(char *const *arg);
