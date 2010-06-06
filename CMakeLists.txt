project(waledac)

cmake_minimum_required(VERSION 2.8)

find_package(Boost)

set(CMAKE_BUILD_TYPE Release)

set(waledac_botnet_src
	src/Bot.cpp src/Spammer.cpp src/Repeater.cpp src/Protecter.cpp
	src/ServerCC.cpp src/BotnetConfig.cpp src/Attacker.cpp
	src/main.cpp
)

set(waledac_botnet_libraries
	boost_system-mt boost_thread-mt boost_program_options-mt ossp-uuid++
)

add_executable(waledac ${waledac_botnet_src})
target_link_libraries(waledac ${waledac_botnet_libraries})

