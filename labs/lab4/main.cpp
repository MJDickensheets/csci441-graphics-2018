#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <csci441/shader.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
int view_y = 0;

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

char processInput(GLFWwindow *window, Shader &shader) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
	return 'w';
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
	return 's';
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
	return '1';
    }   
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
	return '2';
    }   
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
	return '3';
    }   
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
	return '4';
    }   
    if (glfwGetKey(window, GLFW_KEY_COMMA) == GLFW_PRESS) {
	return ',';
    }
    if (glfwGetKey(window, GLFW_KEY_PERIOD) == GLFW_PRESS) {
	return '.';
    }
    if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
	return '-';
    }
    if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
	return '=';
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
	return 'u';
    }
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
	return 'i';
    }
    if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS) {
	return 'o';
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
	return 'p';
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_BRACKET) == GLFW_PRESS) {
	return '[';
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT_BRACKET) == GLFW_PRESS) {
	return ']';
    }
    if (glfwGetKey(window, GLFW_KEY_BACKSLASH) == GLFW_PRESS) {
	    return '\\';
    }

    return '~';
}

void errorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW Error: %s\n", description);
}

int main(void) {
    GLFWwindow* window;

    glfwSetErrorCallback(errorCallback);

    /* Initialize the library */
    if (!glfwInit()) { return -1; }

#ifdef __APPLE__
    glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Lab 4", NULL, NULL);
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

    /* init the model */
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f
    };

    // copy vertex data
    GLuint VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // describe vertex layout
    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float),
            (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float),
            (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    // create the shaders
    Shader shader("../vert.glsl", "../frag.glsl");

    // setup the textures
    shader.use();

    // and use z-buffering
    glEnable(GL_DEPTH_TEST);
    
    float nx = 640;
    float ny = 480;

    float l = -0.9;
    float r = 0.9;
    float b = -0.9;
    float t = 0.9;
    float n = 1;
    float f = -40;

    float thetax = 0;    
    float thetay = 0;
    float thetaz = 0;

    int projvalue = false;
    //set view
    float view[] = {
	    1, 0, 0, 0,
	    0, 1, 0, 0, 
	    0, 0, 1, 0,
	    0, 0, -1, 1};

    //set model
    float model[] = {
	    1, 0, 0, 0,
	    0, 1, 0, 0,
	    0, 0, 1, 0,
	    0, 0, 0, 1};

    //rotation matrix
    float rotatex[] = {
	    1, 0, 0, 0,
	    0, 1, 0, 0,
	    0, 0, 1, 0,
	    0, 0, 0, 1};   
    float rotatey[] = {
	    1, 0, 0, 0,
	    0, 1, 0, 0,
	    0, 0, 1, 0,
	    0, 0, 0, 1};
    float rotatez[] = {
	    1, 0, 0, 0,
	    0, 1, 0, 0,
	    0, 0, 1, 0,
	    0, 0, 0, 1};
    //ortho matrix
    float ortho[] = {
	    2/(r-l), 0, 0, 0,
	    0, 2/(t-b), 0, 0,
	    0, 0, -2/(-n+f), 0,
	    -(r+l)/(r-l), -(t+b)/(t-b), -(n+f)/(-n+f), 1};
    //proj matrix
    float project[] = {
	   2*std::abs(n)/(r-l), 0, 0, 0,
	   0, 2*std::abs(n)/(t-b), 0, 0, 
	   (r+l)/(r-l), (t+b)/(t-b), (std::abs(n)+std::abs(f))/(std::abs(n)-std::abs(f)), -1,
	   0, 0, 2*std::abs(f)*std::abs(n)/(std::abs(n)-std::abs(f)), 0};

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window)) {
        // process input
        char input = processInput(window, shader);
	if(input == 'w'){
		view[13] += 0.05;
	}
	else if (input == 's'){
		view[13] -= 0.05;
	}
	else if (input == '1'){
		view[13] += 0.02;
	}
	else if (input == '2'){
		view[13] -= 0.02;
	}
	else if (input == '3'){
		model[12] -= 0.02;
	}
	else if (input == '4'){
		model[12] += 0.02;
	}
	else if (input == ','){
		view[14] -= 0.02;
	}
	else if (input == '.'){
		view[14] += 0.02;
	}
	else if (input == '-'){
		view[15] = view[15] * (1.25);
	}
	else if (input == '='){
		view[15] = view[15] * (0.8);
	}
	else if (input == 'u'){
		thetax -= 0.02;
		rotatex[5] = (float)cos(thetax);
		rotatex[9] = (float)-sin(thetax);
		rotatex[6] = (float)sin(thetax);
		rotatex[10] = (float)cos(thetax);
	}
	else if (input == 'i'){
		thetax += 0.02;
		rotatex[5] = (float)cos(thetax);
		rotatex[9] = (float)-sin(thetax);
		rotatex[6] = (float)sin(thetax);
		rotatex[10] = (float)cos(thetax);
	}
	else if (input == 'o'){
		thetay -= 0.02;
		rotatey[0] = (float)cos(thetay);
		rotatey[2] = (float)-sin(thetay);
		rotatey[8] = (float)sin(thetay);
		rotatey[10] = (float)cos(thetay);

	}
	else if (input == 'p'){
		thetay += 0.02;
		rotatey[0] = (float)cos(thetay);
		rotatey[2] = (float)-sin(thetay);
		rotatey[8] = (float)sin(thetay);
		rotatey[10] = (float)cos(thetay);
	}
	else if (input == '['){
		thetaz -= 0.02;
		rotatez[0] = (float)cos(thetaz);
		rotatez[4] = (float)-sin(thetaz);
		rotatez[1] = (float)sin(thetaz);
		rotatez[5] = (float)cos(thetaz);
	}
	else if (input == ']'){
		thetaz += 0.02;
		rotatez[0] = (float)cos(thetaz);
		rotatez[4] = (float)-sin(thetaz);
		rotatez[1] = (float)sin(thetaz);
		rotatez[5] = (float)cos(thetaz);
	}
	else if (input == '\\'){
		if(projvalue){
			projvalue = false;	
		}
		else{
			projvalue = true;
		}
	}

        /* Render here */
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // activate shader
        shader.use();

	int ViewLocation = glGetUniformLocation(shader.id(), "View");
	int ModelLocation = glGetUniformLocation(shader.id(), "Model");
	int projLocation = glGetUniformLocation(shader.id(), "proj");
	int rotxLocation = glGetUniformLocation(shader.id(), "rotx");
	int rotyLocation = glGetUniformLocation(shader.id(), "roty");
	int rotzLocation = glGetUniformLocation(shader.id(), "rotz");
	
	glUniformMatrix4fv(ViewLocation, 1, false, view);
	glUniformMatrix4fv(ModelLocation, 1, false, model);
	if(projvalue == true){
		glUniformMatrix4fv(projLocation, 1, false, project);
	}
	else{
		glUniformMatrix4fv(projLocation, 1, false, ortho);
	}
	glUniformMatrix4fv(rotxLocation, 1, false, rotatex);
	glUniformMatrix4fv(rotyLocation, 1, false, rotatey);
	glUniformMatrix4fv(rotzLocation, 1, false, rotatez);


        // render the cube
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices));

        /* Swap front and back and poll for io events */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
