#include <stdio.h>
#include <time.h>
#include "E101.h" //ENGR101 library

//will get a row of pixels from the camera 
int camera(int row, int numCols){
	take_picture();
	display_picture(1,0);
	char pixelLine[numCols];
	for(int i = 0; i < numCols; i++){
		//gets the pixel and makes it white or black
		int pixel = get_pixel(row, i, 3);
		if(pixel < 127){
			pixel = 0;
		}
		else{
			pixel = 1;
		}
		pixelLine[i] = pixel;
		//printf("%d ", pixelLine[i]);
	}
    //printf("\n");
    //calculates the average white pixel index relative to the center collumn 
    int total;
    int numWhite;
    for(int j = 0; j < numCols; j++){
		if(pixelLine[j] == 1){
			total = total + pixelLine[j] * (j - (numCols/2));
			numWhite++;
		}
	}
	return total/numWhite;
}

//makes the robot move 
int move(){
	int speed = 100;
	set_motor(1, speed);
	set_motor(2, speed);
	sleep1(1, 0);
	set_motor(1, 0);
	set_motor(2, 0);
	
	return 0;
}

int main(){
	init();//initialises the hardware
	printf("Average white pixel position %d\n", camera(160, 320));
	move();
}
