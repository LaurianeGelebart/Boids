#include <cstdlib>
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include <vector>

#include "IHM.hpp"
#include "Obstacle.hpp"
#include "Boid.hpp"


std::vector<Boid> boids; 
std::vector<Obstacle> obstacles; 


void add_or_remove_boids(IHM &ihm)
{
    int nb_boids = boids.size(); 
     if (nb_boids<ihm.get_nb_boids()){ 
        for(int i=0 ; i< ihm.get_nb_boids()-nb_boids ; i++){
            Boid b ; 
            boids.push_back(b);
        }
        nb_boids = ihm.get_nb_boids(); 
    } 
    else if (nb_boids>ihm.get_nb_boids()){
        for(int i=0 ; i< nb_boids-ihm.get_nb_boids() ; i++){
            boids.pop_back();
        }
        nb_boids = ihm.get_nb_boids();
    }
}


void add_or_remove_obstacles(IHM &ihm)
{
    int nb_obstacles = obstacles.size(); 
    if (nb_obstacles<ihm.get_nb_obstacles()){
        for(int i=0 ; i< ihm.get_nb_obstacles()-nb_obstacles ; i++){
            Obstacle o ; 
            obstacles.push_back(o);
        }
        nb_obstacles = ihm.get_nb_obstacles(); 
    } 
    else if (nb_obstacles>ihm.get_nb_obstacles()){
        for(int i=0 ; i< nb_obstacles-ihm.get_nb_obstacles() ; i++){
            obstacles.pop_back();
        }
        nb_obstacles = ihm.get_nb_obstacles();
    }
}



int main(int argc, char* argv[])
{
    { // Run the tests
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        // The CI does not have a GPU so it cannot run the rest of the code.
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    // Actual app
    auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    ctx.maximize_window();
        
    IHM ihm ; 

     for(int i=0 ; i<ihm.get_nb_boids() ; i++){
         Boid b ; 
         boids.push_back(b);
     }

     for(int i=0 ; i<ihm.get_nb_obstacles() ; i++){
         Obstacle o ; 
         obstacles.push_back(o);
     }
    
    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background({1.f, 0.7f, 0.2f} );
        ctx.fill = {0.5f, 1.f, 1.f}; 
     
        ihm.draw(); 

        for(size_t i=0 ; i<boids.size() ; i++)
        {   
            boids[i].draw(ctx) ;
            boids[i].collision(boids, obstacles, ihm, ctx) ;
            boids[i].update_position() ; 
        } ;  

        for(size_t j=0 ; j<obstacles.size() ; j++)
        {   
            obstacles[j].draw(ctx) ;
        } ; 

       add_or_remove_boids(ihm) ; 
       add_or_remove_obstacles(ihm) ; 

    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}
