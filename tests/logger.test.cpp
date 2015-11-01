/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmohamed <nmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/01 15:55:29 by nmohamed          #+#    #+#             */
/*   Updated: 2015/11/01 16:45:38 by nmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger.class.hpp"
#include <thread>

int main(void) {
	Logger * l = new Logger("/dev/stdout");
	std::thread t0([l](){
		while (1) {
			l->trace("%s", "Thread ZERO");
			l->debug("%s", "Thread ZERO");
			l->info("%s", "Thread ZERO");
			l->warning("%s", "Thread ZERO");
			l->fatal("%s", "Thread ZERO");
		}
	});
	std::thread t1([l](){
		while (1) {
			l->trace("%s", "Thread ONE");
			l->debug("%s", "Thread ONE");
			l->info("%s", "Thread ONE");
			l->warning("%s", "Thread ONE");
			l->fatal("%s", "Thread ONE");
		}
	});
	t1.join();
	t0.join();
	return 0;
}
