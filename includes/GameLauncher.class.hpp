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

#ifndef GAMELAUNCHER_CLASS_HPP
# define GAMELAUNCHER_CLASS_HPP

# include <ft42.class.hpp>

class Gamelauncher : ft42 {
public:
    Gamelauncher();
    virtual ~Gamelauncher();

    static void intro_lauch_game();
    static void campaign_new();
		static void campaign_continue();
    static void campaign_new_coop();

    static void run_multi_2();
    static void run_multi_3();
    static void run_multi_4();
    static void run_multi_5();

    static void run_arena_2();
    static void run_arena_3();
    static void run_arena_4();
    static void run_arena_5();

    static void retry_previous_game();

private:
    Gamelauncher( Gamelauncher const & src ) = delete;
    Gamelauncher & operator=( Gamelauncher const & rhs ) = delete;

};

#endif
