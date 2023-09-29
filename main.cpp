#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

#define MAX_LEN 500
#define COMPILER_PATH "/bin/g++"
// #define WORKSPACE_DIR "/tmp"
// #define GPP_PATH "/bin/g++"

char* initWorkSpace(){
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];
    char* path = (char*) malloc(100 * sizeof(char));


    time (&rawtime);
    timeinfo = localtime (&rawtime);
    strftime(buffer, 80, "/tmp/auto_gcc_%Y_%m_%d_%H_%M_%S", timeinfo);
    strcat(path, buffer);

    mkdir(path, 0777);
    return path;
    
    
}

int main(int argc, char **argv){
    char command[MAX_LEN] = "1";
    char compiler[50];
    char exit_command[] = "exit\n";
    // char* base_source_head = 
    //     "#include <stdio.h>"
    //     "using namespace std;"
    //     "int main(){";
    // char* base_source_bottom = 
    //     "return 0;"
    //     "}";

    char* workspace_path = initWorkSpace();

    printf("AutoGCC with compiler: %s\nProject workspace path: %s\n", COMPILER_PATH, workspace_path);
    while (strcmp(command, exit_command) != 0){
        printf(">>> ");
        fgets(command, MAX_LEN, stdin);
        printf("%s\n", command);
    }
    
    return 0;
}