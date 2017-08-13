#include <QtWidgets>

#include "mainwindow.h"

#include <QAction>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>
#include <QFileDialog>
#include <QLabel>
#include <QSettings>

#include <QCoreApplication>
#include <QApplication>

#include <QRect>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    setWindowTitle(tr("Main Window"));


    ImgLabel = new QLabel();
    setCentralWidget(ImgLabel);

    statusBar() ;

    createActions();
    createMenus();
    createToolBars();
    readSettings();

}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{

    openAction = new QAction(QIcon(":/images/doc-open"), tr("&Open..."), this);
    openAction->setShortcuts(QKeySequence::Open);
    openAction->setStatusTip(tr("Open an existing file"));

    connect(openAction, &QAction::triggered, this, &MainWindow::open);

    QToolBar *toolBar = addToolBar(tr("&File"));
    toolBar->addAction(openAction);

    //”打印图像“动作
    //PrintTextAction =new QAction(QIcon("printimage.png"),"print image",this);
    //PrintTextAction->setStatusTip("print a Image");

    //”放大“动作
    zoomInAction =new QAction(QIcon("zoomin.png"),tr("zoomin"),this);
    zoomInAction->setStatusTip(tr("zoomin pic"));

    //”缩小“动作
    zoomOutAction =new QAction(QIcon("zoomout.png"),tr("zoomout"),this);
    zoomOutAction->setStatusTip(tr("zoomout pic"));

    //实现图像旋转的动作
    //旋转90
    rotate90Action =new QAction(QIcon("rotate90.png"),tr("rotate 90"),this);
    rotate90Action->setStatusTip(tr("make image rotation 90"));

    //旋转180
    rotate180Action =new QAction(QIcon("rotate180.png"),tr("rotate 180"),this);
    rotate180Action->setStatusTip(tr("make image rotation 180"));

    //旋转270
    rotate270Action =new QAction(QIcon("rotate270.png"),tr("rotate 270"),this);
    rotate270Action->setStatusTip(tr("make image rotation 270"));

    //实现镜像的动作
    //纵向镜像
    mirrorVerticalAction =new QAction(QIcon("mirrovertical.png"),tr("mirror vertical"),this);
    mirrorVerticalAction->setStatusTip(tr("make image mirror vertical"));

    //横向镜像
    mirrorHorizontalAction =new QAction(QIcon("mirrorHorizontal.png"),tr("mirror horizontal"),this);
    mirrorHorizontalAction->setStatusTip(tr("make img mirror horizontal"));


}

void MainWindow::createMenus()
{
    //文件菜单
    fileMenu =menuBar()->addMenu(tr("File"));
    fileMenu->addAction(openAction);


    //缩放菜单
    zoomMenu =menuBar()->addMenu("Edit");

    zoomMenu->addAction(zoomInAction);
    zoomMenu->addAction(zoomOutAction);

    //旋转菜单
    rotateMenu =menuBar()->addMenu("rotate");
    rotateMenu->addAction(rotate90Action);
    rotateMenu->addAction(rotate180Action);
    rotateMenu->addAction(rotate270Action);

    //镜像菜单
    mirrorMenu =menuBar()->addMenu(tr("Mirror"));
    mirrorMenu->addAction(mirrorVerticalAction);
    mirrorMenu->addAction(mirrorHorizontalAction);

}

void MainWindow::createToolBars()
{
    //文件工具条
//    fileTool =addToolBar("File");

//    fileTool->addAction(PrintTextAction);


    //编辑工具条
    zoomTool =addToolBar("Edit");

    zoomTool->addAction(zoomInAction);
    zoomTool->addAction(zoomOutAction);

    //旋转工具条
    rotateTool =addToolBar("rotate");
    rotateTool->addAction(rotate90Action);
    rotateTool->addAction(rotate180Action);
    rotateTool->addAction(rotate270Action);


}


void MainWindow::open()
{
    int width_d=100;
    int height_d=100;
    float scale_w=1.0;
    float scale_h=1.0;

    QMessageBox::information(this, tr("Information"), tr("Open"));
    filename = QFileDialog::getOpenFileName(this,
                                          tr("Open Image File"), ".",
                                          tr("Image Files (*.jpg *.png *.bmp *.jpeg *.tiff *.tif *.dib *.jp2 *.jpe *.ppm *.pgm *.pbm *.ras *.sr)"));
    if (!filename.isEmpty()){

        // now load the image
        image = imread(filename.toStdString(), CV_LOAD_IMAGE_COLOR);   // Read the file

        if(! image.data )                              // Check for invalid input
        {
            QMessageBox msgBox;
            msgBox.setText("The selected image could not be opened!");
            msgBox.show();
            msgBox.exec();
        }
        else // If image file is fine. Show it in the label pixmap
        {
            QImage qigm=MatToQImage(image);

            if (qigm.width()<= ImgLabel->size().width())
            {
                if(qigm.height()<= ImgLabel->size().height()){
                    width_d=qigm.width();
                    height_d=qigm.height();
                }
                else{
                    width_d= int(qigm.width()*(ImgLabel->size().height()/float(qigm.height())));
                    height_d=ImgLabel->size().height();
                }
            }
            else
            {
                if(qigm.height()< ImgLabel->size().height()){
                    width_d=ImgLabel->size().width();
                    height_d=int(qigm.height() * (width_d / float(qigm.width())));
                }
                else{
                    scale_h= ImgLabel->size().height()/float(qigm.height());
                    scale_w= ImgLabel->size().width()/float(qigm.width());

                    if(scale_h<=scale_w){
                        width_d= int(qigm.width()*scale_h);
                        height_d=int(qigm.height()*scale_h);
                    }
                    else{
                        width_d= int(qigm.width()*scale_w);
                        height_d=int(qigm.height()*scale_w);
                    }
                }

            }

            ImgLabel->setPixmap(QPixmap::fromImage(qigm).scaled(width_d,height_d,Qt::IgnoreAspectRatio,Qt::FastTransformation));
        }
    }
}

QImage MainWindow::MatToQImage(const Mat& mat)
{
// 8-bits unsigned, NO. OF CHANNELS=1
if(mat.type()==CV_8UC1)
{
    // Set the color table (used to translate colour indexes to qRgb values)
    QVector<QRgb> colorTable;
    for (int i=0; i<256; i++)
        colorTable.push_back(qRgb(i,i,i));
    // Copy input Mat
    const uchar *qImageBuffer = (const uchar*)mat.data;
    // Create QImage with same dimensions as input Mat
    QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_Indexed8);
    img.setColorTable(colorTable);
    return img;
}
// 8-bits unsigned, NO. OF CHANNELS=3
else if(mat.type()==CV_8UC3)
{
    // Copy input Mat
    const uchar *qImageBuffer = (const uchar*)mat.data;

    // Create QImage with same dimensions as input Mat
    QImage img(qImageBuffer, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
    return img.rgbSwapped();
}
else
{
    //qDebug() << "ERROR: Mat could not be converted to QImage.";
    return QImage();
}
}


void MainWindow::readSettings()
{
    QSettings settings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = settings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = QApplication::desktop()->availableGeometry(this);
        resize(availableGeometry.width() / 2, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}


