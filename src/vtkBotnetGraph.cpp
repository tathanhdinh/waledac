#include "vtkBotnetGraph.h"

void vtkBotnetGraph::update_graph()
{
	this->repeaters = this->botnet->repeaters_list();
	this->protecters = this->botnet->protecters_list();
	this->spammers = this->botnet->spammers_list();
	this->attackers = this->botnet->attackers_list();
		
	if(this->graph_iscreate)
		delete_graph();
		
	construct_graph();
	
	this->vertex_command_and_conquer = this->graph->AddVertex();
	this->vertexcolors->InsertNextValue(1); // rouge

	update_protecters();
	update_repeaters();
	update_spammers();
	
	this->graph->Modified();
	this->graph->GetVertexData()->AddArray(this->vertexcolors);
	
    vtkGraphLayout* layout = vtkGraphLayout::New();
	vtkCircularLayoutStrategy* strategy = vtkCircularLayoutStrategy::New();
	
	layout->SetInput(this->graph);
	layout->SetLayoutStrategy(strategy);
	
	this->graphLayoutView->AddRepresentationFromInputConnection(layout->GetOutputPort());

}

/*
void vtkBotnetGraph::update_color_repeater(boost::shared_ptr<waledac::Bot> bot)
{
	vtkIdType repeater_vertex = assoc_repeaters[repeater->id()];
	int p = (int) (waledac::Bot::percentage_compromised(repeater->rlist())*100);
	vtkIntArray::SafeDownCast(this->tree->GetVertexData()->GetArray("color"))->SetValue(repeater_vertex, p);
}
*/
void vtkBotnetGraph::update_protecters()
{
	for(unsigned int i = 0; i < this->protecters.size(); i++)
	{
		vtkIdType vertex_protecter = this->graph->AddVertex();
		/* tout les protecteurs sont liés au command and conquer */	
		this->graph->AddEdge(vertex_protecter, this->vertex_command_and_conquer);
		
      	this->assoc_protecters[this->protecters[i]] = vertex_protecter;
      	this->vertexcolors->InsertNextValue(2); // bleu
	}

	printf("FIN UPDATE PROTECTERS\n");
}

void vtkBotnetGraph::update_repeaters()
{
	for(unsigned int j = 0; j < this->repeaters.size(); j++)
	{
		vtkIdType vertex_repeater =  this->graph->AddVertex();
		this->assoc_repeaters[this->repeaters[j]] = vertex_repeater;
		this->vertexcolors->InsertNextValue(4); // vert

		/* les répéteurs sont liés aux protécteurs */
		for(unsigned int k = 0; k < this->repeaters[j].plist().size(); k++)
		{
			this->graph->AddEdge(this->assoc_protecters[this->repeaters[j].plist()[k]], vertex_repeater);
		}
	}

	/* les répéteurs sont liés entre eux */
	for(unsigned int j = 0; j < this->repeaters.size(); j++)
	{
		for(unsigned int k = 0; k < this->repeaters[j].rlist().size(); k++)
		{	
			this->graph->AddEdge(this->assoc_repeaters[this->repeaters[j]], this->assoc_repeaters[this->repeaters[j].rlist()[k]]);
		}
	}
	
	printf("FIN UPDATE REPEATERS\n");
}

void vtkBotnetGraph::update_spammers()
{
	for(unsigned int j = 0; j < this->spammers.size(); j++)
	{
		vtkIdType vertex_spammer =  this->graph->AddVertex();
		this->vertexcolors->InsertNextValue(2);
		this->assoc_spammers[this->spammers[j]] = vertex_spammer;
		
		for(unsigned int k = 0; k < this->spammers[j].rlist().size(); k++)
		{
			this->graph->AddEdge(this->assoc_spammers[this->spammers[j]], this->assoc_spammers[this->spammers[j].rlist[k]]);
		}
	}
	
	printf("FIN UPDATE SPAMMERS\n")	;
}

vtkBotnetGraph::vtkBotnetGraph(waledac::Botnet *botnet)
{
	this->botnet = botnet;
	
	this->interactor = new vtkBotnetInteractor;
	this->graphLayoutView = vtkGraphLayoutView::New();
	
	this->lookuptable = vtkLookupTable::New();
	this->lookuptable->SetTableRange(0.0, 10.0);
	this->lookuptable->Build();
	
	construct_graph();
	
	this->graphLayoutView->ResetCamera();
	this->graphLayoutView->Render();
	this->graphLayoutView->GetInteractor()->Start();
}

void vtkBotnetGraph::delete_graph()
{
	this->graph->Delete();
	this->tree->Delete();
	this->vertexcolors->Delete();
	this->theme->Delete();
	
	this->graph_iscreate = false;
}

void vtkBotnetGraph::construct_graph()
{
	this->vertexcolors = vtkIntArray::New();
	this->vertexcolors->SetNumberOfComponents(1);
 	this->vertexcolors->SetName("color");
	
	this->tree = vtkTree::New();
	this->graph = vtkMutableUndirectedGraph::New();
	
	//this->graphLayoutView->AddRepresentationFromInput(this->graph);
	//this->graphLayoutView->SetLayoutStrategyToCone();
	
	/*****/
	this->graphLayoutView->SetVertexColorArrayName("color");
	this->graphLayoutView->ColorVerticesOn();
 
	this->theme = vtkViewTheme::New();
	this->theme->SetPointLookupTable(this->lookuptable);
	this->graphLayoutView->ApplyViewTheme(this->theme);
	/*****/
 
 	this->interactor->setbotnet(this);
 	this->interactor->SetDefaultRenderer(this->graphLayoutView->GetRenderer());
	this->graphLayoutView->GetInteractor()->SetInteractorStyle(this->interactor);
	
	this->graph_iscreate = true;
}

vtkBotnetGraph::~vtkBotnetGraph()
{
	//Delete();
}














