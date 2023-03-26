#pragma once

#include <cstdlib>
#include <vector>
#include "Obstacle.hpp"

#include "p6/p6.h"

using Vec = glm::vec3 ; 

class Boid {

    private : 
        Vec _position ; 
        Vec _velocity ; 
        float _borne_velocity ;  
        p6::Color _color;

        
    public : 
        Boid(); 

        Vec get_position() const; 
        Vec get_velocity() const; 

        void update_position();
        void set_color(p6::Color color);

        void collision(const std::vector<Boid>& boids, const std::vector<Obstacle>& obstacles, IHM ihm, p6::Context& ctx);  
        void collision_bords(IHM ihm, p6::Context& ctx); 
        void bounce(Obstacle obstacle); 
        void collision_obstacles(const std::vector<Obstacle>& obstacles, IHM ihm); 
        void collision_boids(const std::vector<Boid>& boids, IHM ihm);

        void limit_speed(IHM ihm) ;
        double distance(Vec pos) ;
        void draw(p6::Context & ctx); 
        void move(p6::Context& ctx); 

}; 