#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <list>
#include <vector>
#include <chrono>
#include <thread>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <csci441/shader.h>
#include <csci441/matrix.h>
#include <csci441/uniform.h>
#include <csci441/vector.h>

#include "shape.h"

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

// handle mouse drag input
void handleMouse(Matrix& model, GLFWwindow *window, double& prev_x, double& prev_y) {
    Matrix trans;

    double cur_x, cur_y;
    glfwGetCursorPos(window, &cur_x, &cur_y);

    int width, height;
    glfwGetWindowSize(window, &width, &height);

    float x_rat = ((float)cur_x - (float)prev_x) / width;
    float y_rat = -((float)cur_y - (float)prev_y) / height;

    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    if (state == GLFW_PRESS) {
	trans.translate(x_rat, y_rat, 0);
    }

    prev_x = cur_x;
    prev_y = cur_y;

    model = trans * model;
}

// handle zoom in view mode
Matrix processModel(const Matrix& model, GLFWwindow *window) {
    Matrix trans;
    
    const float SCALE = 0.05;
    const float TRANS = 0.01;

    // SCALE
    if (isPressed(window, '-')) { trans.scale(1-SCALE, 1-SCALE, 1-SCALE); }
    else if (isPressed(window, '=')) { trans.scale(1+SCALE, 1+SCALE, 1+SCALE); }

    return trans * model;
}

