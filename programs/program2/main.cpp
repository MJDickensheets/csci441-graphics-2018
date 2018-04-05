#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <csci441/shader.h>
#include <csci441/matrix.h>
#include <csci441/vector.h>
#include <csci441/uniform.h>

#include "shape.h"
#include "camera.h"
#include "model.h"
#include "renderer.h"
#include "mazeMaker.h"

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

bool isPressed(GLFWwindow *window, int key) {
    return glfwGetKey(window, key) == GLFW_PRESS;
}

bool isReleased(GLFWwindow *window, int key) {
    return glfwGetKey(window, key) == GLFW_RELEASE;
}

Matrix processCamera(const Matrix& model, Camera& camera, GLFWwindow *window) {
    Matrix trans;

    const float TURN = .05;
    const float TRANS = .01;

   
   
    double xpos, ypos;
    int width, height;
    glfwGetCursorPos(window, &xpos, &ypos);
    glfwGetWindowSize(window, &width, &height);

    double xratio = (xpos - width/2)/(width/2);
    double yratio = (ypos - height/2)/(height/2);

    double theta, phi;
    double look_x, look_y, look_z;
    look_x = camera.origin.x();
    look_y = camera.origin.y();
    look_z = camera.origin.z();

    //get current yaw
    theta = std::asin(look_z);
    if(look_x < 0) theta = (M_PI) - theta; 
    theta += TURN * xratio;

    // get current pitch
    phi = std::acos(look_y);
    phi	 += TURN * yratio;

    
    
    camera.origin.values[0] = std::cos(theta);
    camera.origin.values[1] = std::cos(phi);
    camera.origin.values[2] = std::sin(theta);

    // TRANSLATE
    Vector direction = camera.origin - camera.eye;
    direction = direction.normalized();

/*    if (isPressed(window, GLFW_KEY_UP)) {
	   camera.eye.values[0] += TRANS * direction.values[0];
	   camera.origin.values[0] += TRANS * direction.values[0];
    }
    else if (isPressed(window, GLFW_KEY_DOWN)) { 
    }
    else if (isPressed(window, GLFW_KEY_LEFT)) { 
    }
    else if (isPressed(window, GLFW_KEY_RIGHT)) { 
    }
*/

    // TRANSLATE
    if (isPressed(window, GLFW_KEY_LEFT)) { trans.translate(-TRANS * direction.z(), 0, TRANS * direction.x()); }
    else if (isPressed(window, GLFW_KEY_RIGHT)) { trans.translate(TRANS * direction.z(), 0, -TRANS * direction.x()); }
    if (isPressed(window, GLFW_KEY_DOWN)) { trans.translate(TRANS * direction.x(),0,TRANS * direction.z()); }
    else if (isPressed(window, GLFW_KEY_UP)) { trans.translate(-TRANS * direction.x(),0,-TRANS * direction.z()); }
    

    return trans * model;

}

Matrix processOverhead(const Matrix& model, GLFWwindow *window){
    Matrix trans;

    const float TRANS = .01;
    int height, width;
    double xpos, ypos;

    glfwGetCursorPos(window, &xpos, &ypos);
    glfwGetWindowSize(window, &width, &height);

    // TRANSLATE
    if (xpos < 0) { trans.translate(-TRANS, 0, 0); }
    else if (xpos > height) { trans.translate(TRANS, 0, 0); }
    else if (ypos < 0) { trans.translate(0,0,-TRANS); }
    else if (ypos > height) { trans.translate(0,0,TRANS); }
    

    return trans * model;

}

Matrix processModel(const Matrix& model, GLFWwindow *window) {
    Matrix trans;

    const float TRANS = .01;

    // TRANSLATE
    if (isPressed(window, GLFW_KEY_LEFT)) { trans.translate(TRANS, 0, 0); }
    else if (isPressed(window, GLFW_KEY_RIGHT)) { trans.translate(-TRANS, 0, 0); }
    else if (isPressed(window, GLFW_KEY_DOWN)) { trans.translate(0,0,-TRANS); }
    else if (isPressed(window, GLFW_KEY_UP)) { trans.translate(0,0,TRANS); }
    

    return trans * model;
}

bool isSpaceEvent(GLFWwindow *window) {
    static bool pressed = false;

    bool trigger = false;
    if (isPressed(window, GLFW_KEY_SPACE)) {
        pressed = true;
    } else if (pressed && isReleased(window, GLFW_KEY_SPACE)) {
        pressed = false;
        trigger = true;
    }
    return trigger;
}

