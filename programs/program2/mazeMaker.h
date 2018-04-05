#include <vector>
#include <iostream>
#include <fstream>

class MazeMaker {

    struct point2d{
	double x;
	double y;
    };

    struct point3d{
	int x;
	int y;
	int z;
    };

    struct wall{
	point2d p1;
	point2d p2;
    };

    struct face{
	int p1;
	int p2;
	int p3;
    };

public:
    std::vector<wall> wallSet;
    std::string mazeName;

    MazeMaker(std::string mazeName){
        this->mazeName = mazeName;
    };

    void addWall(){
	    std::cout << "Type x and y coordinates for point 1:" << std::endl;
	    point2d point1;
	    std::cin >> point1.x >> point1.y;
	    std::cout << "Type x and y cooridates for point 2:" << std::endl;
	    point2d point2;
	    std::cin >> point2.x >> point2.y;
	    wall newWall;
	    newWall.p1 = point1;
	    newWall.p2 = point2;
	    wallSet.push_back(newWall);
    }



    void createObjFile(){
	std::string fileName = "../mazes/" +  mazeName + ".obj";
	std::ofstream file(fileName);
	file << "#" << fileName << "#\n" << std::endl;

	for(int i = 0; i < wallSet.size(); i++){
	    file << "v " << (wallSet[i].p1.x-1)/5 - 0.5 << " " << "-1/5" << " " << (wallSet[i].p1.y-1)/5 - 0.5 << std::endl;
	    file << "v " << (wallSet[i].p1.x-1)/5 - 0.5 << " " << 1/5 << " " << (wallSet[i].p1.y-1)/5 - 0.5 << std::endl;
	    file << "v " << (wallSet[i].p2.x-1)/5 - 0.5 << " " << "-1/5" << " " << (wallSet[i].p2.y-1)/5 - 0.5 << std::endl;
	    file << "v " << (wallSet[i].p2.x-1)/5 - 0.5 << " " << 1/5 << " " << (wallSet[i].p2.y-1)/5 - 0.5 << std::endl;
	}

	file << std::endl;

	for(int i = 0; i < wallSet.size(); i++){
	    file << "f " << (4*i + 1) << " " << (4*i + 2) << " " << (4*i + 3) << std::endl;
	    file << "f " << (4*i + 2) << " " << (4*i + 3) << " " << (4*i + 4) << std::endl;
	}
    }

    void createMaze(){
	char choice = 'y';
	while(choice == 'y'){
	    addWall();
	    std::cout << "Add another wall? type 'y' to continue" << std::endl;
	    std::cin >> choice;
	}
	createObjFile();
    }
};
