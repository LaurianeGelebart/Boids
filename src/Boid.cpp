#include "IHM.hpp"
#include "Boid.hpp"
#include <iostream>
#include <math.h>


Boid::Boid()
{
    this->_position = Vec(p6::random::point(),1.) ;
    this->_borne = 0.003;  
    this->_angle = (float)(p6::random::integer(0, 360))*M_PI/180.0; 
    this->_direction = Vec(cos(_angle), sin(_angle) ,1.) ;
    this->_color = {0.5f, 0.2f, 0.2f} ; 
}

void Boid::draw(p6::Context& ctx)
{  
    ctx.use_fill   = true;
    ctx.use_stroke = false; 
    ctx.fill = this->_color;
    ctx.equilateral_triangle(
        p6::Center{this->_position},   
        p6::Radius{0.03},
        p6::Angle{p6::Radians{this->_angle}}
    ); 
}

Vec Boid::get_position() const
{
    return this->_position ; 
}

Vec Boid::get_direction() const
{
    return this->_direction ; 
}

float Boid::get_angle() const
{
    return this->_angle ; 
}

void Boid::set_position()
{
    this->_position =  this->_position + this->_direction ;
    this->set_angle(); 
}

void Boid::set_direction()
{
     this->_direction.x = cos(_angle) ; 
     this->_direction.y = sin(_angle) ;
}

void Boid::set_color(p6::Color color)
{
    this->_color = color ; 
}

void Boid::set_angle(float angle)
{
    this->_angle = angle;
}

void Boid::set_angle()
{
    this->_angle = atan(this->_direction.y/this->_direction.x);
    if(this->_direction.x < 0) this->_angle+=M_PI;
}


void Boid::collision(const std::vector<Boid>& boids, const std::vector<Obstacle>& obstacles, IHM ihm)
{
    collision_boids(boids, ihm); 
    collision_obstacles(obstacles, ihm); 
    collision_bords(ihm); 
}

void Boid::collision_boids(const std::vector<Boid>& boids, IHM ihm)
{
    double close_x =0, close_y=0, xpos_avg=0, ypos_avg=0, xdir_avg=0, ydir_avg=0 ; 
    int neighboring_boids = 0 ; 

   for (size_t i=0 ; i<sizeof(boids); i++){
        double distance = this->distance(boids[i].get_position());     
        if(distance != 0 ){
            if (distance < ihm.get_too_close() ){ 
                close_x += this->_position.x - boids[i].get_position().x;
                close_y += this->_position.y - boids[i].get_position().y; 
            }  
            else if(distance < ihm.get_close() ) {
                neighboring_boids += 1 ;
                xpos_avg += boids[i].get_position().x ;
                ypos_avg += boids[i].get_position().y ;
                xdir_avg += boids[i].get_direction().x ;
                ydir_avg += boids[i].get_direction().y ;
            } 
        }
   }
   if (neighboring_boids > 0) {
        xpos_avg = xpos_avg/neighboring_boids ;
        ypos_avg = ypos_avg/neighboring_boids ;
        xdir_avg = xdir_avg/neighboring_boids ;
        ydir_avg = ydir_avg/neighboring_boids ;

        this->_direction.x = (this->_direction.x + 
            (xpos_avg - this->_position.x)*ihm.get_centering_factor() + 
            (xdir_avg - this->_direction.x)*ihm.get_matching_factor()) ;
        this->_direction.y = (this->_direction.y + 
            (ypos_avg - this->_position.y)*ihm.get_centering_factor() + 
            (ydir_avg - this->_direction.y)*ihm.get_matching_factor()) ;
    }
    this->_direction.x += close_x*ihm.get_avoid_factor();
    this->_direction.y += close_y*ihm.get_avoid_factor();

    limit_speed(ihm); 
}

void Boid::collision_bords(IHM ihm)
{
    if (this->_position.x > 2-0.4){
         this->_direction.x = this->_direction.x - ihm.get_turn_factor(); 
    }
    if (this->_position.x < -2+0.4 ) {
         this->_direction.x = this->_direction.x + ihm.get_turn_factor(); 
    }
    if (this->_position.y > 1-0.4){
         this->_direction.y = this->_direction.y - ihm.get_turn_factor(); 
    } 
    if (this->_position.y < -1+0.4){
         this->_direction.y = this->_direction.y +  ihm.get_turn_factor(); 
    }
}

void Boid::collision_obstacles(const std::vector<Obstacle>& obstacles, IHM ihm)
{
    for (size_t i=0 ; i<sizeof(obstacles); i++){
        double distance = this->distance(obstacles[i].get_position());
        if(distance < obstacles[i].get_radius()){
            if (this->_position.x > obstacles[i].get_position().x){
                this->_direction.x = this->_direction.x + ihm.get_turn_factor()*10; 
            }
            if (this->_position.x < obstacles[i].get_position().x) {
                this->_direction.x = this->_direction.x - ihm.get_turn_factor()*10; 
            }
            if (this->_position.y > obstacles[i].get_position().y){
                this->_direction.y = this->_direction.y + ihm.get_turn_factor()*10; 
            } 
            if (this->_position.y < obstacles[i].get_position().y){
                this->_direction.y = this->_direction.y -  ihm.get_turn_factor()*10; 
            }
        }
    }
    limit_speed(ihm); 
} 


void Boid::limit_speed(IHM ihm)
{
    float speed = std::sqrt(this->_direction.x*this->_direction.x + this->_direction.y*this->_direction.y); 
    
    if(speed < ihm.get_speed()-this->_borne) speed = ihm.get_speed()-this->_borne ;  

    if (speed < ihm.get_speed()-this->_borne) {
        this->_direction = (this->_direction/speed)*(ihm.get_speed()-this->_borne) ; 
        
    }
    if (speed > ihm.get_speed()+this->_borne) {
        this->_direction = (this->_direction/speed)*(ihm.get_speed()+this->_borne) ; 
    }
}


double Boid::distance(Vec pos)
{
    return std::sqrt( std::pow( this->_position.x - pos.x ,2)  +  std::pow( this->_position.y - pos.y ,2) ) ; 
}