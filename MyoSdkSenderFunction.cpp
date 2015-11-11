#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

// here goes the ip address of the Intel Ediso
#define SERVER "192.168.1.101"
#define BUFLEN 1024
/// here goes the port that are you using
#define PORT 21567

void die(char *s)
{
    perror(s);
    exit(1);
}

struct sockaddr_in si_other;
int s, i, slen=sizeof(si_other);
char buf[BUFLEN];
char message[BUFLEN];

void print()
{
    // Clear the current line
    std::cout << '\r';
    
    if (onArm) {
        
        std::string poseString = currentPose.toString();
        
        std::cout << '[' << (isUnlocked ? "unlocked" : "locked  ") << "] ";
        if(poseString == "fist")
        {
            
            std::string action = "STOP_MOVE";
            std::cout << action << "; " << lastCommand;
            lastCommand = action;
            
            if (sendto(s, action.c_str(), strlen(action.c_str()) , 0 , (struct sockaddr *) &si_other, slen)==-1)
            {
                die("sendto()");
            }
        }
        else if(poseString == "fingersSpread")
        {
            std::string action = "MOVE_FORWARD";
            std::cout << action << "; " << lastCommand;
            lastCommand = action;
            
            if (sendto(s, action.c_str(), strlen(action.c_str()) , 0 , (struct sockaddr *) &si_other, slen)==-1)
            {
                die("sendto()");
            }
        }
        else if(poseString == "waveIn")
        {
            std::string action = "LEFT_MOVE";
            std::cout << action << "; " << lastCommand;
            lastCommand = "STOP_MOVE";
            
            if (sendto(s, action.c_str(), strlen(action.c_str()) , 0 , (struct sockaddr *) &si_other, slen)==-1)
            {
                die("sendto()");
            }
        }
        else if(poseString == "waveOut")
        {
            std::string action = "RIGHT_MOVE";
            std::cout << action << "; " << lastCommand;
            lastCommand = "STOP_MOVE";
            
            if (sendto(s, action.c_str(), strlen(action.c_str()) , 0 , (struct sockaddr *) &si_other, slen)==-1)
            {
                die("sendto()");
            }
        }
        
    } else {
        // Print out a placeholder for the arm and pose when Myo doesn't currently know which arm it's on.
        std::cout << '[' << std::string(8, ' ') << ']' << "[?]" << '[' << std::string(14, ' ') << ']';
    }
    
    std::cout << std::flush;
}