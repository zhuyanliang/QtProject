#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QLabel;
class Spreadsheet;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void connectActions();
    void createStatusBar();
    bool okToContinus();
    bool loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);

    void setCurrentFile(const QString &fullFileName);
    QString strippedName(const QString &fullFileName);

    void readSettings();
    void writeSettings();

    void createRecentFileActions();
    void createRecentFileMenus();

    void updateRecentFileActions();

protected:
    void closeEvent(QCloseEvent *);//所有的关闭时间都会调用它

private slots:
    void about();
    void open();
    bool save();
    bool saveAs();
    void openRecentFile();
    void newFile();
    void gotoCell();

private:
    Ui::MainWindow *ui;
    Spreadsheet *spreadsheet;

    QLabel *locationLabel;
    QLabel *formulaLabel;

    QString curFile;

    enum{MaxRecentFiles = 5};
    QAction *recentFileActions[MaxRecentFiles];
    QAction *separatorAction;

    QStringList recentFiles;
};

#endif // MAINWINDOW_H
