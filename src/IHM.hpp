#pragma once

#include <cstdlib>

#include "p6/p6.h"


class IHM {

    private : 
        float _turn_factor  ; 
        float _matching_factor ;  
        float _avoid_factor ; 
        float _centering_factor ; 
        float _too_close ; 
        float _close ; 
        float _speed ; 
        
    public : 
        IHM(); 
        void draw(); 
        float get_turn_factor()  ; 
        float get_matching_factor() ;  
        float get_avoid_factor() ; 
        float get_centering_factor() ; 
        float get_too_close() ; 
        float get_close() ; 
        float get_speed() ;

}; 