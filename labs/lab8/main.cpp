#include <iostream>

#include <glm/glm.hpp>

#include "bitmap_image.hpp"

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


void render(bitmap_image& image, const std::vector<Sphere>& world) {
    // TODO: implement ray tracer
    int l = -5;
    int r = 5;
    int b = 5;
    int t = -5;
    rgb_t color = make_colour(156, 75, 211);
    Ray rays[640*480];
    for(int i =0; i < 640; i++){
	for(int j = 0; j < 480; j++){
	    float ui = l + (r-l)*(i+.5) / 640;
	    float vj = b + (t-b)*(j+.5) / 480;
	    int current = j*640 + i;
	    //orthographic
	    //rays[current] = Ray(glm::vec3(ui, vj, 0),glm::vec3(0,0,-1));
	    
	    //perspective
	    float distance = 3;
	    glm::vec3 e = glm::vec3(0, 0, -distance);
	    glm::vec3 d = glm::vec3(ui, vj, 0) - e;
	    rays[current] = Ray(e, d);

	    for(int k = 0; k < world.size(); k++){
		float a = glm::dot(rays[current].direction, rays[current].direction);
		float b = 2*glm::dot(rays[current].direction, (rays[current].origin - world[k].center));
		float c = glm::dot((rays[current].origin - world[k].center), (rays[current].origin - world[k].center)) - world[k].radius * world[k].radius;
		float discrim = b * b - 4 * a * c;
		
		
		if(discrim > 0){
		    rgb_t tempColor = make_colour(world[k].color.x*255, world[k].color.y*255, world[k].color.z*255);
		    image.set_pixel(i, j, tempColor);
		    break;
		}
		else{
		    image.set_pixel( i, j, color);
		}
		
	    }
	}
    }
}

int main(int argc, char** argv) {

    // create an image 640 pixels wide by 480 pixels tall
    bitmap_image image(640, 480);

    // build world
    std::vector<Sphere> world = {
        Sphere(glm::vec3(-1, 0, 1), 1, glm::vec3(1,0.5,0.5)),
        Sphere(glm::vec3(1, 4, 4), 2, glm::vec3(0.5,1,0.5)),
        Sphere(glm::vec3(-1, 2, 6), 3, glm::vec3(0.5,0.5,1)),
	Sphere(glm::vec3(-2, 0, 2), 0.5, glm::vec3(0.5, 0.5, 0.5))
    };

    // render the world
    render(image, world);

    //image.save_image("orthographic.bmp");
    image.save_image("perspective.bmp");
    std::cout << "Success" << std::endl;
}


