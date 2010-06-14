#ifndef VTKTIMERCALLBACK_H
#define VTKTIMERCALLBACK_H

#include "vtkCommand.h"
#include "vtkObject.h"
#include "botnet_types.h"
class vtkBotnetGraph;



namespace waledac
{
	class Botnet;
}
 
class vtkTimerCallback : public vtkCommand
{
	public:
    	vtkTimerCallback(vtkBotnetGraph *ptrbotnetgraph);
 		~vtkTimerCallback();
 	
    	virtual void Execute(vtkObject *vtkNotUsed(caller), unsigned long eventId, void *vtkNotUsed(callData));
 
	private:
    	vtkBotnetGraph *ptrbotnetgraph;
};
 
#endif


