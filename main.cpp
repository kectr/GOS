// #include "lib/BitArray2d/BitArray2d.h"
// #include "lib/Window/window.h"
// #include "fonts/font8x8_ib8x8uLSB0-127.h"
#include "stdio.h"
#include "lib/Physics/Physics.h"

int main()
{
    float deltat = 0.33;
    PhysicsEngine hilal(2);
    hilal.Particles[1].position.set(0, 0);
    hilal.Particles[0].position.set(0, 5);
    hilal.Particles[0].velocity.set(0, -1);
    hilal.Particles[0].radius = 1;
    hilal.Particles[1].radius = 1;

    for (int i = 0; i < 30; i++)
    {
        hilal.updateParticles(deltat);
        if(hilal.isColliding(1,2)){
            printf("collide\n");
            hilal.collide(1,2);
        }
        printf("%f - %f", hilal.Particles[0].position.x, hilal.Particles[0].position.y);
        printf(" - %f - %f\n", hilal.Particles[1].position.x, hilal.Particles[1].position.y);
    }

    printf("son  %f - %f", hilal.Particles[0].velocity.x, hilal.Particles[0].velocity.y);
    printf("- %f - %f\n", hilal.Particles[1].velocity.x, hilal.Particles[1].velocity.y);
}