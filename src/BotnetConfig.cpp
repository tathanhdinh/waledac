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

#include "BotnetConfig.h"
#include "Spammer.h"
#include "Repeater.h"
#include "Protecter.h"
#include "ServerCC.h"

namespace waledac
{

//static boost::shared_ptr<BotnetConfig> static_botnet_config;
static std::vector< boost::shared_ptr<Bot> > static_rlist;
static std::vector< boost::shared_ptr<Bot> > static_plist;
static boost::shared_ptr<Bot> static_server;

/*
 * Initialise botnet static configuration
 */
BotnetConfig::BotnetConfig(unsigned int rlist_size, 
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


/*
 * get hardcoded RList
 */
std::vector< boost::shared_ptr<Bot> > hardcoded_rlist()
{
	return static_rlist;
}


/*
 * get hardcoded PList
 */
std::vector< boost::shared_ptr<Bot> > hardcoded_plist()
{
	return static_plist;
}


/*
 * get C&C server
 */
boost::shared_ptr<Bot> servercc()
{
	return static_server;
}


/*
 * insert attackers into RList
 */
void insert_attackers(std::vector< boost::shared_ptr< Bot > >& attackers)
{
	for (unsigned int i = 0; i < attackers.size(); ++i) {
		static_rlist.push_back(attackers[i]);
	}
	return;
}





/*boost::shared_ptr<Bot> random_bot(std::vector< boost::shared_ptr<Bot> >& bot_list)
{
	unsigned int random_index = die() % bot_list.size();
	return bot_list[random_index];
}*/

}