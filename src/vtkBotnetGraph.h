#ifndef VTKBOTNETGRAPH_H
	#define VTKBOTNETGRAPH_H
	
#include <vtkIntArray.h>
#include <vtkLookupTable.h>
#include <vtkMutableUndirectedGraph.h>
#include <vtkGraphLayoutView.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTree.h>
#include <vtkViewTheme.h>
#include <vtkDataSetAttributes.h>
#include <vtkAssignCoordinates.h>
#include <vtkPoints.h>

#include <vtkGraphLayout.h>
#include <vtkCircularLayoutStrategy.h>
#include <vtkSpanTreeLayoutStrategy.h>
#include <vtkAssignCoordinatesLayoutStrategy.h>

#include "vtkBotnetInteractor.h"
#include "Bot.h"
#include <map>
#include <vector>
#include "Botnet.h"

class vtkBotnetGraph
{
	public :
		vtkBotnetGraph(unsigned int rlist_size, unsigned int plist_size, unsigned int spammers_number, unsigned int attackers_number);
		~vtkBotnetGraph();
		
		void update_graph();
		void update_protecters();
		void update_repeaters();
		void update_spammers();
		
		void delete_graph();
		void construct_graph();
		void calc_points(vtkGraphLayout* layout);
		
		vtkTree *tree;
		vtkMutableUndirectedGraph *graph;
		vtkBotnetInteractor *interactor;
		vtkGraphLayoutView *graphLayoutView;
		vtkViewTheme *theme;
		vtkIdType vertex_command_and_conquer;
		vtkGraphLayout* layout;
		//vtkCircularLayoutStrategy* strategy;
		vtkAssignCoordinates *assign;
		vtkAssignCoordinatesLayoutStrategy *assign_coordinates;
		
		vtkIntArray* edgescolors;
		vtkIntArray* vertexcolors;
		vtkLookupTable* lookuptable;
		
		vtkPoints *points;
		
		std::map< boost::shared_ptr< waledac::Bot >, vtkIdType > assoc_spammers; 
		std::map< boost::shared_ptr< waledac::Bot >, vtkIdType > assoc_repeaters;
		std::map< boost::shared_ptr< waledac::Bot >, vtkIdType > assoc_protecters;
		
		waledac::Botnet *botnet;

		bool graph_iscreate;
		bool graph_create_first_time;
		
		std::vector< boost::shared_ptr< waledac::Bot > > repeaters;
		std::vector< boost::shared_ptr< waledac::Bot > > protecters;
		std::vector< boost::shared_ptr< waledac::Bot > > spammers;
		std::vector< boost::shared_ptr< waledac::Bot > > attackers;
};

#endif
