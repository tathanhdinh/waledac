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
#include "Protecter.h"

namespace waledac
{

boost::shared_ptr<BotnetStaticConfiguration> hardcoded_config;
static std::vector< boost::shared_ptr<Bot> > static_rlist(500);
static std::vector< boost::shared_ptr<Bot> > static_plist(10);
	
BotnetStaticConfiguration::BotnetStaticConfiguration()
{
	for (unsigned int i = 0; i < static_rlist.size(); ++i) {
		static_rlist[i].reset(new Spammer());
	}
	
	for (unsigned int i = 0; i < static_plist.size(); ++i) {
		//static_plist[i].reset(new Protecter());
	}
}


/*std::vector< boost::shared_ptr< Bot > > BotnetStaticConfiguration::plist()
{
	return static_plist;
}


std::vector< boost::shared_ptr< Bot > > BotnetStaticConfiguration::rlist()
{
	return static_rlist;
}*/

std::vector< boost::shared_ptr<Bot> > hardcoded_rlist()
{
	return static_rlist;
}


std::vector< boost::shared_ptr<Bot> > hardcoded_plist()
{
	return static_plist;
}

}