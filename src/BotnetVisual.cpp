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

#include "BotnetVisual.h"

#include "vtk-5.6/vtkMutableDirectedGraph.h"
#include "vtk-5.6/vtkIntArray.h"
#include "vtk-5.6/vtkLookupTable.h"
#include "vtk-5.6/vtkType.h"
#include "vtk-5.6/vtkTree.h"
#include "vtk-5.6/vtkGraphLayout.h"
#include "vtk-5.6/vtkGraphLayoutView.h"
#include "vtk-5.6/vtkConeLayoutStrategy.h"
#include "vtk-5.6/vtkViewTheme.h"
#include "vtk-5.6/vtkInteractorStyleSwitch.h"
#include "vtk-5.6/vtkDataSetAttributes.h"
#include "vtk-5.6/vtkRenderWindowInteractor.h"

namespace waledac
{

static vtkMutableDirectedGraph *botnet_graph;

static vtkIntArray *vertexColors = 0;
static vtkLookupTable *lookupTable = 0;
static vtkInteractorStyleSwitch *interactor_style = 0;

static vtkIdType servercc_node;
static std::vector<vtkIdType> protecter_nodes;
static std::vector<vtkIdType> repeater_nodes;

BotnetVisual::BotnetVisual(Botnet *botnet)
{
	botnet_graph = vtkMutableDirectedGraph::New();
	
	vertexColors = vtkIntArray::New();
	vertexColors->SetNumberOfValues(1);
	vertexColors->SetName("vertex_colors");
	
	lookupTable = vtkLookupTable::New();
	lookupTable->SetTableRange(0.0, 10.0);
	lookupTable->Build();
	
	// add servercc node
	servercc_node = botnet_graph->AddVertex();
	vertexColors->InsertNextValue(1);
	
	// add protecter nodes
	std::vector< boost::shared_ptr<Bot> > protecters;
	protecters = botnet->protecters_list();
	for (unsigned int i = 0; i < protecters.size(); ++i) {
		//vtkIdType new_protecter_node = botnet_graph->AddVertex();
		//botnet_graph->AddEdge(new_protecter_node);
		
		vtkIdType new_protecter_node = botnet_graph->AddChild(servercc_node);
		protecter_nodes.push_back(new_protecter_node);
		vertexColors->InsertNextValue(3);
	}
	
	// add repeater nodes
	std::vector< boost::shared_ptr<Bot> > repeaters;
	repeaters = botnet->repeaters_list();
	for (unsigned int i = 0; i < repeaters.size(); ++i) {
		vtkIdType new_repeater_node = botnet_graph->AddVertex();
		repeater_nodes.push_back(new_repeater_node);
		
		for (unsigned int j = 0; j < protecter_nodes.size(); ++j) {
			botnet_graph->AddEdge(new_repeater_node, protecter_nodes[i]);
			vertexColors->InsertNextValue(2);
		}
	}
	
	vtkTree *tree = vtkTree::New();
	tree->GetVertexData()->AddArray(vertexColors);
	
	vtkGraphLayout* layout = vtkGraphLayout::New();
	vtkConeLayoutStrategy* strategy = vtkConeLayoutStrategy::New();
	layout->SetInput(tree);
	layout->SetLayoutStrategy(strategy);


	vtkGraphLayoutView* graphLayoutView = vtkGraphLayoutView::New();
	graphLayoutView->AddRepresentationFromInputConnection(layout->GetOutputPort());
	
	graphLayoutView->SetVertexColorArrayName("color");
	graphLayoutView->ColorVerticesOn();
 
	vtkViewTheme *theme = vtkViewTheme::New();
	theme->SetPointLookupTable(lookupTable);
 
	graphLayoutView->ApplyViewTheme(theme);
	graphLayoutView->ResetCamera();
	graphLayoutView->Render();
  
	interactor_style = vtkInteractorStyleSwitch::New();
  
	graphLayoutView->GetInteractor()->SetInteractorStyle(interactor_style);
	graphLayoutView->GetInteractor()->Start();
}

}