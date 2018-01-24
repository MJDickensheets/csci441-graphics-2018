#include <iostream>

#include "bitmap_image.hpp"

float f(float a[2], float b[2], float p[2]){
	return (a[1]-b[1])*p[0] + (b[0]-a[0])*p[1] + a[0]*b[1] - b[0]*a[1];
}


int main(int argc, char** argv) {
    /*
      Prompt user for 3 points separated by whitespace.

      Part 1:
          You'll need to get the x and y coordinate as floating point values
          from the user for 3 points that make up a triangle.

      Part 3:
          You'll need to also request 3 colors from the user each having
          3 floating point values (red, green and blue) that range from 0 to 1.
    */
    float one[2], two[2], three[2];
    float color_in[3];
    std::cout << "3 points in the format x y x y x y:";
    std::cin >> one[0] >> one[1] >> two[0] >> two[1] >> three[0] >> three[1];   
    
    std::cout << "3 color values between 0 and 1 format r g b:";
    std::cin >> color_in[0] >> color_in[1] >> color_in[2];
    // create an image 640 pixels wide by 480 pixels tall
    bitmap_image image(640, 480);

    /*
      Part 1:
          Calculate the bounding box of the 3 provided points and loop
          over each pixel in that box and set it to white using:

          rgb_t color = make_color(255, 255, 255);
          image.set_pixel(x,y,color);
    */
    float min_x, max_x, min_y, max_y;
    if(one[0]>two[0]){
	    max_x = one[0];
	    min_x = two[0];
    }
    else{
	    max_x = two[0];
	    min_x = one[0];
    }
    if(three[0]>max_x){
	    max_x = three[0];
    }
    else if(three[0]<min_x){
	    min_x = three[0];
    }

    if(one[1]>two[1]){
	    max_y = one[1];
	    min_y = two[1];
    }
    else{
	    max_y = two[1];
	    min_y = one[1];
    }
    if(three[0]>max_y){
	    max_y = three[1];
    }
    else if(three[1]<min_y){
	    min_y = three[1];
    }

    //rgb_t color = make_colour(255, 255, 255);
    for(int i=min_x; i<max_x; i++){
	    for(int j=min_y; j<max_y; j++){
		    float p[] = {(float)i,(float)j};
		    float alpha = f(one,two,p)/f(one,two,three);
		    float beta = f(one,three,p)/f(one,three,two);
	    	    float gamma = 1 - alpha - beta;
		    
		    if((alpha > 0 && alpha < 1) && (beta > 0 && beta < 1) && (gamma > 0 && gamma < 1))
				    {
					int r = alpha * color_in[0] * 255;
				    	int g = beta * color_in[1] * 255;
					int b = gamma * color_in[2] * 255;
					rgb_t color = make_colour(r, g, b);
					image.set_pixel(i,j,color);
				    }
	    }
    }

    /*
      Part 2:
          Modify your loop from part 1. Using barycentric coordinates,
          determine if the pixel lies within the triangle defined by
          the 3 provided points. If it is color it white, otherwise
          move on to the next pixel.

      Part 3:
          For each pixel in the triangle, calculate the color based on
          the calculated barycentric coordinates and the 3 provided
          colors. Your colors should have been entered as floating point
          numbers from 0 to 1. The red, green and blue components range
          from 0 to 255. Be sure to make the conversion.
    */

    image.save_image("triangle.bmp");
    std::cout << "Success" << std::endl;
}
