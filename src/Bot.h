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

#ifndef BOT_H
#define BOT_H

#include <string>
//#include <boost/enable_shared_from_this.hpp>
#include <boost/smart_ptr.hpp>

namespace waledac 
{

class Bot : public boost::enable_shared_from_this< Bot >
{
private :
	std::string m_id;
	unsigned int m_status;

public :
	Bot();
	const std::string& id();
	void compromise();
	bool is_compromised();
	
	virtual void execute() = 0;
	virtual void start() = 0;
 	virtual void wait() = 0;
};

}


#endif // BOT_H
