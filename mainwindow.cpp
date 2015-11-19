#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <spreadsheet.h>
#include "gotocell_dialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    spreadsheet = new Spreadsheet;

    setCentralWidget(spreadsheet);

    createStatusBar();
    connectActions();

    createRecentFileActions();
    createRecentFileMenus();

    readSettings();
    setCurrentFile("");
}

void MainWindow::createStatusBar()
{
    locationLabel = new QLabel(tr("W999"));
    locationLabel->setAlignment(Qt::AlignHCenter);
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);

    ui->statusBar->addWidget(locationLabel);
    ui->statusBar->addWidget(formulaLabel,1);
}

void MainWindow::connectActions()
{
    connect(ui->actionAbout_Qt,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
    connect(ui->action_About,SIGNAL(triggered()),this,SLOT(about()));
    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(open()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(save()));
    connect(ui->actionSave_As,SIGNAL(triggered()),this,SLOT(saveAs()));
    connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(newFile()));
    connect(ui->action_Go_to_Cell,SIGNAL(triggered()),this,SLOT(gotoCell()));

}

void MainWindow::gotoCell()
{
    GotoCell_Dialog dialog(this);
    if(dialog.exec())
    {
        QString str = dialog.getCellLocation().toUpper();
        spreadsheet->setCurrentCell(str.mid(1).toInt()-1,
                                    str[0].unicode()-'A');
    }
}

void MainWindow::newFile()
{
    if(okToContinus())
    {
        spreadsheet->clear();
        setCurrentFile("");
    }
}

void MainWindow::about()
{
    QMessageBox::about(this,tr("About Spreadsheet"),
                       tr("<h2>Spreadsheet 1.1 </h2>"
                          "<p>Copyright &copy;2008 Software Inc."
                          "<p> Spreadsheet is a small application that"
                          "demostrates QAction,QMainWindow,QMenuBar, "
                          "QStatusBar,QTableWidget,QToolBar, and many other "
                          "Qt classes."));
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(okToContinus())
    {
        writeSettings();
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

void MainWindow::createRecentFileActions()
{
    for(int i=0;i<MaxRecentFiles;++i)
    {
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setText(tr("xxxx"));
        recentFileActions[i]->setVisible(true);
        connect(recentFileActions[i],SIGNAL(triggered()),
                this,SLOT(openRecentFile()));
    }
}

void MainWindow::openRecentFile()
{
    if(okToContinus())
    {
        QAction *action = qobject_cast<QAction *>(sender());
        if(action)
            loadFile(action->data().toString());
    }
}

void MainWindow::createRecentFileMenus()
{
    for(int i=0;i<MaxRecentFiles;++i)
    {
        ui->menuFile->insertAction(ui->actionExit,recentFileActions[i]);
    }
    separatorAction = ui->menuFile->insertSeparator(ui->actionExit);
}

void MainWindow::readSettings()
{
    QSettings settings("Software Zyl","Spreadsheet");
    restoreGeometry(settings.value("geometry").toByteArray());

    recentFiles = settings.value("recentFiles").toStringList();
    updateRecentFileActions();

    bool showGrid = settings.value("showGrid").toBool();
    bool autoRecalc = settings.value("autoRecalc").toBool();
    ui->action_Show_Grid->setChecked(showGrid);
    ui->action_Auto_Recalculate->setChecked(autoRecalc);
}
void MainWindow::writeSettings()
{
    QSettings settings("Software Zyl","Spreadsheet");
    settings.setValue("geometry",saveGeometry());
    settings.setValue("showGrid",ui->action_Show_Grid->isChecked());
    settings.setValue("autoRecalc",ui->action_Auto_Recalculate->isChecked());
    settings.setValue("recentFiles",recentFiles);
}

bool MainWindow::okToContinus()
{
    if(isWindowModified())
    {
        int ret = QMessageBox::warning(this,tr("SpreadSheet"),
                             tr("The document has been modified.\n"
                                "Do you want to save your changes?"),
                             QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel);

        if(ret == QMessageBox::Yes)
        {
            //save();
            return true;
        }
        else if(ret == QMessageBox::Cancel)
        {
            return false;
        }
    }

    return true;
}

void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Spreadsheet"),
                                                    ".",
                                                    tr("Spreadsheet files(*.sp)"));
    if(!fileName.isEmpty())
    {
        loadFile(fileName);
    }
}

bool MainWindow::save()
{
    if(curFile.isEmpty())
    {
        return saveAs();
    }
    else
    {
        return saveFile(curFile);
    }

}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save Spreadsheet"),".",
                                                    tr("Spreadsheet files (*.sp)"));
    if(fileName.isEmpty())
    {
        return false;
    }

    return saveFile(fileName);
}

bool MainWindow::saveFile(const QString &fileName)
{
    if(!spreadsheet->writeFile(fileName))
    {
        statusBar()->showMessage(tr("Saving canceled"),2000);
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("Saving saved"),2000);

    return true;
}

bool MainWindow::loadFile(const QString &fileName)
{
    if(!spreadsheet->readFile(fileName))
    {
        statusBar()->showMessage(tr("Loading canceled"),2000);
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"),2000);

    return true;
}

void MainWindow::setCurrentFile(const QString &fullFileName)
{
    curFile = fullFileName;
    setWindowModified(false);

    QString showName = tr("Untitled");
    if(!curFile.isEmpty())
    {
        showName = strippedName(curFile);
        recentFiles.removeAll(curFile);
        recentFiles.prepend(curFile);
        updateRecentFileActions();
    }
    setWindowTitle(tr("%1[*] - %2").arg(showName).arg(tr("Spreadsheet")));
}

void MainWindow::updateRecentFileActions()
{

    QMutableStringListIterator i(recentFiles);
    while(i.hasNext())
    {
        if(!QFile::exists(i.next()))
            i.remove();
    }
    for(int j=0;j<MaxRecentFiles;++j)
    {
        if(j<recentFiles.count())
        {
            QString text = tr("%1 %2").arg(j+1).arg(strippedName(recentFiles[j]));
            recentFileActions[j]->setText(text);
            recentFileActions[j]->setData(recentFiles[j]);
            recentFileActions[j]->setVisible(true);
        }
        else
        {
            recentFileActions[j]->setVisible(false);
        }
    }
    separatorAction->setVisible(!recentFiles.isEmpty());

}


QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

MainWindow::~MainWindow()
{
    delete ui;
}
