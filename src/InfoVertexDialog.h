#ifndef INFOVERTEXDIALOG_H
#define INFOVERTEXDIALOG_H

#include <QtGui>
#include <string>
#include <QCheckBox>
#include <QLineEdit>
#include <QTextEdit>
#include <stdint.h>
class vtkBotnetGraph;
#include "Bot.h"
#include "botnet_types.h"

class InfoVertexDialog : public QDialog
{
	Q_OBJECT

	public :
		InfoVertexDialog(vtkBotnetGraph *vtkgraph, bot_t bot);
		~InfoVertexDialog();
		void paintEvent(QPaintEvent * event);
		
		vtkBotnetGraph *ptrbotnetgraph;
		
	private slots :
		void click_flyto();
};

#endif	
