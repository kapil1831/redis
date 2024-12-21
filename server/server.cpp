#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>


#define PORT 9131

void die(const char *msg){
    std::cerr << msg << std::endl;
    exit(1);
}

void do_processing(int conn_fd, char *buffer){
    int n = read(conn_fd, buffer, 1024);

    if(n < 0){
        die("read()");
    }

    std::cout << "Client: " << buffer << std::endl;

    char wbuf[] = "world";

    write(conn_fd, wbuf, strlen(wbuf));
}

// [TODO] may create a class to handle the server
void createServer(){
    
    // fd of file descriptor
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    //configure socket to reuse address
    // [TODO] use a function for the configuration step.
    int val = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

    // bind the socket to localhost port 8080
    //[TODO] use a function for the binding step.
    struct sockaddr_in address = {};
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address,sin_addr.s_addr = ntohl(0);  // INADDR_ANY

    int rv = bind(fd, (struct sockaddr *)&address, sizeof(address));

    if(rv < 0){
        std::cerr << "Error binding socket to address" << std::endl;
        return;
    }

    // listen for incoming connections
    rv = listen(fd, SOMAXCONN); //SOMAXCONN is the maximum number of connections that can be queued, here it is 128;

    if(rv){
        die("listen()");
    }


    // accept incoming connections
    while(true){
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int conn_fd = accept(fd, (struct sockaddr *)&client_addr,   &client_addr_len);

        if(conn_fd < 0){
            die("accept()");
        }

        // read data from the client
        char buffer[1024] = {};

        do_processing(conn_fd, buffer);

        // close the connection
        close(conn_fd);
    }


}

int main(int argc, char *argv[])
{
    // fd of file descriptor

    return 0;
}