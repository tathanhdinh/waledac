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
#include "Botnet.h"
#include "Connection.h"

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
	
	// bot in idle status
	m_status = IDLE;
	
	// no connection
	m_connections.clear();
}


/*
 * get id of bot
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
 * check status of bot
 */
bool Bot::is_compromised()
{
	bool compromised = false;
	if (this->status() == STOPPED) compromised = true;
	return compromised;
}


/*
 * get all connections of bot
 */
connections_t& Bot::connections()
{
	return m_connections;
}


/*===========================================================================*/
/*                    implementation of common functions                     */
/*===========================================================================*/

/*
 * take a random bot from an existing list
 */
boost::uniform_int<> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
boost::mt19937 gen;
boost::variate_generator<boost::mt19937, boost::uniform_int<> > die(gen, dist);
bot_t random_bot(bots_t& bot_list)
{
	unsigned int random_index = die() % bot_list.size();
	return bot_list[random_index];
}


/*
 * take a sub list of random bots from an existing list
 */
bots_t random_bots(bots_t& bot_list, unsigned int bot_number)
{
	bots_t tmplist = bot_list;
	std::random_shuffle(tmplist.begin(), tmplist.end());

	bots_t sublist;
	for (unsigned int i = 0; i < std::min(bot_number, static_cast<unsigned int>(bot_list.size())); ++i) {
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
	return random_value;
}


/*
 * merge randomly two lists
 */
bots_t merge_list(bots_t& original_list, bots_t& new_list)
{
	bots_t total_list = original_list;
	for (unsigned int i = 0; i < new_list.size(); ++i) {
		total_list.push_back(new_list[i]);
	}
        
	std::random_shuffle(total_list.begin(), total_list.end());
	total_list = remove_duplicate(total_list);
	std::random_shuffle(total_list.begin(), total_list.end());
        
	bots_t merged_list;
	merged_list.assign(total_list.begin(), total_list.begin() + original_list.size());
	return merged_list;
}


/*
 * less than compare two smart pointers of bot
 */
bool compare_bot(bot_t a, bot_t b)
{
	return (a->id() < b->id());
}


/*
 * unique compare two smart pointer of bot
 */
bool unique_bot(bot_t a, bot_t b)
{
	return (a->id() == b->id());
}


/*
 * remove duplicate bots from a list
 */
bots_t remove_duplicate(bots_t& list)
{
	bots_t tmplist = list;
	std::sort(tmplist.begin(), tmplist.end(), compare_bot);
	tmplist.erase(std::unique(tmplist.begin(), tmplist.end()), tmplist.end());
        
	return tmplist;
}


/*
 * update connections for a bot
 */
void update_connections(bot_t& bot, bots_t& connected_bots)
{
	connections_t new_connections;
	insert_connections(new_connections, bot, connected_bots);
	
	bot->connections() = new_connections;
	//std::cout << "update connections : " << new_connections.size() << std::endl;
	return;
}


/*
 * refrest status of all connections
 */
void refresh_connections(bot_t& bot)
{
	for (unsigned int i = 0; i < bot->connections().size(); ++i) {
		bot->connections()[i]->type() = CONNECTION_NORMAL;
	}
	return;
}


}

