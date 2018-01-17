#include <iostream>
#include <string>

class Vector3 {
public:
	float x;
	float y;
	float z;

	// Constructor
	Vector3(){
		std::cout<<"in default constructor"<<std::endl;
	}
	Vector3(float xx, float yy, float zz) : x(xx), y(yy), z(zz) {
		// nothing to do here as we've already initialized x, y, and z above
		std::cout << "in Vector3 constructor" << std::endl;
	}

	// Destructor - called when an object goes out of scope or is destroyed
	~Vector3() {
		// this is where you would release resources such as memory or file descriptors
		// in this case we don't need to do anything
		std::cout << "in Vector3 destructor" << std::endl;
	}
};

Vector3 add(Vector3& v, Vector3& v2) { // v and v2 are copies, so any changes to them in this function
	                             // won't affect the originals
	return Vector3(v.x+v2.x,v.y+v2.y,v.z+v2.z);
}

Vector3 operator+(const Vector3& v, const Vector3& v2){
	return Vector3(v.x+v2.x,v.y+v2.y,v.z+v2.z);
}

std::ostream& operator<<(std::ostream& stream, const Vector3& v){
	stream << v.x << " " << v.y << " " << v.z << std::endl;
	return stream;
}

int main(int argc, char** argv){	
	for(int i=1; i<argc; i++){
		std::cout << argv[i] << " ";
	}
	std::cout << std::endl;
	
	std::cout << "What is your name? ";
	std::string name;
	std::cin >> name;
	std::cout << "hello " << name << std::endl;

	Vector3 a(1,2,3);   // allocated to the stack
	Vector3 b(4,5,6);

	Vector3 test = add(a,b);

	std::cout << test.x << " " << test.y << " " << test.z << std::endl;
	std::cout << a+b << std::endl;

	Vector3* vec = new Vector3(0,0,0);
	vec->y=5;
	delete vec;
	std::cout<<*vec<<std::endl;

	Vector3 array[10];

	Vector3* vec_array = new Vector3[10];
	for(int i=0; i<10; i++){
		std::cout << vec_array[i] << " ";
	}
	std::cout << std::endl;
	delete [] vec_array;
}
