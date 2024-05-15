#include "Physics.h"
#include "../basicFunctions/sgn.h"
#include "../basicFunctions/flabs.h"
#include "stdio.h"

Vector::Vector(float x, float y)
{
    Vector::x = x;
    Vector::y = y;
}

Vector::Vector() {}
Vector::~Vector() {}

void Vector::set(Vector V)
{
    Vector::x = V.x;
    Vector::y = V.y;
}

void Vector::set(float x,float y)
{
    Vector::x = x;
    Vector::y = y;
}

Vector Vector::operator*(float lambda)
{
    Vector retV;
    retV.x = Vector::x * lambda;
    retV.y = Vector::y * lambda;
    return retV;
}

float Vector::operator*(Vector V)
{
    return Vector::x * V.x + Vector::y * V.y;
}

Vector Vector::operator+(Vector V){
    Vector retV;
    retV.x = Vector::x + V.x;
    retV.y = Vector::y + V.y;
    return retV;
}


Vector Vector::operator-(Vector V){
    Vector retV;
    retV.x = Vector::x - V.x;
    retV.y = Vector::y - V.y;
    return retV;
}

float eucludianDistance(Vector v1,Vector v2)
{
    return sqrtf(powf(v1.x-v2.x,2)+powf(v1.y-v2.y,2));
}

Particle::Particle(){

}

Particle::~Particle(){
    
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

    //if (flabs(dx) + flabs(dy) < (Particles[p1].radius + Particles[p2].radius) * 1.5F)
    {
        if (powf(dx, 2) + powf(dy, 2) <= powf(Particles[p1].radius + Particles[p2].radius, 2))
        {
            return true;
            // if ((sgn(dx) == -sgn(Particles[p1].velocity.x - Particles[p2].velocity.x)) || (sgn(dy) == -sgn(Particles[p1].velocity.y - Particles[p2].velocity.y)))
            // {
            //     return true;
            // }
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
        Particles[i].velocity.x += Particles[i].acceleration.x *deltat;
        Particles[i].velocity.y += Particles[i].acceleration.y *deltat;
        Particles[i].position.x += Particles[i].velocity.x * deltat + Particles[i].acceleration.x * deltat * 0.5F;
        Particles[i].position.y += Particles[i].velocity.y * deltat + Particles[i].acceleration.y * deltat * 0.5F;
    }
}

void PhysicsEngine::collide(uint16_t p1, uint16_t p2)
{
    Vector tempvelp1;
    Vector tempvelp2;
    tempvelp1.set(Particles[p1].velocity-(Particles[p1].position-Particles[p2].position)*((2*Particles[p2].mass/(Particles[p1].mass+Particles[p2].mass))*(((Particles[p1].velocity-Particles[p2].velocity)*(Particles[p1].position-Particles[p2].position))/eucludianDistance(Particles[p1].position,Particles[p2].position))));
    tempvelp2.set(Particles[p2].velocity-(Particles[p2].position-Particles[p1].position)*((2*Particles[p1].mass/(Particles[p2].mass+Particles[p1].mass))*(((Particles[p2].velocity-Particles[p1].velocity)*(Particles[p2].position-Particles[p1].position))/eucludianDistance(Particles[p2].position,Particles[p1].position))));

    Particles[p1].velocity.set(tempvelp1);
    Particles[p2].velocity.set(tempvelp2);
}
