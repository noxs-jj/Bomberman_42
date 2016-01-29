#ifndef JOYSTICK_HPP
# define JOYSTICK_HPP

# include <ft42.class.hpp>

class Joystick : public ft42 {
public:
	int		timer;

	Joystick();
	virtual ~Joystick();
	void read_key(int mode);

private:

};

#endif
