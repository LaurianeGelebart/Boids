#include "IHM.hpp"
#include <iostream>
    
IHM::IHM()  // TODO remove it and move default value to .hpp
{
}

void IHM::draw()
{
    ImGui::Begin("Set params");

    float f = this->_detection_radius ; 
    ImGui::SliderFloat("Close", &f, 0.1f, 1.0f);
    this->_detection_radius = f ; 

    float f2 = this->_collision_radius ; 
    ImGui::SliderFloat("Too close", &f2, 0.01f, 0.5f);
    this->_collision_radius = f2 ; 

    float f3 = this->_turn_factor*1000 ; 
    ImGui::SliderFloat("Turn factor", &f3, 0.1f, 1.0f);
    this->_turn_factor = f3/1000 ; 

    float f4 = this->_speed ; 
    ImGui::SliderFloat("Speed", &f4, 0.001f, 0.03f);
    this->_speed = f4; 

    ImGui::End();
}

float IHM::get_turn_factor() {
  return this->_turn_factor ; 
}

float IHM::get_matching_factor() {
  return this->_matching_factor ; 
} 

float IHM::get_avoid_factor() {
  return this->_avoid_factor ; 
}

float IHM::get_centering_factor() {
  return this->_centering_factor ; 
}

float IHM::get_collision_radius(){
  return this->_collision_radius ; 
}

float IHM::get_detection_radius() {
  return this->_detection_radius ; 
} 

float IHM::get_speed() {
  return this->_speed ; 
}
