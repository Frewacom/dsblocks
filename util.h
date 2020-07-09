#include "shared.h"

#define COL0			""
#define COL1			""
#define COL2			""
#define COL3			""
#define COL4			""
#define COL5			""
#define COL6			""
#define COL7			""
#define COL8			""

#define HTSPT			COL1 "" COL0
#define CLOCK			COL1 "" COL0
#define CAL			COL1 "" COL0
#define VOL0			COL1 "" COL0
#define VOL1			COL1 "" COL0
#define CTMP0			COL1 "" COL0
#define CTMP1			COL1 "" COL0
#define BAT0			COL1 "" COL0
#define BAT1			COL1 "" COL0
#define BAT2			COL1 "" COL0
#define BAT3			COL1 "" COL0
#define BAT4			COL1 "" COL0
#define BAT5			COL1 "" COL0

ssize_t getcmdout(char *const *arg, char *cmdout, size_t cmdoutlen);
int readint(const char *path, int *var);
void cspawn(char *const *arg);
void uspawn(char *const *arg);
