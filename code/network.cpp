#include <stdio.h>
#include <time.h>
#include "E101.h" //ENGR101 library

int main (){
	init();
		
	char server_addr[15];
	server_addr[0]='1';
	server_addr[1]='0';
	server_addr[2]='3';
	server_addr[3]='.';
	server_addr[4]='1';
	server_addr[5]='9';
	server_addr[6]='5';
	server_addr[7]='.';
	server_addr[8]='6';
	server_addr[9]='.';
	server_addr[10]='1';
	server_addr[11]='9';
	server_addr[12]='6';
	connect_to_server(server_addr,1024);
	
	char message[24];
	message[0]='P';
	message[1]='l';
	message[2]='e';
	message[3]='a';
	message[4]='s';
	message[5]='e';
	
	
	send_to_server(message);
	
	receive_from_server(message);
	printf("%s", message);
	
	send_to_server(message);

return 0;	
}
