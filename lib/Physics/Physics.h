#ifndef Physics_h
#define Physics_h
#include <cmath>
#include <cstdint>
using namespace std;

class Vector
{
private:
    /* data */
public:
    float x = 0;
    float y = 0;

    Vector();
    Vector(float x,float y);
    ~Vector();
};

class Particle
{
private:
    /* data */
public:
    bool isWall = false;//tarık bunu düşün=?
    bool isActive = false;
    float mass;
    Vector position;
    Vector velocity;
    Vector acceleration;
    float radius = 1; //şekil?    


    Particle();
    Particle(float mass,Vector position,Vector velocity,Vector acceleration,bool isWall);
    ~Particle();

    void Activate();


};


class PhysicsEngine
{
private:
    /* data */
public:
    Particle* Particles = nullptr;
    uint8_t numOfParticles = 0;

    PhysicsEngine(int16_t numOfParticles);
    ~PhysicsEngine();

    bool willCollide(uint8_t p1,uint8_t p2);
    
};
#endif