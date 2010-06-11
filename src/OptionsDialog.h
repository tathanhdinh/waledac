#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QtGui>
//#include "QVTKBotnetWidget.h"



class OptionsDialog : public QDialog
{
	Q_OBJECT

	public:
		OptionsDialog(QWidget *parent);
		~OptionsDialog();
		
		//QVTKBotnetWidget *parent;
		QSpinBox *timerbox;	
};

#endif		
