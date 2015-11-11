# Intel IoT RoadShow 2015

This project was developed in the 2015 IoT RoadShow 2015 in São Paulo, Brazil.

## Data Transmission Function To The Myo

In this project we used a macbook with the operating system OSX El Capitan to send the data to the Intel Edison through UDP messaging.
For this, we downloaded the SDK Myo in https://developer.thalmic.com/downloads and compile the ```hello-myo.xcodeproj``` project within the ```samples``` folder of the SDK.

In this example we modify the code ```hello-myo.cpp``` file in the ```print ()``` function of the ```DataCollector``` class. In this role we have access to the name of the activated gesture at that moment in Myo. With this data in hand we formatted the UDP messages and sent over the network.

The file add the following code beginning with the declaration of variables and inclusion of libraries:



```c++
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
```

After that we add the code to discover the gesture detected, format and send the message to the Python code running in the Intel Edison.

```c++
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
// there is more code in the .cpp file
```

Just simply replace the code in ```print()``` function by the code in ```MyoSdkSenderFunction.cpp``` file.