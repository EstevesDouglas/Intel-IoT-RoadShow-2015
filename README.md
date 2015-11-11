# Intel-IoT-RoadShow-2015

## Função de Envio de Dados para Myo

Neste projeto utilzamos um macbook com o sistema operacional OSX El Capitan para enviar os dados para o Intel Edison através de troca de mensagens UDP.
Para isto, baixamos o SDK do Myo em https://developer.thalmic.com/downloads e compilamos o projeto hello-myo.xcodeproj dentro da pasta samples do SDK.

Neste exemplo modificamos o código do arquivo hello-myo.cpp na função print() da classe DataCollector. Nesta função temos acesso ao nome do gesto ativado 
naquele momento no Myo. Com este dado em mão apenas formatamos uma mensagens UDP e enviamos pela rede.

No inicio do arquivo adicionamos o seguinte código, com a declaração de variáveis e inclusão de bibliotecas:

```c++
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER "10.94.0.208"
#define BUFLEN 1024
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

Depois disso adicionamos código para descobrir o gesto detectado, formatar e enviar a mensagem para o código Python executando do outro lado no Intel Edison.

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

Logo basta substituir o código da função print() pelo código no arquivo MyoSdkSenderFunction.cpp.