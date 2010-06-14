#ifndef INFOVERTEXDIALOG_H
#define INFOVERTEXDIALOG_H

#include <QtGui>
#include <string>
#include <QCheckBox>
#include <QLineEdit>
#include <QTextEdit>
#include <stdint.h>
class vtkBotnetInteractorStyle;

class InfoVertexDialog : public QDialog
{
	Q_OBJECT

	public :
		InfoVertexDialog(vtkBotnetInteractorStyle *irenstyle);
		~InfoVertexDialog();
		void paintEvent(QPaintEvent * event);
		
		vtkBotnetInteractorStyle *ptrirenstyle;
		
	private slots :
		void click_flyto();
};

#endif	
