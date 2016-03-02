#ifndef PARTICLE_CLASS_HPP
# define PARTICLE_CLASS_HPP

# include <list>
# include <entity.class.hpp>
# define N_PARTICLES 500
// #include <event.class.hpp>

class Entity;
// class Event;
class Particle : public Entity {
public:
	Particle( float x, float y, float z, int status, int model );
	Particle( Particle const & src );
	Particle & operator=( Particle const & rhs );
	~Particle( void );

	static std::list<Particle*> *list;

	float pos_z;
	void update();

	static void update_all();
	static void boom(float n, float x, float y, float z);
	static void obstacle(float x, float y, float z, float velx, float vely, float velz, int model);
	int cycle;

private:

	long long int lifetime;
	float velx;
	float vely;
	float velz;

	Particle( void );


};

#endif