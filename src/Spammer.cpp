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

#include "Spammer.h"
#include "Repeater.h"
#include "Botnet.h"
#include "Bot.h"

#include <iostream>
#include <boost/smart_ptr.hpp>
#include <boost/random.hpp>
#include <boost/format.hpp>

namespace waledac
{

/*
 * merge existing rlist with a new rlist
 */
static std::vector< boost::shared_ptr<Bot> > 
spammer_merge_rlist(std::vector< boost::shared_ptr<Bot> > &existing_rlist, 
					std::vector< boost::shared_ptr<Bot> > &new_rlist)
{
	return merge_list(existing_rlist, new_rlist);
}


/*
 * constructor
 */
Spammer::Spammer() : Bot()
{
	// initialise rlist
	m_rlist.clear();
}


/*
 * update rlist from other spammers
 */
void Spammer::update_rlist()
{
	boost::shared_ptr<Bot> repeater_target;
	std::vector<boost::shared_ptr<Bot> > received_rlist;
	unsigned int nb_try = 0;
	
	// repeat
	if (m_rlist.size() > 0) {
		while (true) {
			// takes a random repeater from rlist
			repeater_target = random_bot(m_rlist);
			
			std::cout << "\033[22;32m" 
						<< boost::format("%1$'-'8s %2$'-'36s %3$'-'27s %4$'-'36s\n") 
						% "spammer" % Bot::id() % "updates RList from repeater" % repeater_target->id();
						
			// get subset of rlist from this repeater
			received_rlist = dynamic_cast<Repeater*>(repeater_target.get())->sub_rlist();
			
			if (received_rlist.size() > 0) { // until received non-empty list
				// merge new rlist and existing rlist
				m_rlist = spammer_merge_rlist(m_rlist, received_rlist);
				break;
			}
			
			nb_try++;
			if (nb_try >= 10) break;
		}
	}
	
	//std::cout << "received list size : " << received_rlist.size() << std::endl;
	
	return;
}


/*
 * get command from C&C server
 */
void Spammer::request_command()
{
	// takes a random repeater from rlist
	boost::shared_ptr<Bot> repeater_proxy;
	repeater_proxy = random_bot(m_rlist);
	
	std::cout << "\033[01;36m" 
				<< boost::format("%1$'-'8s %2$'-'36s %3$'-'28s %4$'-'36s\n") 
				% "spammer" % Bot::id() % "get command through repeater" % repeater_proxy->id();
				
	unsigned int received_command = dynamic_cast<Repeater*>
										(repeater_proxy.get())->request_command();
	if (received_command == COMMAND_FROM_ATTACKER) {
		Bot::compromise();
		std::cout << "spammer is compromised" << std::endl;
	}
	
	return;
}


/*
 * return rlist
 */
std::vector< boost::shared_ptr< Bot > > Spammer::rlist()
{
	return m_rlist;
}


/*
 * initialise rlist before running
 */
void Spammer::init()
{
	m_rlist = Botnet::repeaters_list();
	return;
}


/*
 * life of spammer
 */
void Spammer::execute()
{	
	while (true) {
		update_rlist();
		request_command();
		sleep(5);
	}
	
	return;
}


/*
 * start spammer thread
 */
void Spammer::start()
{
	std::cout << "start spammer with id : " << Bot::id() << std::endl;
	m_spammer_thread.reset(new boost::thread(boost::bind(&Spammer::execute, 
														 *this)));
	return;
}


/*
 * wait until spammer thread stop
 */
void Spammer::wait()
{
	m_spammer_thread->join();
	return;
}

}