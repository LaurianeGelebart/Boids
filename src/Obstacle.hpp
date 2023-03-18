#pragma once

#include <cstdlib>
#include <vector>

#include "p6/p6.h"

using Vec = glm::vec3 ; 

class Obstacle {

    private : 
        Vec _position ; 
        float _radius ; 
        
    public : 
        Obstacle(); 

        void draw(p6::Context & ctx); 
        Vec get_position() const; 
        float get_radius() const; 

}; 