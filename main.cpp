#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ncurses.h>
#include <ctype.h>

#define MAX_LEN 500
#define DEFAULT_COMPILER_PATH "/bin/g++"
// #define WORKSPACE_DIR "/tmp"
#define GCC_PATH "/bin/gcc"
#define GPP_PATH "/bin/g++"

static void
readline(char *buffer, int buflen)
{
    int old_curs = curs_set(1);
    int pos = 0;
    int len = 0;
    int x, y;

    getyx(stdscr, y, x);
    for (;;)
    {
        int c;

        buffer[len] = ' ';
        mvaddnstr(y, x, buffer, len + 1);
        move(y, x + pos);
        c = getch();

        if (c == KEY_ENTER || c == '\n' || c == '\r')
        {
            break;
        }
        else if (isprint(c))
        {
            if (pos < buflen - 1)
            {
                memmove(buffer + pos + 1, buffer + pos, len - pos);
                buffer[pos++] = c;
                len += 1;
            }
        }
        else if (c == KEY_LEFT)
        {
            if (pos > 0)
                pos -= 1;
        }
        else if (c == KEY_RIGHT)
        {
            if (pos < len)
                pos += 1;
        }
        else if (c == KEY_BACKSPACE)
        {
            if (pos > 0)
            {
                memmove(buffer + pos - 1, buffer + pos, len - pos);
                pos -= 1;
                len -= 1;
            }
        }
        else if (c == KEY_DC)
        {
            if (pos < len)
            {
                memmove(buffer + pos, buffer + pos + 1, len - pos - 1);
                len -= 1;
            }
        }
    }
    buffer[len] = '\0';
    if (old_curs != ERR)
        curs_set(old_curs);
}

char *initWorkSpace()
{
    time_t rawtime;
    struct tm *timeinfo;
    char buffer[80];
    char *path = (char *)malloc(100 * sizeof(char));

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(buffer, 80, "/tmp/auto_gcc_%Y_%m_%d_%H_%M_%S", timeinfo);
    strcat(path, buffer);

    mkdir(path, 0777);
    return path;
}

int main(int argc, char **argv)
{
    char command[MAX_LEN] = "1";
    char compiler[50] = DEFAULT_COMPILER_PATH;
    char commands_buffer[10000];
    char exit_command[] = "ag_ex";
    char* base_source_head =
        "#include <stdio.h>"
        "using namespace std;"
        "int main(){";
    char* base_source_bottom =
        "return 0;"
        "}";

    char *workspace_path = initWorkSpace();
    initscr();
    raw();
    keypad(stdscr, TRUE);

    printw("AutoGCC with compiler: %s\nProject workspace path: %s\nMode: 0", compiler, workspace_path);
    refresh();
    while (strcmp(command, exit_command) != 0)
    {
        printw(">>> ");
        refresh();
        readline(command, MAX_LEN);
        printw(">>> %s\n", command);
        // Check for internal AutoGCC command (prefix: ag_)
        if (3 <= strlen(command) && ( strncmp("ag_", command, 3) == 0 )) {
            if (!strcmp(command, "ag_sw_gcc")){
                strcpy(compiler, GCC_PATH);
                printw("Switched to gcc: %s\n", compiler);
            }
            else if (!strcmp(command, "ag_sw_g++")){
                strcpy(compiler, GPP_PATH);
                printw("Switched to g++: %s\n", compiler);
            }
        } else { 
            // Execute compiler command
            
        }
        refresh();
    }
    endwin();

    return 0;
}