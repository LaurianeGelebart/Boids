#include <cstdlib>
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"
#include <vector>

#include "IHM.hpp"
#include "Obstacle.hpp"
#include "Boid.hpp"

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

    int nb_boids = 40; 
    int nb_obstacles = 3; 

    std::vector<Boid> boids; 
     for(int i=0 ; i<nb_boids ; i++){
         Boid b ; 
         boids.push_back(b);
     }

     std::vector<Obstacle> obstacles; 
     for(int i=0 ; i<nb_obstacles ; i++){
         Obstacle o ; 
         obstacles.push_back(o);
     }
    
    // Declare your infinite update loop.
    ctx.update = [&]() {
        ctx.background({1.f, 0.7f, 0.2f} );
        ctx.fill = {0.5f, 1.f, 1.f}; 
     
        ihm.draw(); 

        for(int i=0 ; i<nb_boids ; i++)
        {   
            boids[i].draw(ctx) ;
            boids[i].collision(boids, obstacles, ihm) ;
            boids[i].set_position() ; 
        } ;  

        for(int j=0 ; j<nb_obstacles ; j++)
        {   
            obstacles[j].draw(ctx) ;
        } ; 

    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}