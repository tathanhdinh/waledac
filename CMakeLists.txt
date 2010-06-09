cmake_minimum_required(VERSION 2.8)

project(waledac)

find_package(Boost REQUIRED)
find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

set(CMAKE_BUILD_TYPE Release)

include_directories(/usr/local/include/vtk-5.6/)
link_directories(/usr/local/lib/vtk-5.6/)

set(waledac_botnet_src
	src/Bot.cpp src/Spammer.cpp src/Repeater.cpp src/Protecter.cpp
	src/ServerCC.cpp src/Attacker.cpp src/Botnet.cpp
	src/main.cpp
)

set(waledac_botnet_vtk_src
	src/BotnetVisual.cpp
)

set(waledac_botnet_libraries
	boost_system-mt boost_thread-mt boost_program_options-mt ossp-uuid++
)

set(waledac_botnet_vtk_libraries
	vtkHybrid vtkViews
)

add_executable(waledac ${waledac_botnet_src} ${waledac_botnet_vtk_src})
target_link_libraries(waledac ${waledac_botnet_libraries} ${waledac_botnet_vtk_libraries})

