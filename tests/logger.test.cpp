/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logger.test.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmohamed <nmohamed@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/01 15:55:29 by nmohamed          #+#    #+#             */
/*   Updated: 2015/11/01 15:55:29 by nmohamed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "logger.class.hpp"
#include <thread>

int main(void) {
	Logger * l = new Logger("/dev/stdout");
	std::thread t0([l](){
		while (1) {
			l->log("%s", "Thread ZERO");
		}
	});
	std::thread t1([l](){
		while (1) {
			l->log("%s", "Thread ONE");
		}
	});
	t1.join();
	t0.join();
	return 0;
}
