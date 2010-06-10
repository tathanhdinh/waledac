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

//enum { BOT_COMPROMISED = 1, BOT_NON_COMPROMISED = 0 };
	
Bot::Bot()
{
	// generate random bot id
	uuid bot_uuid;
	bot_uuid.make(UUID_MAKE_V4);
	m_id = bot_uuid.string();	
	
	m_status = IDLE;
}


/*
 * get bot id
 */
const std::string& Bot::id()
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
	if (m_status == COMPROMISED)
		compromised = true;
	return compromised;
}


/*
 * obsolete method (will be replace by Bot::status() = COMPROMISED)
 */
void Bot::compromise()
{
	m_status = COMPROMISED;
	
	/*
	printf("test update\n");
	botnetgraph->update_graph();
	printf("test fin update\n");	
	botnetgraph->graphLayoutView->ResetCamera();
	botnetgraph->graphLayoutView->Render();
	*/
}


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
 *
 */
unsigned int random_number(unsigned int max)
{
	unsigned int random_value = die() % (max + 1);;
	//std::cout << "random value " << random_value << std::endl;
	return random_value;
}


/*
 * merge randomly two lists
 */
std::vector< boost::shared_ptr< Bot > > merge_list(std::vector< boost::shared_ptr< Bot > >& listA, 
												   std::vector< boost::shared_ptr< Bot > >& listB)
{
	std::vector< boost::shared_ptr<Bot> >  total_list = listA;
	for (unsigned int i = 0; i < listB.size(); ++i) {
		total_list.push_back(listB[i]);
	}
	std::random_shuffle(total_list.begin(), total_list.end());
	
	std::vector< boost::shared_ptr<Bot> > merged_list(listA.size());
	std::copy(total_list.begin(), total_list.begin() + merged_list.size(), 
			  merged_list.begin());
	
	return merged_list;
}


}

