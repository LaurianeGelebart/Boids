#include "IHM.hpp"
#include <iostream>
    
IHM::IHM()
{
    this->_turn_factor = 0.0005 ; 
    this->_matching_factor = 0.03 ; 
    this->_avoid_factor = 0.005 ; 
    this->_centering_factor = 0.0005 ; 
    this->_too_close = 0.08 ; 
    this->_close = 0.25 ; 
    this->_speed = 0.01 ; 
}

void IHM::draw()
{
    ImGui::Begin("Set params");

    float f = this->_close ; 
    ImGui::SliderFloat("Close", &f, 0.1f, 1.0f);
    this->_close = f ; 

    float f2 = this->_too_close ; 
    ImGui::SliderFloat("Too close", &f2, 0.01f, 0.5f);
    this->_too_close = f2 ; 

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

float IHM::get_too_close(){
  return this->_too_close ; 
}

float IHM::get_close() {
  return this->_close ; 
} 

float IHM::get_speed() {
  return this->_speed ; 
}
