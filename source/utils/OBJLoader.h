#pragma once

#include "libs.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>


static const std::vector<Vertex> LoadObj(const char *filename){

    std::vector<glm::vec3> vertex_position;
    std::vector<glm::vec2> vertex_texcoord;
    std::vector<glm::vec3> vertex_normal;

    std::vector<GLint> vertex_position_idx;
    std::vector<GLint> vertex_texcoord_idx;
    std::vector<GLint> vertex_normal_idx;

    std::vector<Vertex> vertices;

    std::string row = "";
    std::stringstream ss;
    std::ifstream file(filename);

    std::string prefix = "";
    glm::vec3 tmp_vec3;
    glm::vec2 tmp_vec2;
    GLint tmp_idx;

    if(!file.is_open()){
        std::cerr << "could not open file " << filename << "\n";
        exit(EXIT_FAILURE);
    }

    while(std::getline(file, row)){

        ss.clear();
        ss.str(row);
        ss >> prefix;

        if(prefix == "v"){
            ss >> tmp_vec3.x >> tmp_vec3.y >> tmp_vec3.z;
            vertex_position.push_back(tmp_vec3);
        }
        else if(prefix == "vt"){
            ss >> tmp_vec2.x >>  tmp_vec2.y;
            vertex_texcoord.push_back(tmp_vec2);           
        }
        else if(prefix == "vn"){
            ss >> tmp_vec3.x >> tmp_vec3.y >> tmp_vec3.z;
            vertex_normal.push_back(tmp_vec3);
        }
        else if(prefix == "f"){
            
            int counter = 0;

            while(ss >> tmp_idx){

                if(counter == 0){
                    vertex_position_idx.push_back(tmp_idx);
                }
                else if(counter == 1){
                    vertex_texcoord_idx.push_back(tmp_idx);
                }
                else if(counter == 2){
                    vertex_normal_idx.push_back(tmp_idx);
                }

                if(ss.peek() == '/'){
                    counter++;
                    ss.ignore(1, '/');
                }
                else if(ss.peek() == ' '){
                    counter++;
                    ss.ignore(1, ' ');
                }

                /* reset counter */
                if(counter > 2){
                    counter = 0;
                }
            }
        }
    }

    vertices.resize(vertex_position_idx.size(), Vertex());

    for(int i=0; i<vertices.size(); i++){
        
        int position_idx = vertex_position_idx[i]-1;
        int texcoord_idx = vertex_texcoord_idx[i]-1;
        int normal_idx   = vertex_normal_idx[i]-1;

        vertices[i].position = vertex_position[position_idx];
        vertices[i].texcoord = vertex_texcoord[texcoord_idx];
        vertices[i].normal   = vertex_normal[normal_idx];
        vertices[i].color    = glm::vec3(1.f, 1.f, 1.f);
    }

    return vertices;
}