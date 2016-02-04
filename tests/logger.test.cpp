// ************************************************************************** //
//   24 Bomb                                                                  //
//   By: rcargou <rcargou@student.42.fr>                  :::      ::::::::   //
//   By: nmohamed <nmohamed@student.42.fr>              :+:      :+:    :+:   //
//   By: adjivas <adjivas@student.42.fr>              +:+ +:+         +:+     //
//   By: vjacquie <vjacquie@student.42.fr>          +#+  +:+       +#+        //
//   By: jmoiroux <jmoiroux@student.42.fr>        +#+#+#+#+#+   +#+           //
//   Created: 2015/10/16 17:03:20 by rcargou           #+#    #+#             //
//   Updated: 2015/10/27 14:00:02 by rcargou          ###   ########.fr       //
//                                                                            //
// ************************************************************************** //

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
