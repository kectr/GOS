#include "Physics.h"
#include "../sgn/sgn.h"

Vector::Vector(float x, float y)
{
    Vector::x = x;
    Vector::y = y;
}

void Particle::Activate()
{
    isActive = true;
}

PhysicsEngine::PhysicsEngine(int16_t numOfParticles)
{
    PhysicsEngine::Particles = new Particle[numOfParticles];
    PhysicsEngine::numOfParticles = numOfParticles;
}

PhysicsEngine::~PhysicsEngine()
{
    if (Particles != nullptr)
    {
        delete[] Particles;
    }
}

bool PhysicsEngine::willCollide(uint8_t p1, uint8_t p2)
{
    
}
