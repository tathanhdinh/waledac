#include "vtkBotnetInteractorStyle.h"
#include "vtkBotnetGraph.h"
#include "vtkActor.h"
#include "vtkMapper.h"
#include "vtkDataSet.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkPointPicker.h"
#include "Bot.h"

vtkBotnetInteractorStyle::vtkBotnetInteractorStyle(vtkBotnetGraph *ptrbotnetgraph)
{
	this->first_time = true;
	this->ptrbotnetgraph = ptrbotnetgraph;
}

vtkBotnetInteractorStyle::~vtkBotnetInteractorStyle()
{
}

bot_t vtkBotnetInteractorStyle::FindBot(int point)
{
	bot_t null_bot;
	null_bot.reset();
	 
	/* sync avec l'ordre dans lequel on insère les points */
	/*
	if(point == 0)
	{
		printf("command and conquer touché, retourne le premier protecter pour l'instant\n");
		return this->ptrbotnetgraph->protecters[0];
	}
	else if(point > 0 && point < this->ptrbotnetgraph->protecters.size())
		return this->ptrbotnetgraph->protecters[point-1];
		
	else if(point >= this->ptrbotnetgraph->protecters.size() && point < (this->ptrbotnetgraph->protecters.size()+this->ptrbotnetgraph->repeaters.size()))
		return this->ptrbotnetgraph->repeaters[point-this->ptrbotnetgraph->protecters.size()-1];
		
	else if(point >= (this->ptrbotnetgraph->protecters.size()+this->ptrbotnetgraph->repeaters.size()) && point < (this->ptrbotnetgraph->protecters.size()+this->ptrbotnetgraph->repeaters.size()+this->ptrbotnetgraph->spammers.size()))
		return this->ptrbotnetgraph->spammers[point-this->ptrbotnetgraph->protecters.size()-this->ptrbotnetgraph->repeaters.size()-1];
	else 
		return null_bot;*/
}

void vtkBotnetInteractorStyle::OnRightButtonDown()
{
	int* clickPos = this->GetInteractor()->GetEventPosition();
	vtkPointPicker* picker = (vtkPointPicker *)this->GetInteractor()->GetPicker();
	picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());

	double* pos = picker->GetPickPosition();	
	vtkActor* pickedObject = picker->GetActor();
	
	if(pickedObject != NULL)
	{
		printf("get actor fini\n");
		int point = pickedObject->GetMapper()->GetInput()->FindPoint(pos[0],pos[1],pos[2]);
		bot_t bot = this->FindBot(point);
		printf("point = %d\n",point);
	}

	/* overwrite vtkInteractorStyleTrackballCamera::OnRightButtonDown */
}











