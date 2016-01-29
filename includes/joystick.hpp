#ifndef JOYSTICK_HPP
# define JOYSTICK_HPP

# include <ft42.class.hpp>

class Joystick : public ft42 {
public:
	int		timer;

	Joystick(void);
	// Joystick( Joystick const & src );
	// Joystick & operator=( Joystick const & rhs );
	virtual ~Joystick( void );
	void read_key(int mode);
	void change_dir_joystick(t_key *key, int dir);

private:

};

#endif
