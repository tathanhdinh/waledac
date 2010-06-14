#include "vtkBotnetGraph.h"
#include "vtkPoints.h"
#include "vtkDataSetAttributes.h"
#include "vtkLookupTable.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkViewTheme.h"
#include "vtkPointPicker.h"
#include "vtkTimerCallback.h"

#include "vtkProperty.h"
#include "vtkPointData.h"
#include "vtkCellData.h"

#include "Attacker.h"
#include "Spammer.h"

// DOIT DERIVER DE QVTKBOTNET... ET INTERACTOR DANS QVTK (pas de pointeur)
// class message (il me faut la source et le destinateur si je veux colorer)
//quand click sur noeud : repeater/spammer statistiques rlist a nous a 50%
// regler la vitesse (sleep())

void vtkBotnetGraph::assign_points(bots_t repeaters, bots_t protecters, bots_t spammers, bots_t attackers)
{
	/* command and conquer */
	this->graph_points->InsertNextPoint(250+rand()%250, rand()%500, 100);
	
	unsigned int i;
	
	for(i = 0; i < protecters.size(); i++)
	{
		this->graph_points->InsertNextPoint(rand()%500, rand()%500, 200);
	}
	
	for(i = 0; i < repeaters.size(); i++)
	{
		this->graph_points->InsertNextPoint(rand()%500, rand()%500, 400);
	}
	
	for(i = 0; i < attackers.size(); i++)
	{
		this->graph_points->InsertNextPoint(500+rand()%200, 500+rand()%200, 200);
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
	
	update_servercc(this->botnet->server());	
	update_protecters(protecters);
	update_repeaters(repeaters);
	update_attackers(attackers); // après les répéteurs et les protecteurs
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
	
	this->polydata_graph->SetInput(this->graph);
	
	this->tube_edges->SetInput(polydata_graph->GetOutput());
	
  	this->mapper_graph->SetInput(this->tube_edges->GetOutput());
  	
	this->actor_graph->SetMapper(this->mapper_graph);
	
	
	this->polydata_vertex->SetPoints(this->graph_points);
  	this->polydata_vertex->GetPointData()->SetScalars(this->colors_vertex);
  	
  	this->glyph_vertex->GeneratePointIdsOn();
	this->glyph_vertex->SetSource(this->cube_vertex->GetOutput());
  	this->glyph_vertex->SetInput(this->polydata_vertex);
 
	this->mapper_vertex->SetInputConnection(this->glyph_vertex->GetOutputPort());
  	this->actor_vertex->SetMapper(this->mapper_vertex);

	this->win->Render();
}

	
void vtkBotnetGraph::update_servercc(bot_t servercc)
{
	this->vertex_command_and_conquer = this->graph->AddVertex();
	this->colors_vertex->InsertNextTuple3(255, 0, 0); // rouge
	
	this->assoc_bot_vertex[servercc] = vertex_command_and_conquer;
	this->assoc_vertex_bot[vertex_command_and_conquer] = this->botnet->server();
}
	
void vtkBotnetGraph::update_attackers(bots_t attackers)
{
	waledac::Attacker *attacker;
	vtkIdType vertex_attacker;

	for(unsigned int j = 0; j < attackers.size(); j++)
	{
		printf("attaquer %d\n",j);
		vertex_attacker =  this->graph->AddVertex();
		this->colors_vertex->InsertNextTuple3(0, 255, 0); // green
		this->assoc_bot_vertex[attackers[j]] = vertex_attacker;
		this->assoc_vertex_bot[vertex_attacker] = attackers[j];
		attacker = dynamic_cast<waledac::Attacker*>(attackers[j].get());
		
		/* les attaquants sont liés aux protécteurs */	
		for(unsigned int k = 0; k < attacker->plist().size(); k++)
		{
			printf("attaquer fleche vers protecteur\n");
			this->graph->AddEdge(this->assoc_bot_vertex[attacker->plist()[k]], vertex_attacker);
			this->colors_edges->InsertNextTuple3(0, 255, 0); // green
		}
	}

	// les attaquants sont liés entre eux 
	for(unsigned int j = 0; j < attackers.size(); j++)
	{
		attacker = dynamic_cast<waledac::Attacker*>(attackers[j].get());
		vertex_attacker = this->assoc_bot_vertex[attackers[j]];
	
		for(unsigned int k = 0; k < attacker->rlist().size(); k++)
		{	
			printf("attaquer fleche vers autre attaquant\n");
			this->graph->AddEdge(vertex_attacker, this->assoc_bot_vertex[attacker->rlist()[k]]);
			this->colors_edges->InsertNextTuple3(0, 255, 0); // green
		}
	}
	
	printf("FIN UPDATE\n\n\n\n\n");
}

void vtkBotnetGraph::update_protecters(bots_t protecters)
{
	vtkIdType vertex_protecter;
	
	for(unsigned int i = 0; i < protecters.size(); i++)
	{
		vertex_protecter = this->graph->AddVertex();
		/* tout les protecteurs sont liés au command and conquer */	
		this->graph->AddEdge(vertex_protecter, this->vertex_command_and_conquer);
		this->assoc_bot_vertex[protecters[i]] = vertex_protecter;
		this->assoc_vertex_bot[vertex_protecter] = protecters[i];
      	this->colors_edges->InsertNextTuple3(255, 140, 0); // dark orange
      	this->colors_vertex->InsertNextTuple3(255, 140, 0); // dark orange
	}
}

void vtkBotnetGraph::update_repeaters(bots_t repeaters)
{
	waledac::Repeater *repeater;
	vtkIdType vertex_repeater;
	
	for(unsigned int j = 0; j < repeaters.size(); j++)
	{
		vertex_repeater =  this->graph->AddVertex();
			
		this->colors_vertex->InsertNextTuple3(238, 203, 173); // peachpuff 2
		this->assoc_bot_vertex[repeaters[j]] = vertex_repeater;
		this->assoc_vertex_bot[vertex_repeater] = repeaters[j];
		repeater = dynamic_cast<waledac::Repeater*>(repeaters[j].get());
		
		/* les répéteurs sont liés aux protécteurs */	
		for(unsigned int k = 0; k < repeater->plist().size(); k++)
		{
			std::cout << "ap plist: " << typeid(repeater->plist()[k].get()).name() << std::endl;

			this->graph->AddEdge(this->assoc_bot_vertex[repeater->plist()[k]], vertex_repeater);
			this->colors_edges->InsertNextTuple3(238, 203, 173); // peachpuff 2
		}
	}

	// les répéteurs sont liés entre eux 
	for(unsigned int j = 0; j < repeaters.size(); j++)
	{
		repeater = dynamic_cast<waledac::Repeater*>(repeaters[j].get());
		vertex_repeater = this->assoc_bot_vertex[repeaters[j]];
		
		for(unsigned int k = 0; k < repeater->rlist().size(); k++)
		{	
			this->graph->AddEdge(vertex_repeater, this->assoc_bot_vertex[repeater->rlist()[k]]);
			this->colors_edges->InsertNextTuple3(139, 90, 43); // tan 4
		}
	}
}

void vtkBotnetGraph::update_spammers(bots_t spammers)
{
	waledac::Spammer *spammer;
	//waledac::Repeater *repeater;
	boost::shared_ptr<waledac::Repeater> repeater;
	
	vtkIdType vertex_spammer;
	
	for(unsigned int j = 0; j < spammers.size(); j++)
	{
		vertex_spammer =  this->graph->AddVertex();
		
		this->assoc_bot_vertex[spammers[j]] = vertex_spammer;
		this->assoc_vertex_bot[vertex_spammer] = spammers[j];
		spammer = dynamic_cast<waledac::Spammer*>(spammers[j].get());
		if(spammer->is_compromised())
			this->colors_vertex->InsertNextTuple3(0, 255, 0); // green
		else
			this->colors_vertex->InsertNextTuple3(238, 203, 173); // peachpuff 2
			
		for(unsigned int k = 0; k < spammer->rlist().size(); k++)
		{
			this->graph->AddEdge(vertex_spammer, this->assoc_bot_vertex[spammer->rlist()[k]]);
			
			//repeater = dynamic_cast<waledac::Repeater *>(spammer->rlist()[k]);
			repeater = boost::dynamic_pointer_cast<waledac::Repeater>(spammer->rlist()[k]);
			if(repeater->is_attacker())
				this->colors_edges->InsertNextTuple3(113, 198, 113); // sgi chartreuse
			else
				this->colors_edges->InsertNextTuple3(0, 255, 0); // green
		}
	}
}
	
void vtkBotnetGraph::set_interactor(vtkRenderWindowInteractor *iren)
{
	this->iren = iren;
}
	
void vtkBotnetGraph::set_simulation(waledac::Botnet *botnet)
{	
	this->botnet = botnet;
}
	
void vtkBotnetGraph::start_simulation()
{	
	this->ren->AddActor(this->actor_graph);
	this->ren->AddActor(this->actor_vertex);
	
	this->botnet->init();	
	this->botnet->start();
	
	this->update_graph(this->botnet->repeaters_list(),this->botnet->protecters_list(),this->botnet->spammers_list(),this->botnet->attackers_list());
	this->ren->ResetCamera();
		
	vtkTimerCallback* cb = new vtkTimerCallback(this);
	this->iren->AddObserver(vtkCommand::TimerEvent, cb);
	this->iren->CreateRepeatingTimer(300);	
}
	
vtkBotnetGraph::vtkBotnetGraph(vtkRenderWindowInteractor *iren)
{	
	this->iren = iren;
	this->graph_create_first_time = true;	

	this->graph_points = vtkPoints::New();
	construct_graph();	
			
	this->polydata_graph = vtkGraphToPolyData::New();
	this->mapper_graph = vtkPolyDataMapper::New();
	this->mapper_graph->ScalarVisibilityOn();
  	this->mapper_graph->SetScalarModeToUseCellFieldData();
	this->mapper_graph->SelectColorArray("coloredges");
	this->actor_graph = vtkActor::New();
	this->tube_edges = vtkTubeFilter::New();
	this->tube_edges->GlobalWarningDisplayOff();
	this->tube_edges->SetRadius(2);
	
	this->polydata_vertex = vtkPolyData::New();
	this->cube_vertex = vtkCubeSource::New();
	this->cube_vertex->SetXLength(15);
	this->cube_vertex->SetYLength(15);
	this->cube_vertex->SetZLength(15);
	
	this->glyph_vertex = vtkGlyph3D::New();
  	this->glyph_vertex->SetColorModeToColorByScalar();
  	this->glyph_vertex->ScalingOff();
  	
  	this->mapper_vertex = vtkPolyDataMapper::New();
	this->actor_vertex = vtkActor::New();
		

	this->win = vtkRenderWindow::New();	
	this->ren = vtkRenderer::New();
	
	this->interactor_style = new vtkBotnetInteractorStyle(this);
	this->interactor_style->SetDefaultRenderer(this->ren);
	
	this->win->AddRenderer(this->ren);
	this->iren->SetInteractorStyle(this->interactor_style);
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
	this->colors_vertex = vtkUnsignedCharArray::New();
	this->colors_vertex->SetNumberOfComponents(3);
 	this->colors_vertex->SetName("colorvertices");
 	
 	this->colors_edges = vtkUnsignedCharArray::New();
	this->colors_edges->SetNumberOfComponents(3);
 	this->colors_edges->SetName("coloredges");
	
	this->graph = vtkMutableDirectedGraph::New();
	
	this->graph_iscreate = true;
}

vtkBotnetGraph::~vtkBotnetGraph()
{
	//Delete();
}














