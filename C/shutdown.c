#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define CLEAR_SCREEN "\033[H\033[J"

#ifdef _WIN32
    #define SHUTDOWN_CMD "cmd /c shutdown -s -t"
    #define CANCEL_SHUTDOWN "shutdown -a"
#else
    #define SHUTDOWN_CMD "sleep %d && sudo shutdown -h now "
    #define CANCEL_SHUTDOWN "sudo shutdown -c"
#endif

void ClearTerminal();
void ClearBuffer();

int main()
{
    char selection;
    int shutdownTimer;
    int secondToMinuteMultiplier = 60;

    //Take user name
    const char* username = getenv("USERNAME");

    if (username == NULL) 
    {
        printf("Unable to fetch username.\n");
        return 1;
    }

    while(1)
    {
        printf("Enter '1' to set the shutdown timer.\nEnter '2' to cancel the shutdown.\nEnter '3' to exit.\n");
        scanf(" %c", &selection);
        ClearBuffer();

        if(selection == '1')
        {
            printf("How many minutes later do you want the computer to shutdown: ");
            scanf(" %d", &shutdownTimer);

            char command[200];
            sprintf(command, "runas /user:%s\\Administrator \"%s %d\"", username, SHUTDOWN_CMD, shutdownTimer * secondToMinuteMultiplier);
            
            system(command);  //Run the command

            ClearTerminal();
            printf("The system will be shut down in %d minutes!\n", shutdownTimer * secondToMinuteMultiplier);
        }
        else if(selection == '2')
        {
            char command[200];
            sprintf(command, "runas /user:%s\\Administrator \"%s\"", username, CANCEL_SHUTDOWN);
            
            system(command);

            ClearTerminal();;
            printf("The shutdown has been canceled...\n");
        }
        else if(selection == '3')
        {
            printf("Program is terminating...\n");
            break;
        }
        else
        {
            ClearTerminal();
            printf("Invalid option!\n");
        }
    }

    return 0;
}

void ClearTerminal()
{
    printf("%s", CLEAR_SCREEN);
}

void ClearBuffer()
{
    char c;
    while((c = getchar()) != EOF && c != '\n');
}
