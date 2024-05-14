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
    Vector(float x, float y);
    ~Vector();
    
    void set(Vector V);
    // Vector operator*(float lambda);
    // Vector operator+(Vector V);
    // Vector operator-(Vector V);
    
};

class Particle
{
private:
    /* data */
public:
    bool isWall = false; // tarık bunu düşün=?
    bool isActive = false;
    float mass;
    Vector position;
    Vector velocity;
    Vector acceleration;
    float radius = 1; // şekil?

    Particle();
    Particle(float mass, Vector position, Vector velocity, Vector acceleration, bool isWall);
    ~Particle();

    void activate(bool value);
    void makeWall(bool value);
};

class PhysicsEngine
{
private:
    /* data */
public:
    Particle *Particles = nullptr;
    uint16_t numOfParticles = 0;
    int16_t i = 0;
    int8_t dvx = 0;
    int8_t dvy = 0;
    float dx = 0;
    float dy = 0;
    float tempvx = 0;
    float tempvy = 0;

    PhysicsEngine(uint16_t numOfParticles);
    ~PhysicsEngine();

    bool isColliding(uint16_t p1, uint16_t p2);
    void setSystemAcceleration(Vector acceleration);
    void updateParticles(float deltat);
    void collide(uint16_t p1, uint16_t p2);
};
#endif