void processInput(bool& birds_eye, Matrix& model, Camera& camera, GLFWwindow *window) {
    if (isPressed(window, GLFW_KEY_ESCAPE) || isPressed(window, GLFW_KEY_Q)) {
        glfwSetWindowShouldClose(window, true);
    } else if (isSpaceEvent(window)) {
	if(birds_eye == true){
	    birds_eye = false;
	    camera.eye = Vector(0, -1, 0);
    	    camera.origin = Vector(0, 0, 1);
    	    camera.up = Vector(0, 1, 0);
       	    Matrix maze_trans, maze_scale;
       	    maze_trans.translate(-0.42, 0, -.53);
	    maze_scale.scale(6, 20, 6);

	    model = maze_scale * maze_trans;
	}
	else{ 
		birds_eye = true;
		camera.eye = Vector(0, 2, 0);
		camera.origin = Vector(0, 0, 0);
		camera.up = Vector(0, 0, 1);
		Matrix maze_trans, maze_scale;
    		maze_trans.translate(-0.42, 0, -.53);
	        maze_scale.scale(6, 20, 6);

		model = maze_scale * maze_trans;
	}
    }
    if(birds_eye){
        
    }
    else{ 
	model = processCamera(model, camera, window);
        //camera.eye = Vector(0, -1, 0);
        //camera.origin = Vector(0, 0, 1);
        //model = processModel(model, window);
    }
}


void errorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}
int main(void) {
    GLFWwindow* window;

    glfwSetErrorCallback(errorCallback);

    /* Initialize the library */
    if (!glfwInit()) { return -1; }

    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CSCI441-lab", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    // tell glfw what to do on resize
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    // init glad
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return -1;
    }

    // create obj
    /*Model obj(
            Torus(40, .75, .5, 1, .2, .4).coords,
            Shader("../vert.glsl", "../frag.glsl"));
    */
    // create objects from file
    //MazeMaker maker("maze1");
    //maker.createMaze();


    /*Object smooth(1, .2, .4, true);
    smooth.load_obj("../models/dino.obj");
    Model obj1(
	    smooth.coords,
	    Shader("../vert.glsl", "../frag.glsl"));
    */
    Object maze(.2, .2, .2, true);
    maze.load_obj("../mazes/maze1.obj");
    Model obj1(
	    maze.coords, Shader("../vert.glsl", "../frag.glsl"));

    Matrix maze_trans, maze_scale;
    maze_trans.translate(-0.42, 0, -.53);
    maze_scale.scale(6, 20, 6);
    obj1.model = maze_scale*maze_trans;

    // make a floor
    Model floor(
            DiscoCube().coords,
            Shader("../vert.glsl", "../frag.glsl"));
    Matrix floor_trans, floor_scale;
    floor_trans.translate(0, -2, 0);
    floor_scale.scale(100, 1, 100);
    floor.model = floor_trans*floor_scale;

    // make a duck
    Object duck(0.4, 1.0, 0.9, true);
    duck.load_obj("../models/dino.obj");
    Model character( duck.coords, Shader("../vert.glsl", "../frag.glsl"));
    Matrix duck_scale, duck_trans;
    duck_scale.scale(0.6, 0.6, 0.6);
    duck_trans.translate(0, -0.5, 0);
    character.model = duck_trans*duck_scale;

    // setup camera
    Matrix projection;
    projection.perspective(45, 1, .01, 100);
    Matrix orthographic;
    orthographic.ortho(-2, 2, -2, 2, -2, 4);

    Camera camera;
    camera.projection = projection;
    camera.eye = Vector(0, -1, 0);
    camera.origin = Vector(0, 0, 1);
    camera.up = Vector(0, 1, 0);

    // and use z-buffering
    glEnable(GL_DEPTH_TEST);

    // set lineWidth
    glLineWidth(1.1);

    // create a renderer
    Renderer renderer;

    // set the light position
    Vector lightPos(3.75f, 3.75f, 4.0f);

    // birds_eye mode
    bool birds_eye = false;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
	// process input
	processInput(birds_eye, obj1.model, camera, window);

	if(birds_eye){
	    character.model = processModel(character.model, window);
	    character.model = processOverhead(character.model, window);
	    obj1.model = processOverhead(obj1.model, window);
	}
        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//if(birds_eye)camera.projection = orthographic;
	//else camera.projection = projection;
        // render the object and the floor
        renderer.render(camera, obj1, lightPos);
        renderer.render(camera, floor, lightPos);
	if(birds_eye)renderer.render(camera, character, lightPos);

        /* Swap front and back and poll for io events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
