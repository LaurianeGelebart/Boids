#include "Obstacle.hpp"
#include <iostream>
    
void Obstacle::draw(p6::Context & ctx)
{
    ctx.use_fill   = true;
    ctx.fill =  {0.1f, 0.1f, 0.1f} ; 
    ctx.circle(
        p6::Center{this->_position},   
        p6::Radius{this->_radius}
    ); 
}

Obstacle::Obstacle()
{
    this->_position = Vec(p6::random::point(),1.) ;
    this->_radius = p6::random::number(0.1, 0.2) ; 
}

Vec Obstacle::get_position() const
{
    return this->_position ; 
}

float Obstacle::get_radius() const
{
    return this->_radius ; 
}