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

#ifndef BOTNETSTATICCONFIGURATION_H
#define BOTNETSTATICCONFIGURATION_H

#include "Bot.h"

#include <boost/smart_ptr.hpp>
#include <vector>

namespace waledac
{

class BotnetConfig
{
public :
	BotnetConfig(unsigned int rlist_size, unsigned int plist_size);
};

//extern boost::shared_ptr<BotnetConfig> static_botnet_config;

extern std::vector< boost::shared_ptr<Bot> > hardcoded_rlist();
extern std::vector< boost::shared_ptr<Bot> > hardcoded_plist();

extern boost::shared_ptr<Bot> servercc();
										
extern void insert_attackers(std::vector< boost::shared_ptr< Bot > >& attackers);

}

#endif // BOTNETSTATICCONFIGURATION_H
