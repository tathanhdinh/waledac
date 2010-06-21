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


#include "UpdatingBotList.h"

namespace waledac
{


/*
 * constructor
 */
UpdatingBotList::UpdatingBotList()
{
	m_bot_list.clear();
	m_update_timestamp = boost::posix_time::to_simple_string(boost::posix_time::ptime());
}


/*
 * constructor with parameters
 */
UpdatingBotList::UpdatingBotList(entries_t& bot_list, std::string& timestamp)
{
	m_bot_list = bot_list;
	m_update_timestamp = timestamp;
}


/*
 * return entry list
 */
entries_t& UpdatingBotList::bot_list()
{
	return m_bot_list;
}


/*
 * return update timestamp;
 */
std::string& UpdatingBotList::update_timestamp()
{
	return m_update_timestamp;
}


}