#include <stdio.h>
#include <time.h>
#include "E101.h" //ENGR101 library

//will get a row of pixels from the camera
//accepts the row in the image it needs to look at
int pixelLine(int row){
	int THRESHOLD = 100;
	int WIDTH = 320;
	take_picture();
	//display_picture(0,10);
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
	if(numWhite > 4){
		return total/numWhite;
	}
	//If there are no white pixels
	return 10000;
}

//makes the robot move
//accepts the ideal speed, error, and scaling factor as a arguments
void move(int speed, int error, double factor){
	if(error == 10000){//backwards
		set_motor(1, -25);
		set_motor(2, -35);
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

int main(){
	init();//initialises the hardware
	//Infinite loop for running the robot
	while(true){
		int error = pixelLine(160);
		move(35, error, 0.33);
		
		//printf("%d\n", error);
	}
}
