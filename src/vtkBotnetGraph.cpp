#include "vtkBotnetGraph.h"
#include "vtkPoints.h"
#include "vtkDataSetAttributes.h"
#include "vtkLookupTable.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkViewTheme.h"
#include "vtkPointPicker.h"
#include "vtkTimerCallback.h"
#include "Attacker.h"
#include "Spammer.h"

void vtkBotnetGraph::assign_points(bots_t repeaters, bots_t protecters, bots_t spammers, bots_t attackers)
{
	/* command and conquer */
	this->graph_points->InsertNextPoint(rand()%500, rand()%500, 100);
	
	unsigned int i;
	/*for(i = 0; i < this->attackers.size(); i++)
	{
		this->points->InsertNextPoint(500+rand()%200, 500+rand()%200, 200);
	}*/
	
	for(i = 0; i < protecters.size(); i++)
	{
		this->graph_points->InsertNextPoint(rand()%500, rand()%500, 200);
	}
	
	for(i = 0; i < repeaters.size(); i++)
	{
		this->graph_points->InsertNextPoint(rand()%500, rand()%500, 400);
	}
	
	for(i = 0; i < spammers.size(); i++)
	{
		this->graph_points->InsertNextPoint(rand()%500, rand()%500, 600);
	}	
}

void vtkBotnetGraph::update_graph(bots_t repeaters, bots_t protecters, bots_t spammers, bots_t attackers)
{	
	if(this->graph_iscreate)
		delete_graph();
		
	construct_graph();
	
	this->vertex_command_and_conquer = this->graph->AddVertex();
	this->colors_vertex->InsertNextValue(1); // rouge
	
	update_attackers(attackers);
	update_protecters(protecters);
	update_repeaters(repeaters);
	update_spammers(spammers);
	
	this->graph->Modified();
	this->graph->GetVertexData()->AddArray(this->colors_vertex);
	this->graph->GetEdgeData()->AddArray(this->colors_edges);
	
	if(this->graph_create_first_time)
	{
		this->graph_create_first_time = false;
		assign_points(repeaters, protecters, spammers, attackers);
	}
	
	this->graph->SetPoints(this->graph_points);
	this->graphLayoutView->AddRepresentationFromInput(this->graph);
	this->graphLayoutView->SetLayoutStrategyToPassThrough();
}

void vtkBotnetGraph::update_attackers(bots_t attackers)
{
	waledac::Attacker *attacker;
	/*
	for(unsigned int j = 0; j < this->attackers.size(); j++)
	{
		vtkIdType vertex_attacker =  this->graph->AddVertex();
		this->vertexcolors->InsertNextValue(6); // vert
		this->assoc_bot_vertex[this->attackers[j]] = vertex_attacker;
		attacker = dynamic_cast<waledac::Attacker*>(this->attackers[j].get());
		
		// les répéteurs sont liés aux protécteurs 	
		for(unsigned int k = 0; k < attacker->plist().size(); k++)
		{
			this->graph->AddEdge(this->assoc_bot_vertex[attacker->plist()[k]], vertex_attacker);
			this->edgescolors->InsertNextValue(4);
		}
	}

	// les répéteurs sont liés entre eux 
	for(unsigned int j = 0; j < this->attackers.size(); j++)
	{
		attacker = dynamic_cast<waledac::Attacker*>(this->attackers[j].get());
		//std::vector< boost::shared_ptr<waledac::Bot> > repeater_rlist = repeater->rlist();
	
		for(unsigned int k = 0; k < attacker->rlist().size(); k++)
		{	
			this->graph->AddEdge(this->assoc_bot_vertex[this->attackers[j]], this->assoc_bot_vertex[attacker->rlist()[k]]);
			this->edgescolors->InsertNextValue(4);
		}
	}*/
}

void vtkBotnetGraph::update_protecters(bots_t protecters)
{
	for(unsigned int i = 0; i < protecters.size(); i++)
	{
		vtkIdType vertex_protecter = this->graph->AddVertex();
		/* tout les protecteurs sont liés au command and conquer */	
		this->graph->AddEdge(vertex_protecter, this->vertex_command_and_conquer);
		this->assoc_bot_vertex[protecters[i]] = vertex_protecter;
      	this->colors_edges->InsertNextValue(2);
      	this->colors_vertex->InsertNextValue(2);
	}
}

