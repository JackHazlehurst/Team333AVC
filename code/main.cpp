#include <stdio.h>
#include <time.h>
#include "E101.h" //ENGR101 library

/**
 * will get a row of pixels from the camera
 * accepts the row in the image it needs to look at 
 */
int pixelLine(int row){
	int THRESHOLD = 110;
	int WIDTH = 320;
	char pixelLine[WIDTH];
	for(int i = 0; i < WIDTH; i++){
		//gets the pixel and makes it white or black
		int pixel = get_pixel(row, i, 3);
		if(pixel < THRESHOLD){//black
			pixel = 0;
			set_pixel(row, i , 1, 1, 1);
		}
		else{//white
			pixel = 1;
			set_pixel(row, i ,255, 255, 255);
		}
		pixelLine[i] = pixel;
	}
	//display_picture(1, 0);
    //printf("\n");
    //calculates the average white pixel index relative to the center collumn 
    int total = 0;
    int numWhite = 0;
    for(int j = 0; j < WIDTH; j++){
		if(pixelLine[j] == 1){
			total = total + pixelLine[j] * (j - (WIDTH/2));
			numWhite++;
		}
	}
	if(numWhite > 300){//if all white pixels
			return 10001;
	}
	if(numWhite > 4){
		return total/numWhite;
	}
	//If there are no white pixels
	return 10000;
}

int averageError(){
	int total = 0;
	int count = 0;
	
	for(int i = 140; i < 181; i = i + 5){
		total += pixelLine(i);
		count++;
	}
	
	total /= count;
	display_picture(1, 0);
	return total;
}

/**
 * will get a collumn of pixels from the camera
 * accepts the collumn in the image it needs to look at 
 */
int pixelCol(int col){
	
	//display_picture(1, 0);
	
	
	int THRESHOLD = 100;
	int HEIGHT = 240;
	char pixelLine[HEIGHT];
	for(int i = 0; i < HEIGHT; i++){
		//gets the pixel and makes it white or black
		int pixel = get_pixel(i, col, 3);
		if(pixel < THRESHOLD){//black
			pixel = 0;
			set_pixel(i, col, 1, 1, 1);
		}
		else{//white
			pixel = 1;
			set_pixel(i, col, 255, 255, 255);
		}
		pixelLine[i] = pixel;
	}
	//display_picture(1, 0);
    //printf("\n");
    //calculates the average white pixel index relative to the center collumn 
    int total = 0;
    int numWhite = 0;
    for(int j = 0; j < HEIGHT; j++){
		if(pixelLine[j] == 1){
			total = total + pixelLine[j] * (j - (HEIGHT/2));
			numWhite++;
		}
	}
	return numWhite;
}

/**
* Makes the robot turn left until it has the white line in the center again
*/
void turnLeft(){
	int error = pixelLine(160);
		while(error > 80 || error < -80){
			set_motor(1, -40);
			set_motor(2, 40);
			error = pixelLine(160);
			sleep1(0, 12500);
		}
}

/**
 * makes the robot move
 * accepts the ideal speed, error, and scaling factor as a arguments
*/
void move(int speed, int error, double factor){
	if(error == 10000){//backwards
		set_motor(1, -30);
		set_motor(2, -40);
	}
	else{
		//calculates speed for each wheel
		int leftSpeed = speed - (int)((double)error*factor);
		int rightSpeed = speed + (int)((double)error*factor);
		//sets speed for each wheel
		set_motor(1, leftSpeed);
		set_motor(2, rightSpeed);
	}
	sleep1(0, 12500);//80 Hz
}

void gate(){
	char server_addr[15]={'1','3','0','.','1','9','5','.','6','.','1','9','6'};
	connect_to_server(server_addr,1024);
	char message[24]={'P','l','e','a','s','e'};
	send_to_server(message);
	receive_from_server(message);
	send_to_server(message);
}

int main(){
	init();//initialises the hardware
	//Infinite loop for running the robot
	gate();
	while(true){
		take_picture();
		int error = averageError();
		printf("%d\n", error);
		if(error < 254 && error > -254 || error == 10000){
			move(35, error, 0.3);
		}
		else{
			printf("Speed\n");
		}
		
		if(error == 10001){
			break;
		}
	}
	printf("Quadrant 3\n");
	sleep1(0, 200000);
	sleep1(10, 0);
	//quadrant 3
	while(true){
		take_picture();
		int error = averageError();
		printf("%d\n", error);
		if(error < 254 && error > -254 || error == 10000){
			move(35, error, 0.3);
		}
		else{
			printf("Speed");
		}

		if(error == 10001){
			printf("Turning left...");
			fflush(stdout);
			turnLeft();
			printf("Finished turning");
			fflush(stdout);
		}
		printf("%d\n", error);
	}
}
