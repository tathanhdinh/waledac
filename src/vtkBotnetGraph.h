#ifndef VTKBOTNETGRAPH_H
	#define VTKBOTNETGRAPH_H

#include "botnet_types.h"
#include "vtkMutableUndirectedGraph.h"
#include "vtkBotnetInteractorStyle.h"
#include "vtkGraphLayoutView.h"
#include "vtkIntArray.h"
#include <map>
class Bot;

namespace waledac
{
	class Botnet;
}



class vtkBotnetGraph
{
	public :
		vtkBotnetGraph(waledac::Botnet *botnet);
		~vtkBotnetGraph();
		
		void update_graph(bots_t repeaters, bots_t protecters, bots_t spammers, bots_t attackers);
		
		waledac::Botnet *botnet;
		vtkGraphLayoutView *graphLayoutView;
		
	private :	
		void update_attackers(bots_t attackers);
		void update_protecters(bots_t protecters);
		void update_repeaters(bots_t repeaters);
		void update_spammers(bots_t spammers);
		
		void delete_graph();
		void construct_graph();
		void assign_points(bots_t repeaters, bots_t protecters, bots_t spammers, bots_t attackers);
		
		vtkMutableUndirectedGraph *graph;
		vtkBotnetInteractorStyle *interactor_style;
		vtkViewTheme *view_theme;
		vtkIdType vertex_command_and_conquer;
		
		vtkIntArray *colors_edges;
		vtkIntArray *colors_vertex;
		vtkLookupTable *lookup_table;
		
		vtkPoints *graph_points;
		
		std::map< bot_t, vtkIdType > assoc_bot_vertex; 

		bool graph_iscreate;
		bool graph_create_first_time;			
};

#endif
