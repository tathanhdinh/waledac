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


#ifndef UPDATINGBOTLIST_H
#define UPDATINGBOTLIST_H

#include "Bot.h"

namespace waledac 
{

class UpdatingBotList
{
private:
	entries_t m_bot_list;
	boost::posix_time::ptime m_update_timestamp;
	
public:
	UpdatingBotList();
	UpdatingBotList(entries_t& bot_list, boost::posix_time::ptime& timestamp);
	
	entries_t& bot_list();
	boost::posix_time::ptime& update_timestamp();
};

}

#endif // UPDATINGBOTLIST_H
