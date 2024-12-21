#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>


#define PORT 8083

void createClient(){

    // fd of file descriptor
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd == 0){
        std::cout << "Socket failed" << std::endl;
        return;
    }

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = ntohs(PORT);
    address.sin_addr.s_addr = ntohl(INADDR_LOOPBACK); // 127.0.0.1

    int conn = connect(fd, (const struct sockaddr*)&address, sizeof(address));

    if(conn < 0){
        std::cout << "Connection failed" << std::endl;
        return;
    }


    char msg[] = "Hello from client";
    write(fd, msg, strlen(msg));
    

    char buffer[1024] = {0};
    ssize_t n = read(fd, buffer, 1024);

    if(n < 0){
        std::cout << "Read failed" << std::endl;
        return;
    }

    std::cout << "Server says: " << buffer << std::endl;

    close(fd);

}


int main(int argc, char *argv[])
{
    
    createClient();
    
    return 0;
}


