#include <cstdlib>
#include <vector>
#include <csci441/matrix.h>

template <typename T, typename N>
void add_vertex(T& coords, const N& x, const N& y) {
    coords.push_back(x);
    coords.push_back(y);
    coords.push_back(0);
}

class Shape {
protected:
    Matrix trans;
    unsigned int VBO;
    unsigned int VAO;
    std::string name;
public:
    std::vector<float> coords;
    float r, g, b;
    float color[3];

    float* getColor() {
	color[0] = r;
	color[1] = g;
	color[2] = b;
	return color;
    }

    void rotate(float theta) {
	Matrix rot;
	rot.rotate_z(theta);
	trans = rot * trans;
    }

    void scale(float x, float y, float z){
	Matrix scal;
	scal.scale(x, y, z);
	trans = scal * trans;
    }

    void translate(float x, float y, float z){
	Matrix t;
	t.translate(x, y, z);
	trans = t * trans;
    }

    Matrix getTrans() {
	return trans;
    }

    void setVBO(unsigned int VBOin) {
	VBO = VBOin;
	name += std::to_string(VBO);
    }

    void setVAO(unsigned int VAOin) {
	VAO = VAOin;
    }

    unsigned int getVBO() {
	return VBO;
    }

    unsigned int getVAO() {
	return VAO;
    }

    std::string getName() {
	return name;
    }
};

class Triangle: public Shape {
private:
    Matrix trans;
public:
    //std::vector<float> coords;
    Triangle(float r, float g, float b){
        add_vertex(coords, -0.5f, -0.5f);
	add_vertex(coords, 0.5f, -0.5f);
	add_vertex(coords, 0.0f, 0.5f);
	this->r = r;
	this->g = g;
	this->b = b;
	name = "Triangle";
    }
};

class Square: public Shape {
private:
    Matrix trans;

public:
    //std::vector<float> coords;
    Square(float r, float g, float b) {
        add_vertex(coords, -0.5f, -0.5f);
	add_vertex(coords, 0.5f, -0.5f);
	add_vertex(coords, -0.5f, 0.5f);

	add_vertex(coords, -0.5f, 0.5f);
	add_vertex(coords, 0.5f, 0.5f);
	add_vertex(coords, 0.5f, -0.5f);
	this->r = r;
	this->g = g;
	this->b = b;
	name = "Square";
    }


};

class Circle: public Shape {
private:
    Matrix trans;

public:
    //std::vector<float> coords;
    Circle(unsigned int n, float r, float g, float b){
	double step_size = 2*M_PI / n;
	float radius = .5;

	for (int i = 0; i < n; ++i) {
	    //vertex i
	    double theta_i = i*step_size;
	    double vi_x = radius*cos(theta_i);
	    double vi_y = radius*sin(theta_i);
	    //vertex i+1
	    double theta_ip1 = ((i+1)%n)*step_size;
	    double vip1_x = radius*cos(theta_ip1);
	    double vip1_y = radius*sin(theta_ip1);

	    add_vertex(coords, 0.0f, 0.0f);
	    add_vertex(coords, vi_x, vi_y);
	    add_vertex(coords, vip1_x, vip1_y);
	    this->r = r;
	    this->g = g;
	    this->b = b;
	}
	name = "Circle";
    }


};

class UserShape: public Shape {
private:
    Matrix trans;

public:
    //std::vector<float> coords;
    UserShape(unsigned int n, float* x_in, float* y_in, float r, float g, float b){
	for(int i = 0; i < n; ++i){
	    add_vertex(coords, 0.0f, 0.0f);
	    add_vertex(coords, x_in[i], y_in[i]);
	    add_vertex(coords, x_in[(i+1)%n], y_in[(i+1)%n]);
	}
	this->r = r;
	this->g = g;
	this->b = b;
	name = "User";
    }
};
