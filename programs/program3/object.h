#include <vector>
#include <cstdlib>
class Object {
    
    struct triangle{
	glm::vec3 p;
	glm::vec3 q;
	glm::vec3 r;
	glm::vec3 normp;
	glm::vec3 normq;
	glm::vec3 normr;
	glm::vec3 color;

	triangle(const glm::vec3& p, const glm::vec3 q, 
		const glm::vec3 r, const glm::vec3& normp,
		const glm::vec3 normq, const glm::vec3 normr,
		const glm::vec3 color) : 
		p(p), q(q), r(r), normp(normp), normq(normq), normr(normr), color(color){}
    };
	
    std::vector<float> coords;
    std::vector<Vector> verticies;
    std::vector<Vector> normals;
    std::vector<GLushort> elements;

public:
    std::vector<triangle> faces;
    Object(const char* filename){
	std::ifstream in(filename, std::ios::in);
        if (!in)
        {
            std::cerr << "Cannot open " << filename << std::endl; exit(1);
        }
        
        std::string line;
        while (getline(in, line))
        {
            if (line.substr(0,2) == "v ")
            {
                std::istringstream s(line.substr(2));
		float x, y, z;
                s >> x; s >> y; s >> z;
                verticies.push_back(Vector(x, y, z));
		
            }
            else if(line.substr(0,2) == "f ")
            {
                std::istringstream s(line.substr(2));
                GLushort a,b,c;
                s >> a; s >> b; s >> c;
                a--; b--; c--;
                elements.push_back(a); elements.push_back(b); elements.push_back(c);
            }
        }
       

	// do smooth shading
	std::vector<Vector> vert_norms;
    	for(int j = 0; j < verticies.size(); j++){
	    std::vector<Vector> temp_norms;
	    for(int i = 0; i < elements.size(); i+=3){
                   GLushort ia = elements[i];
	   	   GLushort ib = elements[i+1];
	   	   GLushort ic = elements[i+2];
		   if(ia == j || ib == j || ic == j){
		   Vector normal = (verticies[ib] - verticies[ia]).cross(verticies[ic] - verticies[ia]);
			 temp_norms.push_back(normal);
		    }
	    }
	    Vector v_norm(0,0,0);
	    while(!temp_norms.empty()){
		   v_norm = Vector(v_norm.x() + temp_norms.back().x(), v_norm.y() + temp_norms.back().y(), v_norm.z() + temp_norms.back().z());
		   temp_norms.pop_back();
	    }
	    v_norm = v_norm.normalized();
	    vert_norms.push_back(v_norm);
	}

	for(int i = 0; i < elements.size(); i+=3){
	   GLushort ia = elements[i];
	   GLushort ib = elements[i+1];
	   GLushort ic = elements[i+2];
	   //add_vertex(coords, verticies[ia].x()/1100, verticies[ia].y()/1100, verticies[ia].z()/1100, r, g, b, vert_norms[ia]);
	   //add_vertex(coords, verticies[ib].x()/1100, verticies[ib].y()/1100, verticies[ib].z()/1100, r, g, b, vert_norms[ib]);
	   //add_vertex(coords, verticies[ic].x()/1100, verticies[ic].y()/1100, verticies[ic].z()/1100, r, g, b, vert_norms[ic]);
	   glm::vec3 p = glm::vec3(verticies[ia].x()/300, verticies[ia].y()/300, verticies[ia].z()/300);
	   glm::vec3 q = glm::vec3(verticies[ib].x()/300, verticies[ib].y()/300, verticies[ib].z()/300);
	   glm::vec3 r = glm::vec3(verticies[ic].x()/300, verticies[ic].y()/300, verticies[ic].z()/300);
	   glm::vec3 normp = glm::vec3(vert_norms[ia].x(), vert_norms[ia].y(), vert_norms[ia].z());
	   glm::vec3 normq = glm::vec3(vert_norms[ib].x(), vert_norms[ib].y(), vert_norms[ib].z());
	   glm::vec3 normr = glm::vec3(vert_norms[ic].x(), vert_norms[ic].y(), vert_norms[ic].z());
	   glm::vec3 color = glm::vec3(1, 1, 0);
	   faces.push_back(triangle(p, q, r, normp, normq, normr, color));
	}
    }
};
