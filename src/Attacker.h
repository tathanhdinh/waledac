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

#ifndef ATTACKER_H
#define ATTACKER_H

#include "Repeater.h"

namespace waledac {

class Attacker : public Repeater
{
private:
	boost::shared_ptr< boost::thread > m_attacker_thread;
	
public:
	Attacker();
	virtual void update_rlist();
	virtual void update_plist();
	virtual std::vector< boost::shared_ptr<Bot> > sub_rlist();
	virtual std::vector< boost::shared_ptr<Bot> > sub_plist();
	
	virtual std::string get_control_command();
	
	virtual void execute();
	virtual void start();
	virtual void wait();
};

}

#endif // ATTACKER_H
