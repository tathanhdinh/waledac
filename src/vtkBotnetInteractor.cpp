#include "vtkBotnetInteractor.h"
#include "vtkBotnetGraph.h"

vtkBotnetInteractor::vtkBotnetInteractor()
{
	this->first_time = true;
}

vtkBotnetInteractor::~vtkBotnetInteractor()
{
}

void vtkBotnetInteractor::setbotnet(vtkBotnetGraph *ptrbotnetgraph)
{
	this->ptrbotnetgraph = ptrbotnetgraph;
}

void vtkBotnetInteractor::OnMouseWheelForward() 
{
	vtkInteractorStyleTrackballCamera::OnMouseWheelForward();
		
	vtkCamera *camera = this->CurrentRenderer->GetActiveCamera();
	if(camera->GetParallelProjection())
		this->zoom_save = camera->GetParallelScale();
}

void vtkBotnetInteractor::OnMouseWheelBackward()
{
	vtkInteractorStyleTrackballCamera::OnMouseWheelBackward();
	
	vtkCamera *camera = this->CurrentRenderer->GetActiveCamera();
	if(camera->GetParallelProjection())
		this->zoom_save = camera->GetParallelScale();
}

int vtkBotnetInteractor::FindBotPosition(int point)
{
	/* sync avec l'ordre dans lequel on insère les points */
	
	if(point == 0)
	{
		printf("command and conquer touché, retourne le premier repéteur pour l'instant\n");
		return this->ptrbotnetgraph->repeaters[0];
	}
	else if(point > 0 && point < this->ptrbotnetgraph->protecters.size())
		return this->ptrbotnetgraph->repeaters[point-1];
		
	else if(point >= this->ptrbotnetgraph->protecters.size() && point < (this->ptrbotnetgraph->protecters.size()+this->ptrbotnetgraph->repeaters.size()))
		return this->ptrbotnetgraph->repeaters[point-this->ptrbotnetgraph->protecters.size()-1];
		
	else if(point >= (this->ptrbotnetgraph->protecters.size()+this->ptrbotnetgraph->repeaters.size()) && point < (this->ptrbotnetgraph->protecters.size()+this->ptrbotnetgraph->repeaters.size()+this->ptrbotnetgraph->spammers.size()))
		return this->ptrbotnetgraph->repeaters[point-this->ptrbotnetgraph->protecters.size()-this->ptrbotnetgraph->repeaters.size()-1];
}

void vtkBotnetInteractor::FindBot(int point)
{
	/* sync avec l'ordre dans lequel on insère les points */
	
	int pos = this->FindBotPosition(point);
	if(point == 0)
	{
		printf("command and conquer touché\n");
	}
	else if(point > 0 && point < this->ptrbotnetgraph->protecters.size())
	{
		printf("protecter touché\n");
	}
	else if(point >= this->ptrbotnetgraph->protecters.size() && point < (this->ptrbotnetgraph->protecters.size()+this->ptrbotnetgraph->repeaters.size()))
	{
		printf("repeater touché\n");
	}
	else if(point >= (this->ptrbotnetgraph->protecters.size()+this->ptrbotnetgraph->repeaters.size()) && point < (this->ptrbotnetgraph->protecters.size()+this->ptrbotnetgraph->repeaters.size()+this->ptrbotnetgraph->spammers.size()))
	{
		printf("spammer touché\n");
	}	
}

void vtkBotnetInteractor::OnLeftButtonDown()
{
	bool click_point = false;
	
	int* clickPos = this->GetInteractor()->GetEventPosition();
	vtkPointPicker* picker = (vtkPointPicker *)this->GetInteractor()->GetPicker();
	picker->Pick(clickPos[0], clickPos[1], 0, this->GetDefaultRenderer());

	double* pos = picker->GetPickPosition();	
	vtkActor* pickedObject = picker->GetActor();
	
	if(pickedObject != NULL)
	{
		printf("get actor fini\n");
		int point = pickedObject->GetMapper()->GetInput()->FindPoint(pos[0],pos[1],pos[2]);
		this->FindBot(point);
		printf("point = %d\n",point);
		
		/*
		printf("find point fini\n");
    	vtkDataArray *arr = pickedObject->GetMapper()->GetInput()->GetPointData()->GetArray("InputPointIds");
		printf("data array fini\n");
		if(arr != NULL && point >= 0 && point < arr->GetNumberOfTuples())
		{
			int ipid = (int)*(arr->GetTuple(point));
			printf("ipid = %d\n",ipid);
     			
			if(ipid >= 0)
     		{
     			printf("actor assoc\n");
     			int a = this->vtkcfg->actors_list[pickedObject];
     			printf("vrai ipid\n");
		 		int vrai_ipid = this->vtkcfg->vertex_symb_list[a][ipid];
		 		printf("node\n");
    			node_t *node = this->vtkcfg->vertex_list[vrai_ipid];
    		
				if(node != NULL)
				{
					printf("vertex\n");
					vertex_t *vertex = (vertex_t *) node->vertex;
    			
					printf("%d === %d === (%d)\n",ipid,vertex->symb,point);
					InfoVertexDialog info_vertex((int)vertex->add, vertex->code, vertex->code_length, vertex->symb);
					info_vertex.exec();
    			
    				click_point = true;
    				return;
				}
			}
		}*/
	}
	
	// forward events
	if(!click_point)
		vtkInteractorStyleTrackballCamera::OnLeftButtonDown();



	vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
	//this->ptrbotnetgraph->botnet->wait();
}

void vtkBotnetInteractor::OnRightButtonDown()
{	
	/* overwrite vtkInteractorStyleTrackballCamera::OnRightButtonDown */
}











