#include "Physics.h"
#include "../basicFunctions/sgn.h"
#include "../basicFunctions/flabs.h"

Vector::Vector(float x, float y)
{
    Vector::x = x;
    Vector::y = y;
}

void Vector::set(Vector V)
{
    Vector::x = V.x;
    Vector::y = V.y;
}

void Particle::activate(bool value)
{
    isActive = value;
}

void Particle::makeWall(bool value)
{
    isWall = value;
}

PhysicsEngine::PhysicsEngine(uint16_t numOfParticles)
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

bool PhysicsEngine::isColliding(uint16_t p1, uint16_t p2)
{
    dx = Particles[p1].position.x - Particles[p2].position.x;
    dy = Particles[p1].position.y - Particles[p2].position.y;

    if (flabs(dx) + flabs(dy) < (Particles[p1].radius + Particles[p2].radius) * 1.5F)
    {
        if (powf(dx, 2) + powf(dy, 2) <= powf(Particles[p1].radius + Particles[p2].radius, 2))
        {
            if ((sgn(dx) == -sgn(Particles[p1].velocity.x - Particles[p2].velocity.x))||(sgn(dy) == -sgn(Particles[p1].velocity.y - Particles[p2].velocity.y)))
            {
                return true;
            }
        }
    }
    return false;
}

void PhysicsEngine::setSystemAcceleration(Vector sysAcceleration)
{
    for (i = 0; i < numOfParticles; i++)
    {
        Particles[i].acceleration.set(sysAcceleration);
    }
}

void PhysicsEngine::updateParticles(float deltat)
{
    for (i = 0; i < numOfParticles; i++)
    {
        Particles[i].position.x = Particles[i].velocity.x*deltat+Particles[i].acceleration.x*deltat*0.5F;
    }
}

void PhysicsEngine::collide(uint16_t p1, uint16_t p2)
{
    
}
