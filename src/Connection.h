/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) <year>  <name of author>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

*/

#ifndef CONNECTION_H
#define CONNECTION_H

#include "Bot.h"
#include "botnet_types.h"

namespace waledac 
{

enum connection_type
{
	CONNECTION_NULL = 0,
	CONNECTION_NORMAL = 1,
	CONNECTION_GETKEY = 2,
	CONNECTION_FIRST = 3,
	CONNECTION_NOTIFY = 4,
	CONNECTION_EMAILS = 5,
	CONNECTION_TASKREQ = 6,
	CONNECTION_WORDS = 7,
	CONNECTION_TASKREP = 8,
	CONNECTION_HTTPSTATS = 9,
	CONNECTION_CREDS = 10,
	CONNECTION_UPDATE_RLIST = 11,
	CONNECTION_UPDATE_PLIST = 12
};

class Connection
{
private:
	bot_t m_beginning;
	bot_t m_end;
	connection_type m_type;
	
public:
	Connection(bot_t& beginning, bot_t& end);
	
	bot_t beginning();
	bot_t end();
	connection_type& type();
};


extern void insert_connections(connections_t& connections, bot_t& beginning, 
													bots_t& ends);
													
extern connection_t find_connection(connections_t& connections, bot_t& begin, bot_t& end);

}

#endif // CONNECTION_H
