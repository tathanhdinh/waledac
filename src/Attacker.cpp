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

#include "Attacker.h"
#include <iostream>

namespace waledac
{

/*
 * constructor with parameters
 */
Attacker::Attacker(unsigned int rlist_size, 
									 unsigned int plist_size, 
									 unsigned int sub_rlist_size, 
									 unsigned int sub_plist_size): Repeater(rlist_size, 
																													plist_size, 
																													sub_rlist_size, 
																													sub_plist_size)
{
}


	
/*
 * constructor
 */
Attacker::Attacker() : Repeater()
{
}


/*
 * sybil attack
 */
bots_t Attacker::sub_rlist()
{
	bots_t sub_list;
	unsigned int sub_list_size;
	
	sub_list_size = Repeater::default_sub_rlist_size();
	for (unsigned int i = 0; i < sub_list_size; ++i) {
		sub_list.push_back(Bot::shared_from_this());
	}
	
	return sub_list;
}


/*
 * extract a random subset of repeaters from plist
 */
bots_t Attacker::sub_plist()
{
	return Repeater::sub_plist();
}


/*
 * update plist from other repeaters
 */
void Attacker::update_plist()
{
	//std::cout << "\033[01;34m" << "fake ";
	//Repeater::update_plist();
	return;
}


/*
 * update rlist from other repeaters
 */
void Attacker::update_rlist()
{
	//std::cout << "\033[01;31m" << "fake ";
	//Repeater::update_rlist();
	return;
}


/*
 * depend on type of attack
 */
response_code Attacker::send_message(message_code message)
{
	// always response stop when receive a message from spammer
	return RESPONSE_STOP;
}


#ifdef THREAD_VERSION
/*
 * life of attacker
 */
void Attacker::execute()
{
	waledac::Repeater::execute();
	return;
}


/*
 * start attacker
 */
void Attacker::start()
{
	//std::cout << "start attacker with id : " << Bot::id() << std::endl;
	m_attacker_thread.reset(new boost::thread(boost::bind(&Attacker::execute, this)));
	return;
}


/*
 * wait until attacker stop
 */
void Attacker::wait()
{
	m_attacker_thread->join();
	return;
}
#endif


}
