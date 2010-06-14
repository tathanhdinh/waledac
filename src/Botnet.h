/*
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Library General Public
   License version 2 as published by the Free Software Foundation.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Library General Public License for more details.

   You should have received a copy of the GNU Library General Public License
   along with this library; see the file COPYING.LIB.  If not, write to
   the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.
*/

#ifndef BOTNET_H
#define BOTNET_H

#include "Bot.h"
#include "botnet_types.h"

#include <boost/smart_ptr.hpp>


namespace waledac {

class Botnet : public boost::enable_shared_from_this< Botnet >
{
public:
	Botnet(unsigned int repeaters_number, unsigned int protecters_number, 
		   unsigned int spammers_number, unsigned int attackers_number);
		   
	void init();
	void start();
	
	#ifdef THREAD_VERSION
	void wait();
	#endif
	
	bots_t repeaters_list();
	bots_t protecters_list();
	bots_t spammers_list();
	bots_t attackers_list();
	bot_t server();
	
private:	
	bots_t repeaters;
	bots_t protecters;
	bots_t spammers;
	bots_t attackers;
	bot_t server_cc;
};

}
#endif // BOTNET_H
