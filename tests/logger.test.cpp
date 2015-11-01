#include "logger.class.hpp"

int main(void) {
	Logger * l = new Logger("/dev/stdout");

	l->log("%s", "Hello World");
	return 0;
}
