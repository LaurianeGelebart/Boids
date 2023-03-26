#pragma once

#include <cstdlib>

#include "p6/p6.h"


class IHM {

    private : 
        float _turn_factor = 0.0005  ; 
        float _matching_factor = 0.03 ;
        float _avoid_factor = 0.005 ; 
        float _centering_factor = 0.0005 ; 
        float _collision_radius = 0.08 ; 
        float _detection_radius = 0.25 ; 
        float _speed = 0.01 ; 
        
    public : 
        IHM(); 
        void draw(); 
        float get_turn_factor()  ; 
        float get_matching_factor() ;  
        float get_avoid_factor() ; 
        float get_centering_factor() ; 
        float get_collision_radius() ; 
        float get_detection_radius() ; 
        float get_speed() ;

}; 