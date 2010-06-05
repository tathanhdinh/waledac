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

namespace waledac
{

static boost::shared_ptr<Bot> repeater_random_repeater(std::vector<boost::shared_ptr<Bot> >&  rlist)
{
	unsigned int rlist_size = rlist.size();
	boost::uniform_int<> dist(0, rlist_size);
	boost::mt19937 gen;
	boost::variate_generator<boost::mt19937, boost::uniform_int<> > die(gen, dist);
	
	unsigned int random_index = die();
	
	return rlist[random_index];
}


std::vector<boost::shared_ptr<Bot> > repeater_merge_rlist(std::vector<boost::shared_ptr<Bot> > &existing_rlist, 
														  std::vector<boost::shared_ptr<Bot> > &new_rlist)
{
	return existing_rlist;
}


/*
 * constructor
 */
Repeater::Repeater()
{
	// initialiser rlist 
	//m_rlist = BotnetStaticConfiguration::rlist();
}


/*
 * extract 100 repeater from rlist
 */
std::vector< boost::shared_ptr< Bot > > Repeater::extract_rlist()
{
	// not yet implemented
	return m_rlist;
}



/*
 * update rlist from other repeaters
 */
void Repeater::update_rlist()
{
	// get random repeater
	boost::shared_ptr<Repeater> repeater_target;
	repeater_target.reset(dynamic_cast<Repeater*>(repeater_random_repeater(m_rlist).get()));
	
	// get updating rlist from this spammer
	std::vector<boost::shared_ptr<Bot> > new_rlist = repeater_target->extract_rlist();
	
	// merge new rlist and existing rlist
	m_rlist = repeater_merge_rlist(m_rlist, new_rlist);
	
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