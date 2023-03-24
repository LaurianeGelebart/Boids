#pragma once

#include <cstdlib>
#include <vector>
#include "Obstacle.hpp"

#include "p6/p6.h"

using Vec = glm::vec3 ; 

class Boid {

    private : 
        Vec _position ; 
        Vec _direction ; 
        float _borne ;  
        float _angle ;   
        p6::Color _color;

        
    public : 
        Boid(); 

        Vec get_position() const; 
        Vec get_direction() const; 
        float get_angle() const; 

        void set_position();
        void set_color(p6::Color color);
        void set_direction() ;
        void set_direction(Vec direction) ;
        void set_angle();
        void set_angle(float angle); 

        void collision(const std::vector<Boid>& boids, const std::vector<Obstacle>& obstacles, IHM ihm);  
        void collision_bords(IHM ihm); 
        void bounce(Obstacle obstacle); 
        void collision_obstacles(const std::vector<Obstacle>& obstacles, IHM ihm); 
        void collision_boids(const std::vector<Boid>& boids, IHM ihm);

        void is_close(Boid boid) ;
        void limit_speed(IHM ihm) ;
        double distance(Vec pos) ;
        void draw(p6::Context & ctx); 
        void move(p6::Context& ctx); 

}; 