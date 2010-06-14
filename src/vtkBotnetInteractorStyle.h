#ifndef VTKBOTNETINTERACTORSTYLE_H
#define VTKBOTNETINTERACTORSTYLE_H

#include <vtkInteractorStyleTrackballCamera.h>
#include "botnet_types.h"
class vtkBotnetGraph;



class vtkBotnetInteractorStyle : public vtkInteractorStyleTrackballCamera
{
	public:
   		vtkBotnetInteractorStyle(vtkBotnetGraph *ptrbotnetgraph);
   		~vtkBotnetInteractorStyle();
   		
   		void FlyToLastClick();
   		
   	private:	
   		bot_t FindBot(int point);
   		virtual void OnRightButtonDown();
   		vtkBotnetGraph *ptrbotnetgraph;
   		
   		double* pos;
};

#endif



