#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <thread>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_interpolation.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/compatibility.hpp>

#include <csci441/shader.h>
#include <csci441/matrix.h>
#include <csci441/matrix3.h>
#include <csci441/vector.h>
#include <csci441/uniform.h>

#include <glm/glm.hpp>


#include "bitmap_image.hpp"
#include "object.h"

struct Viewport {
    glm::vec2 min;
    glm::vec2 max;

    Viewport(const glm::vec2& min, const glm::vec2& max)
        : min(min), max(max) {}
};

struct Sphere {
    int id;
    glm::vec3 center;
    glm::vec3 color;
    float radius;

    Sphere(const glm::vec3& center=glm::vec3(0,0,0),
            float radius=0,
            const glm::vec3& color=glm::vec3(0,0,0))
        : center(center), radius(radius), color(color) {
            static int id_seed = 0;
            id = ++id_seed;
        }
};

struct Ray {
    glm::vec3 origin;// = glm::vec3(0,0,0);
    glm::vec3 direction;// = glm::vec3(0,0,0);

    Ray(const glm::vec3& origin=glm::vec3(0,0,0),
	const glm::vec3& direction = glm::vec3(0,0,0))
	: origin(origin) {
	    this->direction = glm::normalize(direction);
	}
};

bool raytri(glm::vec3 a_vec, glm::vec3 b_vec, glm::vec3 c_vec, glm::vec3 e_vec, glm::vec3 d_vec, float& gamma, float& beta, float& t){
    float a = a_vec.x-b_vec.x;
    float b = a_vec.y-b_vec.y;
    float c = a_vec.z-b_vec.z;
    float d = a_vec.x-c_vec.x;
    float e = a_vec.y-c_vec.y;
    float f = a_vec.z-c_vec.z;
    float g = d_vec.x;
    float h = d_vec.y;
    float i = d_vec.z;
    float j = a_vec.x-e_vec.x;
    float k = a_vec.y-e_vec.y;
    float l = a_vec.z-e_vec.z;
    float eihf = (e*i-h*f);
    float gfdi = (g*f-d*i);
    float dheg = (d*h-e*g);
    float akjb = (a*k-j*b);
    float jcal = (j*c-a*l);
    float blkc = (b*l-k*c);
    float m = a*eihf + b*gfdi + c*dheg;


    t = (f*akjb + e*jcal + d*blkc)/m;

    if(t < -100 || t > 100){
	//std::cout << "Breaking t ";
	return false;
    }
    gamma = (i*akjb + h*jcal + g*blkc)/m;

    if(gamma < 0 || gamma > 1){
	//std::cout << "Breaking gamma " << gamma << " ";
	return false;
    }
    beta = (j*eihf + k*gfdi + l*dheg)/m;

    if(beta < 0 || beta > (1-gamma)){
	//std::cout << "Breaking beta " << beta << " ";
	return false;
    }
    return true;
}
void shader(float beta, float gamma, float t, 
		glm::vec3 d, glm::vec3 e, glm::vec3 norm_p, glm::vec3 norm_q, glm::vec3 norm_r, 
		glm::vec3 in_color, rgb_t& color){

    glm::vec3 light = glm::vec3(-100, 100, 0);
    glm::vec3 pos = t*d - e;
    glm::vec3 l = glm::normalize(light - pos);

    float alpha = 1 - beta - gamma;
    glm::vec3 n = alpha * norm_p + beta * norm_q + gamma * norm_r;
    n = glm::normalize(n);
    //diffuse shading
    glm::vec3 diffColor = in_color * std::max(0.0f, glm::dot(n, l));
    //specular shading
    glm::vec3 v = glm::normalize(-t*d);
    glm::vec3 h = glm::normalize(v+l);

    float phong = 100;
    glm::vec3 specColor = glm::vec3(1, 1, 1) * std::max(0.0f, std::pow(glm::dot(n, h), phong));
    glm::vec3 ambColor = glm::vec3(in_color.x * 0.2, in_color.y * 0.2, in_color.z*0.2);
    glm::vec3 outcolor = glm::vec3(std::min(diffColor.x + specColor.x + ambColor.x, 1.0f),std::min(diffColor.y + specColor.y + ambColor.y, 1.0f),std::min(diffColor.z + specColor.z + ambColor.z, 1.0f));
    if(specColor.x < 0) std::cout << "X ";
    color = make_colour(outcolor.x*255, outcolor.y*255, outcolor.z*255);

}


