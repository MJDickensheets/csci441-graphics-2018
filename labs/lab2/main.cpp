#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/**
 * BELOW IS A BUNCH OF HELPER CODE
 * You do not need to understand what is going on with it, but if you want to
 * know, let me know and I can walk you through it.
 */

void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

GLFWwindow* initWindow() {
    GLFWwindow* window;
    if (!glfwInit()) {
        return NULL;
    }

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    window = glfwCreateWindow(640, 480, "Lab 2", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return NULL;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
    if (!gladLoadGL()) {
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return NULL;
    }

    return window;
}

std::string shaderTypeName(GLenum shaderType) {
    switch(shaderType) {
        case GL_VERTEX_SHADER: return "VERTEX";
        case GL_FRAGMENT_SHADER: return "FRAGMENT";
        default: return "UNKNOWN";
    }
}

std::string readFile(const std::string& fileName) {
    std::ifstream stream(fileName);
    std::stringstream buffer;
    buffer << stream.rdbuf();

    std::string source = buffer.str();
    std::cout << "Source:" << std::endl;
    std::cout << source << std::endl;

    return source;
}

/** END OF CODE THAT YOU DON'T NEED TO WORRY ABOUT */

GLuint createShader(const std::string& fileName, GLenum shaderType) {
    std::string source = readFile(fileName);
    const GLchar* src_ptr = source.c_str();
    
    /** YOU WILL ADD CODE STARTING HERE */
    GLuint shader = glCreateShader(shaderType);;
    // create the shader using
    // glCreateShader, glShaderSource, and glCompileShader
    glShaderSource(shader, 1, &src_ptr, NULL);
    glCompileShader(shader);
    /** END CODE HERE */

    // Perform some simple error handling on the shader
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::" << shaderTypeName(shaderType)
            <<"::COMPILATION_FAILED\n"
            << infoLog << std::endl;
    }

    return shader;
}

GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader) {
    /** YOU WILL ADD CODE STARTING HERE */
    // create the program using glCreateProgram, glAttachShader, glLinkProgram
    GLuint program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);


    /** END CODE HERE */

    // Perform some simple error handling
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        std::cerr << "ERROR::PROGRAM::COMPILATION_FAILED\n"
            << infoLog << std::endl;
    }

    return program;
}

void w2nd(float* input) {
    input[0] = (input[0]*2/640)-1;
    input[1] = 1 - (input[1]*2/480);
}

int main(void) {
    GLFWwindow* window = initWindow();
    if (!window) {
        std::cout << "There was an error setting up the window" << std::endl;
        return 1;
    }

    /** YOU WILL ADD DATA INITIALIZATION CODE STARTING HERE */

    /* PART1: ask the user for coordinates and colors, and convert to normalized
     * device coordinates */

    // convert the triangle to an array of floats containing
    // normalized device coordinates and color components.
    // float triangle[] = ...
    float coords[6];
    float colors[9];
    std::cout << "3 points in the format x y x y x y:";
    std::cin >> coords[0] >> coords[1] >> coords[2] >> coords[3] >> coords[4] >> coords[5];
    std::cout << "3 color values in the format r g b r g b r g b:";
    std::cin >> colors[0] >> colors[1] >> colors[2] >> colors[3] >> colors[4] >> colors[5] >> colors[6] >> colors[7] >> colors[8];
    
    w2nd(&coords[0]);
    w2nd(&coords[2]);
    w2nd(&coords[4]);

    for(int i = 0; i < 9; i++){
	colors[i] = colors[i]/255;
    }

    float triangle[] = {coords[0], coords[1], colors[0], colors[1], colors[2],
	    		coords[2], coords[3], colors[3], colors[4], colors[5],
			coords[4], coords[5], colors[6], colors[7], colors[8]};
    /** PART2: map the data*/

    // create vertex and array buffer objects using
    // glGenBuffers, glGenVertexArrays
    GLuint VBO, VAO;

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);
    
    // setup triangle using glBindVertexArray, glBindBuffer, GlBufferData
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindVertexArray(VAO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);
    // setup the attribute pointer for the coordinates
    // setup the attribute pointer for the colors
    // both will use glVertexAttribPointer and glEnableVertexAttribArray;
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
    /** PART3: create the shader program */

    // create the shaders
    // YOU WILL HAVE TO ADD CODE TO THE createShader FUNCTION ABOVE
    GLuint vertexShader = createShader("./vert.glsl", GL_VERTEX_SHADER);
    GLuint fragmentShader = createShader("./frag.glsl", GL_FRAGMENT_SHADER);

    // create the shader program
    // YOU WILL HAVE TO ADD CODE TO THE createShaderProgram FUNCTION ABOVE
    GLuint shaderProgram = createShaderProgram(vertexShader, fragmentShader);

    // cleanup the vertex and fragment shaders using glDeleteShader
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    /** END INITIALIZATION CODE */

    while (!glfwWindowShouldClose(window)) {
        // you don't need to worry about processInput, all it does is listen
        // for the escape character and terminate when escape is pressed.
        processInput(window);

        /** YOU WILL ADD RENDERING CODE STARTING HERE */
        /** PART4: Implemting the rendering loop */

        // clear the screen with your favorite color using glClearColor
        glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0,0,0,0);
        // set the shader program using glUseProgram
	glUseProgram(shaderProgram);
        // bind the vertex array using glBindVertexArray
	glBindVertexArray(VAO);
        // draw the triangles using glDrawArrays
	glDrawArrays(GL_TRIANGLES, 0, 3);

        /** END RENDERING CODE */

        // Swap front and back buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
