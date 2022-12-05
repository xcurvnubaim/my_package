#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <dirent.h>

class jsonloader
{
    public:

    static void get(std::string path, std::vector<std::string> &filename_array, std::vector<std::string> &data_array){
        struct dirent *entry = nullptr;
        DIR *dp = opendir(path.c_str());
        while ((entry = readdir(dp))){
            std::string filename = entry->d_name;
            if(filename.find(".json",0)!=std::string::npos){
                std::cout << filename << "---";
                filename_array.push_back(filename);
                std::ifstream inFile;
                inFile.open(path+filename); //open the input file
                
                std::stringstream strStream;
                strStream << inFile.rdbuf(); //read the file
                std::string config = strStream.str(); //str holds the content of the file
                data_array.push_back(config);
                std::cout << "config ok\n";
            }
        }
    }

    static void write(std::string path, std::vector<std::string> &filename_array, std::vector<std::string> &data_array){
        for (int i = 0; i < int(filename_array.size()); i++)
        {
            // std::cout << filename_array[i] << " ; " << data_array[i] << std::endl;
            std::ofstream file(path + filename_array[i]);
            if(file){
                file << data_array[i];
                file.close();
                std::cout << "succes creating " << filename_array[i] << "\n";
            } else {
                std::cout << "error creating files\n";
            }
        }
    }
    
};

void hello(){
    std::cout << "hello world\n";
}