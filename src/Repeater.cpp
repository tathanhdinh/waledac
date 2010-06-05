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

#include "Repeater.h"
#include "BotnetStaticConfiguration.h"

#include <boost/smart_ptr.hpp>
#include <boost/random.hpp>
#include <algorithm>

namespace waledac
{


std::vector<boost::shared_ptr<Bot> > repeater_merge_rlist(
									std::vector<boost::shared_ptr<Bot> > &existing_rlist, 
									std::vector<boost::shared_ptr<Bot> > &new_rlist)
{
	// not yet implemented
	return existing_rlist;
}


/*
 * constructor
 */
Repeater::Repeater()
{
	// initialiser rlist 
	m_rlist = hardcoded_rlist();
	std::cout << "new repeater with id : " << Bot::id() << std::endl;
}


/*
 * extract 100 repeater from rlist
 */
std::vector< boost::shared_ptr< Bot > > Repeater::sub_rlist()
{
	std::cout << "sub_rlist" << std::endl;
	std::vector< boost::shared_ptr<Bot> > sublist(100);
	//std::cout << "rlist_size : " << m_rlist.size() << std::endl;
	//std::copy(m_rlist.begin(), m_rlist.begin() + 99, sublist.begin());
	return sublist;
}



/*
 * update rlist from other repeaters
 */
void Repeater::update_rlist()
{
	// get random repeater
	boost::shared_ptr<Bot> repeater_target;
	repeater_target = random_bot(m_rlist);
	
	// get updating rlist from this spammer
	//std::vector<boost::shared_ptr<Bot> > new_rlist = repeater_target->sub_rlist();
	
	// merge new rlist and existing rlist
	//m_rlist = repeater_merge_rlist(m_rlist, new_rlist);
	
	return;
}


/*
 * update plist from other repeaters
 */
void Repeater::update_plist()
{
	return;
}


/*
 * life of repeater
 */
void Repeater::run()
{
	while (true) {
		update_rlist();
		update_plist();
	}
	
	return;
}

}