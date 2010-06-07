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

#include <ossp/uuid++.hh>
//#include <uuid++.hh>

#include <boost/smart_ptr.hpp>
#include <boost/random.hpp>

namespace waledac {

enum { BOT_COMPROMISED = 1, BOT_NON_COMPROMISED = 0 };
	
Bot::Bot()
{
	// generate random bot id
	uuid bot_uuid;
	bot_uuid.make(UUID_MAKE_V4);
	m_id = bot_uuid.string();	
}


/*
 * get id of bot
 */
const std::string& Bot::id()
{
	return m_id;
}


/*
 * check status of bot
 */
bool Bot::is_compromised()
{
	bool compromised = false;
	if (m_status == BOT_COMPROMISED)
		compromised = true;
	return compromised;
}


/*
 * bot is compromised
 */
void Bot::compromise()
{
	m_status = BOT_COMPROMISED;
	return;
}


/*
 * take a random bot from an existing list
 */
boost::uniform_int<> dist(std::numeric_limits<int>::min(), 
						  std::numeric_limits<int>::max());
boost::mt19937 gen;
boost::variate_generator<boost::mt19937, boost::uniform_int<> > die(gen, dist);
boost::shared_ptr<Bot> random_bot(std::vector< boost::shared_ptr<Bot> >& bot_list)
{
	unsigned int random_index = die() % bot_list.size();
	return bot_list[random_index];
}

}

