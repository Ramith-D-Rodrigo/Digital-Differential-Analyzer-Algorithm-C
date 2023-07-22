#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

float min(float a, float b){
    return a > b ? b : a;
}

int main(int argc, char *argv[]){
    if(argc != 6){
        printf("Usage: ./main <PIXEL_COUNT> <X1> <Y1> <X2> <Y2>\n");
        return -1;
    }

    //creating the canvas and initalizing the required variables
    int pixelCount = atoi(argv[1]) + 1; //+1 because we need to think the 0th axes

    if(pixelCount <= 0){
        printf("Pixel Count should be greater than 0\n");
        return - 1;
    }

    char **canvas;
    canvas = (char **) malloc(sizeof(char*) * pixelCount); //allocate memory for holding the addresses of the arrays

    //allocating memory for storing the characters
    for(int i = 0; i < pixelCount; i++){
        canvas[i] = (char *) malloc(sizeof(char) * pixelCount);
    }

    for(int i = 0; i < pixelCount; i++){
        for(int j = 0; j < pixelCount; j++){
            canvas[i][j] = '.';
        }
    }

    int x1 = atoi(argv[2]);
    int y1 = atoi(argv[3]);

    int x2 = atoi(argv[4]);
    int y2 = atoi(argv[5]);

    if(x1 < 0 || x2 < 0 || y1 < 0 || y2 < 0){
        printf("Coordinate points should be greater than 0\n");
        return -1;
    }

    if(x1 > pixelCount || y1 > pixelCount || x2 > pixelCount || y2 > pixelCount){
        printf("Coordinate points should not exceed the Pixel Count\n");
        return -1;
    }

    //dda algorithm

    //preprocessing
    float dx = x2 - x1;
    float dy = y2 - y1;

    float m = dy/dx; //slopes

    int steps = max(abs(dx), abs(dy));

    //increment values for x and y
    float xInc = dx / steps;
    float yInc = dy / steps;

    //add the points
    for(int i = 0; i <= (int) steps; i++){
        //canvas[pixelCount - y][x] because 0,0 origin should start from bottom left and x should be horiztontal axis
        canvas[pixelCount - 1 - (int) roundf(y1 + yInc * i)][(int) roundf(x1 + xInc * i)] = '*';
    }

    //printing the canvas
    for(int i = 0; i < pixelCount; i++){
        for(int j = 0; j < pixelCount; j++){
            if(j == 0){ //y axis values
                printf("%2d", pixelCount - i - 1);
            }
            printf("%3c", canvas[i][j]);
        }
        printf("\n"); //next row
    }

    printf("  ");

    //print x axis values
    for(int i = 0; i < pixelCount; i++){
        printf("%3d", i);
    }

    return 0;
}