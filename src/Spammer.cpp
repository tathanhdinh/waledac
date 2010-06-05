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
#include "BotnetStaticConfiguration.h"

#include <iostream>
#include <boost/smart_ptr.hpp>
#include <boost/random.hpp>

namespace waledac
{

/*
 * merge existing rlist with a new rlist
 */
static std::vector< boost::shared_ptr<Bot> > 
spammer_merge_rlist(std::vector< boost::shared_ptr<Bot> > &existing_rlist, 
					std::vector< boost::shared_ptr<Bot> > &new_rlist)
{
	// not yet implemented
	return existing_rlist;
}


/*
 * constructor
 */
Spammer::Spammer() : Bot()
{
	// initialise rlist
	m_rlist = hardcoded_rlist();
}


/*
 * update rlist from other spammers
 */
void Spammer::update_rlist()
{
	// takes a random repeater from rlist
	boost::shared_ptr<Bot> repeater_target;
	repeater_target = random_bot(m_rlist);
	
	std::cout << "spammer " << Bot::id() << " updates RList from repeater " 
							<< repeater_target->id() << std::endl;
	
	// get subset of rlist from this repeater
	std::vector<boost::shared_ptr<Bot> > new_rlist;
	new_rlist = dynamic_cast<Repeater*>(repeater_target.get())->sub_rlist();
	
	// merge new rlist and existing rlist
	m_rlist = spammer_merge_rlist(m_rlist, new_rlist);
	
	return;
}


/*
 * get command from C&C server
 */
void Spammer::get_command()
{
	// not yet implemented
	return;
}


/*
 * life of spammer
 */
void Spammer::execute()
{
	while (true) {
		update_rlist();
		get_command();
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