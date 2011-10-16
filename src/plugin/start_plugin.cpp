#include "start_plugin.h"
#include "QMessageBox"
int StartPlugin::Init(ShellInterface * shell){
    ShellInterface* f_shell = shell;
        QToolBar* main_toolbar = f_shell->GetPluginsToolBar();

        if(main_toolbar != NULL){
            action_hello = new QAction(tr("Hello world!"), this);
            action_hello->setShortcut(tr("Ctrl+H"));
            action_hello->setStatusTip(tr("Hello world!"));
            connect(action_hello, SIGNAL(triggered()), this, SLOT(Hello()));

            main_toolbar->addAction(action_hello);
        }else{
            QMessageBox message;
            message.setText("Error! Toolbar didn't loaded!");
            message.exec();
        }
    return 0;
}
int StartPlugin::Stop(){
    return 0;
}
void StartPlugin::Hello()
{
    QMessageBox message;
    message.setText("Hello, World! I'm plugin!");
    message.exec();
}

Q_EXPORT_PLUGIN2(gis_hello, StartPlugin)
