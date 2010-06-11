#ifndef BOTNETTYPES_H
#define BOTNETTYPES_H

	#include <boost/smart_ptr.hpp>
	#include <vector>

	namespace waledac
	{
		class Bot;
		class Botnet;
	}
	
	typedef std::vector< boost::shared_ptr< waledac::Bot > > bots_t;
	typedef boost::shared_ptr< waledac::Bot > bot_t;
	
	typedef boost::shared_ptr< waledac::Botnet > botnet_t;

#endif
