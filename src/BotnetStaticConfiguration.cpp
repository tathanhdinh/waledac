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

#include "BotnetStaticConfiguration.h"
#include "Spammer.h"
#include "Repeater.h"
#include "Protecter.h"
#include "ServerCC.h"

#include <boost/random.hpp>

namespace waledac
{

boost::uniform_int<> dist(std::numeric_limits<int>::min(), 
						  std::numeric_limits<int>::max());
boost::mt19937 gen;
boost::variate_generator<boost::mt19937, boost::uniform_int<> > die(gen, dist);

boost::shared_ptr<BotnetStaticConfiguration> hardcoded_config;
static std::vector< boost::shared_ptr<Bot> > static_rlist;
static std::vector< boost::shared_ptr<Bot> > static_plist;
static boost::shared_ptr<Bot> static_server;

/*
 * Initialise botnet static configuration
 */
BotnetStaticConfiguration::BotnetStaticConfiguration(unsigned int rlist_size, 
													 unsigned int plist_size)
{
	static_rlist.resize(rlist_size);
	for (unsigned int i = 0; i < static_rlist.size(); ++i) {
		static_rlist[i].reset(new Repeater());
	}
	
	static_plist.resize(plist_size);
	for (unsigned int i = 0; i < static_plist.size(); ++i) {
		static_plist[i].reset(new Protecter());
	}
	
	static_server.reset(new ServerCC());
}


std::vector< boost::shared_ptr<Bot> > hardcoded_rlist()
{
	return static_rlist;
}


std::vector< boost::shared_ptr<Bot> > hardcoded_plist()
{
	return static_plist;
}


boost::shared_ptr<Bot> servercc()
{
	return static_server;
}

boost::shared_ptr<Bot> random_bot(std::vector< boost::shared_ptr<Bot> >& bot_list)
{
	unsigned int random_index = die() % bot_list.size();
	//std::cout << "random_index : " << random_index << std::endl;
	//std::cout << bot_list[random_index]->id() << std::endl;	
	return bot_list[random_index];
}

}