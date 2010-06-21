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
// bots_t Attacker::sub_rlist()
// {
// 	bots_t sub_list;
// 	for (unsigned int i = 0; i < m_sub_rlist_size; ++i) {
// 		sub_list.push_back(Bot::shared_from_this());;
// 	}
// 	
// 	return sub_list;
// }


/*
 * extract a random subset of repeaters from plist
 */
// bots_t Attacker::sub_plist()
// {
// 	return Repeater::sub_plist();
// }


/*
 * depend on type of attack
 */
response_code Attacker::send_message(message_code message)
{
	return Repeater::send_message(message);
}


/*
 * attack a repeater
 */
void Attacker::attack(bot_t& target)
{
	repeater_t repeater;
	repeater = boost::dynamic_pointer_cast<Repeater>(target);
	
	unsigned int repeater_rlist_size;
	repeater_rlist_size = repeater->m_rlist.size();
	repeater->m_rlist.clear();
	
	// replace all entry in RList of target by id of this attacker
	for (unsigned int i = 0; i < repeater_rlist_size; ++i) {
		repeater->m_rlist.push_back(Bot::shared_from_this());
	}
	
	return;
}



#ifdef THREAD_VERSION
/*
 * attacker always reponses requests (send_message, sub_rlist, sub_plist) 
 * from repeaters
 */
void Attacker::execute()
{
	while (true) {
		Bot::status() = RECEIVING_MESSAGE;
		boost::this_thread::sleep(boost::posix_time::hours(
																				boost::posix_time::pos_infin));
	}
	
	return;
}


/*
 * start attacker
 */
void Attacker::start()
{
	std::cout << "start attacker with id : " << Bot::id() << std::endl;
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