void vtkBotnetGraph::update_repeaters(bots_t repeaters)
{
	waledac::Repeater *repeater;
	
	for(unsigned int j = 0; j < repeaters.size(); j++)
	{
		vtkIdType vertex_repeater =  this->graph->AddVertex();
		this->colors_vertex->InsertNextValue(3); // vert
		this->assoc_bot_vertex[repeaters[j]] = vertex_repeater;
		repeater = dynamic_cast<waledac::Repeater*>(repeaters[j].get());
		
		/* les répéteurs sont liés aux protécteurs */	
		for(unsigned int k = 0; k < repeater->plist().size(); k++)
		{
			this->graph->AddEdge(this->assoc_bot_vertex[repeater->plist()[k]], vertex_repeater);
			this->colors_edges->InsertNextValue(3);
		}
	}

	// les répéteurs sont liés entre eux 
	for(unsigned int j = 0; j < repeaters.size(); j++)
	{
		repeater = dynamic_cast<waledac::Repeater*>(repeaters[j].get());
		//std::vector< boost::shared_ptr<waledac::Bot> > repeater_rlist = repeater->rlist();
	
		for(unsigned int k = 0; k < repeater->rlist().size(); k++)
		{	
			this->graph->AddEdge(this->assoc_bot_vertex[repeaters[j]], this->assoc_bot_vertex[repeater->rlist()[k]]);
			this->colors_edges->InsertNextValue(3);
		}
	}
}

void vtkBotnetGraph::update_spammers(bots_t spammers)
{
	for(unsigned int j = 0; j < spammers.size(); j++)
	{
		vtkIdType vertex_spammer =  this->graph->AddVertex();
		this->colors_vertex->InsertNextValue(5);
		this->assoc_bot_vertex[spammers[j]] = vertex_spammer;
		
		waledac::Spammer *spammer = dynamic_cast<waledac::Spammer*>(spammers[j].get());
		
		for(unsigned int k = 0; k < spammer->rlist().size(); k++)
		{
			this->graph->AddEdge(vertex_spammer, this->assoc_bot_vertex[spammer->rlist()[k]]);
			this->colors_edges->InsertNextValue(10);
		}
	}
}

vtkBotnetGraph::vtkBotnetGraph(waledac::Botnet *botnet)
{	
	this->botnet = botnet;
	
	this->graph_create_first_time = true;	
	
	this->interactor_style = new vtkBotnetInteractorStyle(this);
	
	this->lookup_table = vtkLookupTable::New();
	this->lookup_table->SetTableRange(0.0, 10.0);
	this->lookup_table->Build();
	
	this->graph_points = vtkPoints::New();
	
	this->graphLayoutView = vtkGraphLayoutView::New();
	this->graphLayoutView->SetVertexColorArrayName("colorvertices");
	this->graphLayoutView->SetEdgeColorArrayName("coloredges"); 
	this->graphLayoutView->ColorVerticesOn();
	this->graphLayoutView->ColorEdgesOn();
	
	this->graphLayoutView->GetInteractor()->Initialize();

	
	construct_graph();
	
	
	this->view_theme = vtkViewTheme::New();
	this->view_theme->SetPointLookupTable(this->lookup_table);
	this->graphLayoutView->ApplyViewTheme(this->view_theme);
 
 	this->interactor_style->SetDefaultRenderer(this->graphLayoutView->GetRenderer());
	this->graphLayoutView->GetInteractor()->SetInteractorStyle(this->interactor_style);
	
	vtkPointPicker *picker = vtkPointPicker::New();
  	picker->SetTolerance(0.01);
  	this->graphLayoutView->GetInteractor()->SetPicker(picker);
  	

	vtkTimerCallback* cb = new vtkTimerCallback(this);
	this->graphLayoutView->GetInteractor()->AddObserver(vtkCommand::TimerEvent, cb);
	this->graphLayoutView->GetInteractor()->CreateRepeatingTimer(300);
 	
	this->graphLayoutView->ResetCamera();
	this->graphLayoutView->Render();
	this->graphLayoutView->GetInteractor()->Start();	
}


void vtkBotnetGraph::delete_graph()
{
	this->graph->Delete();
	this->colors_vertex->Delete();
	this->colors_edges->Delete();
	
	this->graph_iscreate = false;
}

void vtkBotnetGraph::construct_graph()
{
	this->colors_vertex = vtkIntArray::New();
	this->colors_vertex->SetNumberOfComponents(1);
 	this->colors_vertex->SetName("colorvertices");
 	
 	this->colors_edges = vtkIntArray::New();
	this->colors_edges->SetNumberOfComponents(1);
 	this->colors_edges->SetName("coloredges");
	
	this->graph = vtkMutableUndirectedGraph::New();
	
	this->graph_iscreate = true;
}

vtkBotnetGraph::~vtkBotnetGraph()
{
	//Delete();
}














