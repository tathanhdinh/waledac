#ifndef VTKTIMERCALLBACK_H
#define VTKTIMERCALLBACK_H

#include <vtkSmartPointer.h>
#include <vtkCommand.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkTesting.h>

class vtkBotnetGraph;
 
class vtkTimerCallback : public vtkCommand
{
  public:
    vtkTimerCallback(vtkBotnetGraph *ptrbotnetgraph);
 	~vtkTimerCallback();
 	
    virtual void Execute(vtkObject *vtkNotUsed(caller), unsigned long eventId, void *vtkNotUsed(callData));
 
    int TimerCount;
    vtkBotnetGraph *ptrbotnetgraph;
    
    bool first_time;
 
};
 
#endif


