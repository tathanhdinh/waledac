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

#ifndef ATTACKER_H
#define ATTACKER_H

#include "Repeater.h"
#include "botnet_types.h"

namespace waledac {

class Attacker : public Repeater
{
private:
	#ifdef THREAD_VERSION
	boost::shared_ptr< boost::thread > m_attacker_thread;
	#endif

public:
	Attacker(unsigned int rlist_size,
					 unsigned int plist_size,
					 unsigned int sub_rlist_size,
					 unsigned int sub_plist_size);
	
	Attacker();
	
// 	virtual bots_t sub_rlist();
// 	virtual bots_t sub_plist();
	
	virtual response_code send_message(message_code message);
	
	virtual void attack(bot_t& target);
	
	#ifdef THREAD_VERSION
	virtual void execute();
	virtual void start();
	virtual void wait();
	#endif
};

}

#endif // ATTACKER_H