void thread_wrap(bitmap_image& image, const std::vector<Object>& world, int i, int j){
	std::cout << "Thread " << j << std::endl;
	int l = -5;
        int r = 5;
        int b = 5;
        int t = -5;
        Ray rays[640*480];	
	float ui = l + (r-l)*(i+.5) / 640;
	    float vj = b + (t-b)*(j+.5) / 480;
	    int current = j*640 + i;
	    //orthographic
	    //rays[current] = Ray(glm::vec3(ui, vj, 0),glm::vec3(0,0,-1));
	    float ratio = (float)j/480;
	    //std::cout << ratio << " ";
	    rgb_t color = make_colour((int)(156*ratio), (int)(75*ratio), (int)(211*ratio));    
	    //perspective
	    float distance = 10;
	    glm::vec3 e = glm::vec3(0, 0, -distance);
	    glm::vec3 d = glm::vec3(ui, vj, 0) - e;
	    d = glm::normalize(d);
	    rays[current] = Ray(e, d);

	    for(int k = 0; k < world.size(); k++){
		std::vector<std::thread> threads;
		for(int g = 0; g < world[k].faces.size(); g++){

		    float gamma, beta, t;

		    if(raytri(world[k].faces[g].p, world[k].faces[g].q, world[k].faces[g].r, e, d, gamma, beta, t)){
		        rgb_t tempColor;
			shader(beta, gamma, t, d, e, world[k].faces[g].normp, world[k].faces[g].normq, world[k].faces[g].normr, world[k].faces[g].color, tempColor);
		        image.set_pixel(i, j, tempColor);
		        break;
		    }
		    else{
		        image.set_pixel( i, j, color);
		    }
		}
	    }
		
}

void render(bitmap_image& image, const std::vector<Object>& world) {
    // TODO: implement ray tracer
    int l = -5;
    int r = 5;
    int b = 5;
    int t = -5;
    
    Ray rays[640*480];
    for(int i =0; i < 640; i++){
	std::vector<std::thread> threads;
	for(int j = 0; j < 480; j++){
	    //std::cout << "About to create thread " << j << std::endl;
	    //threads.emplace_back(std::thread(&thread_wrap, std::ref(image), std::ref(world), i, j));
	    float ui = l + (r-l)*(i+.5) / 640;
	    float vj = b + (t-b)*(j+.5) / 480;
	    int current = j*640 + i;
	    //orthographic
	    //rays[current] = Ray(glm::vec3(ui, vj, 0),glm::vec3(0,0,-1));
	    float ratio = (float)j/480;
	    //std::cout << ratio << " ";
	    rgb_t color = make_colour((int)(156*ratio), (int)(75*ratio), (int)(211*ratio));    
	    //perspective
	    float distance = 10;
	    glm::vec3 e = glm::vec3(0, 0, -distance);
	    glm::vec3 d = glm::vec3(ui, vj, 0) - e;
	    d = glm::normalize(d);
	    rays[current] = Ray(e, d);

	    for(int k = 0; k < world.size(); k++){
		std::vector<std::thread> threads;
		for(int g = 0; g < world[k].faces.size(); g++){

		    float gamma, beta, t;

		    if(raytri(world[k].faces[g].p, world[k].faces[g].q, world[k].faces[g].r, e, d, gamma, beta, t)){
		        rgb_t tempColor;
			shader(beta, gamma, t, d, e, world[k].faces[g].normp, world[k].faces[g].normq, world[k].faces[g].normr, world[k].faces[g].color, tempColor);
		        image.set_pixel(i, j, tempColor);
		        break;
		    }
		    else{
		        image.set_pixel( i, j, color);
		    }
		    


		}
		
	    }
	    //for(int j = 0; j<480; j++){
//		threads[j].join();
//	    }
	}
    }
}



int main(int argc, char** argv) {

    // create an image 640 pixels wide by 480 pixels tall
    bitmap_image image(640, 480);

    // build world
    //std::vector<Sphere> world = {
    //    Sphere(glm::vec3(-1, 0, 1), 1, glm::vec3(1,0.5,0.5)),
    //    Sphere(glm::vec3(1, 4, 4), 2, glm::vec3(0.5,1,0.5)),
    //    Sphere(glm::vec3(-1, 2, 6), 3, glm::vec3(0.5,0.5,1)),
    //	Sphere(glm::vec3(-2, 0, 2), 0.5, glm::vec3(0.5, 0.5, 0.5))
    //};
    //
    std::vector<Object> world = {
	Object("../models/floor.obj"),
	Object("../models/duck.obj")
    };

    // render the world
    render(image, world);

    //image.save_image("orthographic.bmp");
    image.save_image("perspective.bmp");
    std::cout << "Success" << std::endl;
}


