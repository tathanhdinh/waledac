#include "vtkBotnetInteractorStyle.h"
#include "vtkBotnetGraph.h"
#include "vtkActor.h"
#include "vtkMapper.h"
#include "vtkDataSet.h"
#include "vtkPointData.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPointPicker.h"
#include "Bot.h"
#include "InfoVertexDialog.h"

vtkBotnetInteractorStyle::vtkBotnetInteractorStyle(vtkBotnetGraph *ptrbotnetgraph)
{
	this->ptrbotnetgraph = ptrbotnetgraph;
}

vtkBotnetInteractorStyle::~vtkBotnetInteractorStyle()
{
}

/* comment savoir si un Bot est de type Repeater / Spammer ? */
bot_t vtkBotnetInteractorStyle::FindBot(int point)
{
	bot_t null_bot;
	null_bot.reset();
	 
	/* sync avec l'ordre dans lequel on insère les points */
	if(point >= 0 && point < this->ptrbotnetgraph->graph->GetNumberOfVertices())
		return this->ptrbotnetgraph->assoc_vertex_bot[point];
	else
	{
		bot_t null_bot;
		null_bot.reset();
		return null_bot;
	}
}

void vtkBotnetInteractorStyle::FlyToLastClick()
{	
	if(pos == NULL)
		return;
		
	this->ptrbotnetgraph->iren->FlyTo(this->ptrbotnetgraph->ren, this->pos[0],this->pos[1],this->pos[2]);
}

void vtkBotnetInteractorStyle::OnRightButtonDown()
{
	int* clickPos = this->GetInteractor()->GetEventPosition();
	vtkPointPicker* picker = (vtkPointPicker *)this->GetInteractor()->GetPicker();
	picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());

	this->pos = picker->GetPickPosition();	
	vtkActor* pickedObject = picker->GetActor();
	
	if(pickedObject != NULL)
	{
		int point = pickedObject->GetMapper()->GetInput()->FindPoint(this->pos[0],this->pos[1],this->pos[2]);
		vtkDataArray *arr = pickedObject->GetMapper()->GetInput()->GetPointData()->GetArray("InputPointIds");
		if(arr != NULL && point >= 0 && point < arr->GetNumberOfTuples())
		{
			int ipid = (int)*(arr->GetTuple(point));
				
			if(ipid >= 0)
     		{
				bot_t bot = this->FindBot(ipid);
				if(bot != NULL)
				{
					int *pw = this->ptrbotnetgraph->win->GetActualSize();
					InfoVertexDialog info_vertex(this->ptrbotnetgraph, bot);
					info_vertex.move(clickPos[0], pw[1]-clickPos[1]);
					info_vertex.exec();
				}
			}
		}
	}

	/* overwrite vtkInteractorStyleTrackballCamera::OnRightButtonDown */
}











