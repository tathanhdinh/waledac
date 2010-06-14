/*
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

#include "Connection.h"

namespace waledac
{


/*
 * connection constructor
 */
Connection::Connection(bot_t& beginning, bot_t& end)
{
	m_beginning = beginning;
	m_end = end;
	
	m_type = CONNECTION_NORMAL;
}


/*
 * return beginning of connection
 */
bot_t Connection::beginning()
{
	return m_beginning;
}


/*
 * return end of connection
 */
bot_t Connection::end()
{
	return m_end;
}


/*
 * return type of connection
 */
connection_type& Connection::type()
{
	return m_type;
}


/*===========================================================================*/
/*                    implementation of common functions                     */
/*===========================================================================*/

/*
 * create and insert connections into a connection list
 */
void insert_connections(connections_t& connections, bot_t& beginning, bots_t& ends)
{
	connection_t new_connection;
	for (unsigned int i = 0; i < ends.size(); ++i) {
		new_connection.reset(new Connection(beginning, ends[i]));
		connections.push_back(new_connection);
	}
		
}


/*
 * find a connection in a connection list
 */
connection_t find_connection(connections_t& connections, bot_t& begin, bot_t& end)
{
	connection_t found_connection;

	for (unsigned int i = 0; i < connections.size(); ++i) {
		if ((connections[i]->beginning()->id() == begin->id()) && 
			(connections[i]->beginning()->id() == end->id())) {
			found_connection = connections[i];
		}
	}
	
	return found_connection;
}



}