//handle mode changes
void processInput(Matrix& model,  GLFWwindow *window, bool* modes) {
    if (isPressed(window, GLFW_KEY_ESCAPE) || isPressed(window, GLFW_KEY_Q)) {
        glfwSetWindowShouldClose(window, true);
    }
    else if (isPressed(window, GLFW_KEY_V)) { 
	if(modes[0] == true){
	    modes[0] = false;
	    std::cout << "Edit Mode" << std::endl;
	}
	else {
	    modes[0] = true;
	    std::cout << "View Mode" << std::endl;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
    else if (isPressed(window, GLFW_KEY_T)) { modes[1] = true; }
    else if (isPressed(window, GLFW_KEY_S)) { modes[2] = true; }
    else if (isPressed(window, GLFW_KEY_C)) { modes[3] = true; }
    else if (isPressed(window, GLFW_KEY_U)) { modes[4] = true; }
    else if (isPressed(window, GLFW_KEY_G)) { modes[5] = true; }
    else if (isPressed(window, GLFW_KEY_M)) { modes[6] = true; }

    if(modes[0]==true){
        model = processModel(model, window);
    }
}

// create shapes and vertex array attibutes
void createShape(GLFWwindow* window, std::list<Shape> *l, int choice) {
    std::cout << "Enter RGB values (between 0 and 1) in form r g b: " << std::endl;
    float rgb[3];
    std::cin >> rgb[0] >> rgb[1] >> rgb[2];
    std::cout << "Click where on the screen you would like to place the shape." << std::endl;
    double x_pos, y_pos;
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    while(true){
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if(state == GLFW_PRESS){
	    glfwGetCursorPos(window, &x_pos, &y_pos);
	    break;
	}
	glfwPollEvents();
    }
    float xtrans = (2 * x_pos / width) - 1;
    float ytrans = -((2 * y_pos / height) - 1);
    std::cout << "Enter scaling factors in form x y:" << std::endl;
    float xscal, yscal;
    std::cin >> xscal >> yscal;
    std::cout << "Enter degrees of rotation." << std::endl;
    float rotate;
    std::cin >> rotate;

    std::list<Shape>::iterator p;

    switch (choice) {
	case 1:{
	    Triangle t(rgb[0], rgb[1], rgb[2]);
	    t.scale(xscal, yscal, 1);
	    t.rotate(rotate);
	    t.translate(xtrans, ytrans, 0);
	    l->push_back(t);}
	    break;
	case 2:{
	    Square s(rgb[0], rgb[1], rgb[2]);
	    s.scale(xscal, yscal, 1);
	    s.rotate(rotate);
	    s.translate(xtrans, ytrans, 0);
	    l->push_back(s);}
	    break;
	case 3:{
	    Circle c(40, rgb[0], rgb[1], rgb[2]);
	    c.scale(xscal, yscal, 1);
	    c.rotate(rotate);
	    c.translate(xtrans, ytrans, 0);
	    l->push_back(c);}
	    break;
	case 4:{
	    std::vector<float> v;
	    std::cout << "Click points on screen to draw. Press enter to create shape." << std::endl;
	    while(!isPressed(window, GLFW_KEY_ENTER)){
		glfwPollEvents();
		int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		if(state == GLFW_PRESS){
		    double x, y;
		    glfwGetCursorPos(window, &x, &y);
		    v.push_back((2*x/width)-1);
		    v.push_back(-((2*y/height)-1));
		}
	    }
	    float xs[v.size()/2], ys[v.size()/2];

	    for(int i = 0; i<v.size(); i+=2){
		xs[i/2] = v[i];
		ys[i/2] = v[i+1];
	    }
	    UserShape u(v.size()/2, xs, ys, rgb[0], rgb[1], rgb[2]);
	    u.scale(xscal, yscal, 1);
	    u.rotate(rotate);
	    u.translate(xtrans, ytrans, 0);
	    l->push_back(u);
	    break;}

    }


    for ( p = l->begin(); p != l->end(); ++p){
	//copy vertex data
	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, p->coords.size()*sizeof(float),
		&p->coords[0], GL_STATIC_DRAW);
	p->setVBO(VBO);
	// describe vertex layout
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float),
                          (void*)0);
        glEnableVertexAttribArray(0);
	p->setVAO(VAO);
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
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "program1", NULL, NULL);
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
    
    // create shape list
    std::list<Shape> l;
    std::list<Shape>::iterator p;
    
    //mouse data
    double m_x, m_y;
    glfwGetCursorPos(window, &m_x, &m_y);

    // group structure
    std::vector<std::string> group;

    // initialize matricies
    Matrix projection;
    Matrix view;
    Matrix model;

    // create the shaders
    Shader shader("../vert.glsl", "../frag.glsl");
    
    // setup the textures
    shader.use();
    
    
    // and use z-buffering
    glEnable(GL_DEPTH_TEST);
    
    // modes: view, triangle, square, circle, user, group, modify
    bool modes [] = {true, false, false, false, false, false, false};

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // process input
        processInput(view, window, modes);
	
	//check mode
	if(modes[0]) {

	    // handle mouse
	    handleMouse(view, window, m_x, m_y);
	}
	else{
	    Matrix newMat;
	    view = newMat;
	}

	// check modes and create shapes
	if(modes[1]&&!modes[0]){
	    createShape(window, &l, 1);
	    modes[1] = false;
	}
	else if(modes[2]&&!modes[0]) {
	    createShape(window, &l, 2);
	    modes[2] = false;
	}
	else if(modes[3]&&!modes[0]) {
	    createShape(window, &l, 3);
	    modes[3] = false;
	}
	else if(modes[4]&&!modes[0]) {
	    createShape(window, &l, 4);
	    modes[4] = false;
	}
	//Group Mode
	else if(modes[5] &&! modes[0]) {
	    
	    // get list of names
	    if(group.empty()){
	        std::cout << "Type in names from the list below to add them to the group. Type 'end' to finalize the group." << std::endl;

	        for(p = l.begin(); p != l.end(); ++p){
		    std::cout << p->getName() << std::endl;
	        }

	        bool end = false;
	        while(!end){
		    std::string name;
		    std::cin >> name;
		    for(p = l.begin(); p != l.end(); ++p){
		        if(name == p->getName()){
		 	     group.push_back(name);
			     std::cout << "Added " << name << std::endl;
		        }
		        else if (name == "end") end = true;
	            }
	        }
	        std::cout << "Shapes Grouped" << std::endl;
	    }
	    else{
		std::cout << "Ungroup? (y/n)" << std::endl;
		char ungroup;
		std::cin >> ungroup;
		if(ungroup == 'y'){
		    std::vector<std::string> new_group;
		    group = new_group;
		}
	    }
	    modes[5] = false;
	}
	// Modify mode
	else if(modes[6] && !modes[0]){
	    // check if modify group
	    std::string name;
	    std::vector<std::string> primitives;
	    char group_in;
	    if(!group.empty()){
		std::cout << "Modify group? (y/n)" << std::endl;
	        std::cin >> group_in;
	    }
	    if(group_in == 'y') {
		for(int i=0; i < group.size(); ++i){
		    primitives.push_back(group[i]);
		}
	    }
	    else{
	    	std::cout << "Type in the name of the shape you would like to modify." << std::endl;
	    	for(p = l.begin(); p != l.end(); ++p){
		std::cout << p->getName() << std::endl;
	    	}
		std::cin >> name;
		primitives.push_back(name);
	    }
	    //get origin
	    std::cout << "Click where on the screen you would like to origin to be." << std::endl;
    	    double x_pos, y_pos;
    	    int w, h;
    	    glfwGetWindowSize(window, &w, &h);
    	    while(true){
		int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		if(state == GLFW_PRESS){
	    	    glfwGetCursorPos(window, &x_pos, &y_pos);
	    	    break;
	    	}
		glfwPollEvents();
    	    }
	    float x_orig = (2 * x_pos / w) - 1;
	    float y_orig = (2 * y_pos / h) - 1;
	    //choose modification
	    std::cout << "Modifying " << name << ". Type r to rotate, s to scale, t to translate, c to change color or e to exit modify mode." << std::endl;
	    char choose;
	    std::cin >> choose;
	    if(choose == 'r'){
		std::cout << "Enter degree of rotation:" << std::endl;
		float rotate;
		std::cin >> rotate;
		for(int i = 0; i < primitives.size(); ++i){
	            for(p = l.begin(); p != l.end(); ++p){
		        if(primitives[i] == p->getName()){
			    p->translate(-x_orig, y_orig, 0);
			    p->rotate(rotate);
			    p->translate(x_orig, -y_orig, 0);
		        }
		    }
	        }
	    }
	    else if(choose == 's'){
		std::cout << "Enter scaling factors in form x y." << std::endl;
		float x, y;
		std::cin >> x >> y;
		for(int i = 0; i < primitives.size(); ++i){
		    for(p = l.begin(); p != l.end(); ++p){
		        if(primitives[i] == p->getName()){
			    p->translate(-x_orig, y_orig, 0);
			    p->scale(x, y, 1);
			    p->translate(x_orig, -y_orig, 0);
		        }
		    }
	        }
	    }
	    else if(choose == 't') {
		std::cout << "Enter translation percentages (-1 to 1) in form x y." << std::endl;
		float x, y;
		std::cin >> x >> y;
		for(int i = 0; i < primitives.size(); ++i){
		    for(p = l.begin(); p != l.end(); ++p){
		        if(primitives[i] == p->getName()) p->translate(x, y, 0);;
	            }
		}
	    }
	    else if(choose == 'c') {
		std::cout << "Enter new colors in (0 to 1) r g b format:" << std::endl;
		float r, g, b;
		std::cin >> r >> g >> b;
		for(int i = 0; i < primitives.size(); ++i){
		    for(p = l.begin(); p != l.end(); ++p){
		        if(primitives[i] == p->getName()){
			    p->r = r;
			    p->g = g;
			    p->b = b;
			}
		    }
	        }
	    }
	    modes[6] = false;
	}

	//handle resize
        Matrix resize;
	int width, height;
	glfwGetWindowSize(window, &width, &height);
   	float ratio = (float)width / (float) height;
	float x_ratio = 1;
	float y_ratio = 1;
	if(ratio > 1) x_ratio *= ratio;
	else y_ratio *= 1/ratio;
   	resize.ortho(-x_ratio, x_ratio, -y_ratio, y_ratio, -1.0, 1.0);
    	Uniform::set(shader.id(), "projection", resize);
	Uniform::set(shader.id(), "view", view);

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
        // activate shader
        shader.use();
	
        // render the shapes
	
	for(p = l.begin(); p != l.end(); ++p){
	    //if((p->getVBO())%2==0) p->rotate(0.5);
	    //else p->rotate(-0.5);
	    model = p->getTrans();
	    Uniform::set(shader.id(), "model", model);
	    int col_loc = glGetUniformLocation(shader.id(), "color");
	    glUniform3fv(col_loc, 1, p->getColor());
	    glBindBuffer(GL_ARRAY_BUFFER, p->getVBO());
            glBindVertexArray(p->getVAO());
            glDrawArrays(GL_TRIANGLES, 0, p->coords.size()*sizeof(float));
	} 
        
        /* Swap front and back and poll for io events */
        glfwSwapBuffers(window);
        glfwPollEvents();

	modes[1] = false;
	modes[2] = false;
	modes[3] = false;
	modes[4] = false;
    }
    
    glfwTerminate();
    return 0;
}
