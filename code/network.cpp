#include <stdio.h>
#include <time.h>
#include "E101.h" //ENGR101 library

int main (){
	init();
	char server_addr[15]={'1','3','0','.','1','9','5','.','6','.','1','9','6'};
	connect_to_server(server_addr,1024);
	char message[24]={'P','l','e','a','s','e'};
	send_to_server(message);
	receive_from_server(message);
	send_to_server(message);
	printf("%s", message);
	return 0;	
}
