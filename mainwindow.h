#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMainWindow>
#include <QImage>
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QComboBox>
#include <QSpinBox>
#include <QToolBar>
#include <QToolButton>
#include <QTextCharFormat>

#include <opencv2/opencv.hpp>

using namespace cv;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void createActions();
    void createMenus();
    void createToolBars();

    void loadFile(QString filename);
    void mergeFormat(QTextCharFormat);
    Mat image;
    QImage MatToQImage(const Mat& mat);

private:
    void open();
void readSettings();

    QLabel *ImgLabel;
    QString filename;




private:
    QMenu *fileMenu; //各项菜单栏
    QMenu *zoomMenu;
    QMenu *rotateMenu;
    QMenu *mirrorMenu;

    QImage img;
    QString fileName;


//QAction *PrintTextAction;

    QAction *openAction;
    QAction *copyAction;//编辑菜单项
    QAction *cutAction;
    QAction *pasteAction;
    QAction *aboutAction;
    QAction *zoomInAction;
    QAction *zoomOutAction;

    QAction *rotate90Action;//旋转菜单项
    QAction *rotate180Action;
    QAction *rotate270Action;

    QAction *mirrorVerticalAction;//镜像菜单项
    QAction *mirrorHorizontalAction;

    QAction *undoAction;
    QAction *redoAction;

    QToolBar *fileTool;//工具栏
    QToolBar *zoomTool;
    QToolBar *rotateTool;
    QToolBar *mirrorTool;

    QToolBar *doToolBar;



protected slots:



};

#endif // MAINWINDOW_H
