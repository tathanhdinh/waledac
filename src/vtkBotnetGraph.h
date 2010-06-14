#ifndef VTKBOTNETGRAPH_H
	#define VTKBOTNETGRAPH_H

#include "vtkGraphMapper.h"
#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkGraphToPolyData.h"
#include "vtkPolyDataMapper.h"
#include "vtkTubeFilter.h"
#include "vtkCubeSource.h"
#include "vtkGlyph3D.h"

#include "botnet_types.h"
#include "vtkMutableDirectedGraph.h"
#include "vtkBotnetInteractorStyle.h"
#include <map>
//class Bot;
#include "Botnet.h"

class vtkBotnetGraph
{
	public :
		vtkBotnetGraph(vtkRenderWindowInteractor *iren);
		~vtkBotnetGraph();
		
		void update_graph(bots_t repeaters, bots_t protecters, bots_t spammers, bots_t attackers);
		void set_simulation(waledac::Botnet *botnet);
		void set_interactor(vtkRenderWindowInteractor *iren);
		void start_simulation();
		
		vtkRenderer *ren;
		vtkRenderWindow *win;
		vtkRenderWindowInteractor *iren;
		vtkBotnetInteractorStyle *interactor_style;
		
		vtkMutableDirectedGraph *graph;
		waledac::Botnet *botnet;
		std::map< vtkIdType, bot_t > assoc_vertex_bot;
		
	private :	
		void update_servercc(bot_t servercc);
		void update_attackers(bots_t attackers);
		void update_protecters(bots_t protecters);
		void update_repeaters(bots_t repeaters);
		void update_spammers(bots_t spammers);
		
		void delete_graph();
		void construct_graph();
		void assign_points(bots_t repeaters, bots_t protecters, bots_t spammers, bots_t attackers);
		
		vtkPolyData *polydata_vertex;
		vtkCubeSource *cube_vertex;
		vtkGlyph3D *glyph_vertex;
		vtkPolyDataMapper *mapper_vertex;
		vtkActor *actor_vertex;
		vtkUnsignedCharArray *colors_vertex;
		
		vtkGraphToPolyData *polydata_graph;
		vtkPolyDataMapper *mapper_graph;
		vtkActor *actor_graph;
		vtkTubeFilter *tube_edges;
		vtkUnsignedCharArray *colors_edges;
		
		vtkPoints *graph_points;  

		bool graph_iscreate;
		bool graph_create_first_time;			

		vtkIdType vertex_command_and_conquer;
		std::map< bot_t, vtkIdType > assoc_bot_vertex;
};

#endif
