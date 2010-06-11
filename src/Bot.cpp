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

#include "Bot.h"

#include <iostream>
#include <vector>
#include <algorithm>

#include <ossp/uuid++.hh>
//#include <uuid++.hh>

#include <boost/smart_ptr.hpp>
#include <boost/random.hpp>

namespace waledac {

Bot::Bot()
{
	// generate random bot id
	uuid bot_uuid;
	bot_uuid.make(UUID_MAKE_V4);
	m_id = bot_uuid.string();	
	
	m_status = IDLE; // first status of bot
}


/*
 * get bot id
 */
const std::string& Bot::id() const
{
	return m_id;
}


/*
 * get/set bot running status
 */
bot_status& Bot::status()
{
	return m_status;
}


/*
 * check bot compromised status
 */
bool Bot::is_compromised()
{
	bool compromised = false;
	
	if (this->status() == STOPPED) compromised = true;
	return compromised;
}


/*===========================================================================*/
/*                    implementation of common functions                     */
/*===========================================================================*/

boost::uniform_int<> dist(std::numeric_limits<int>::min(), 
						  std::numeric_limits<int>::max());
boost::mt19937 gen;
boost::variate_generator<boost::mt19937, boost::uniform_int<> > die(gen, dist);

/*
 * take a random bot from an existing list
 */
boost::shared_ptr<Bot> random_bot(std::vector< boost::shared_ptr<Bot> >& bot_list)
{
	unsigned int random_index = die() % bot_list.size();
	return bot_list[random_index];
}


/*
 * take a sub list of random bots from an existing list
 */
std::vector< boost::shared_ptr<Bot> > random_bots(std::vector< boost::shared_ptr<Bot> >& bot_list, 
												  unsigned int bot_number)
{
	std::vector< boost::shared_ptr<Bot> > tmplist = bot_list;
	std::random_shuffle(tmplist.begin(), tmplist.end());
	
	std::vector< boost::shared_ptr<Bot> > sublist;
	for (unsigned int i = 0; i < std::min(bot_number, static_cast<unsigned int>
										(bot_list.size())); ++i) {
		sublist.push_back(tmplist[i]);
	}
	
	return sublist;
}


/*
 * get a random number in [0,max]
 */
unsigned int random_number(unsigned int max)
{
	unsigned int random_value = die() % (max + 1);;
	return random_value;
}


/*
 * merge randomly two lists
 */
std::vector< boost::shared_ptr< Bot > > merge_list(std::vector< boost::shared_ptr< Bot > >& original_list, 
												   std::vector< boost::shared_ptr< Bot > >& new_list)
{
	std::vector< boost::shared_ptr<Bot> >  total_list = original_list;
	for (unsigned int i = 0; i < new_list.size(); ++i) {
		total_list.push_back(new_list[i]);
	}
	std::random_shuffle(total_list.begin(), total_list.end());
	total_list = remove_duplicate(total_list);
	std::random_shuffle(total_list.begin(), total_list.end());
	
	std::vector< boost::shared_ptr<Bot> > merged_list;
	merged_list.assign(total_list.begin(), total_list.begin() + original_list.size());
	return merged_list;
}


/*
 * less than compare two smart pointers of bot
 */
bool compare_bot(boost::shared_ptr<Bot> a, boost::shared_ptr<Bot> b)
{
	return (a->id() < b->id());
}


/*
 * unique compare two smart pointer of bot
 */
bool unique_bot(boost::shared_ptr<Bot> a, boost::shared_ptr<Bot> b)
{
	return (a->id() == b->id());
}


/*
 * remove duplicate bots from a list
 */
std::vector< boost::shared_ptr< Bot > > remove_duplicate(
						std::vector< boost::shared_ptr< Bot > >& list)
{
	std::vector< boost::shared_ptr<Bot> > tmplist = list;
	std::sort(tmplist.begin(), tmplist.end(), compare_bot);
	tmplist.erase(std::unique(tmplist.begin(), tmplist.end()), tmplist.end());
	
	return tmplist;
}



}

