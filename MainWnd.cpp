#include "MainWnd.h"
#include <QtWidgets>
#include <QFileDialog>
#include <QStatusBar>
#include <QPainter>
#include "PrimitiveFigure.h"
#include "CentralWidget.h"

#include "Picture.h"
#include "Point.h"
#include "Line.h"



MainWnd::MainWnd(QWidget *parent)
    : QMainWindow(parent)
{   
    picture = std::make_unique<Picture>();
    

    cntWidget = new CentralWidget(*picture);
    setCentralWidget(cntWidget);
    createMenu();
    createActions();
    createStatusBar();
    createToolBars();    

    connect(m_lineAct, SIGNAL(triggered(bool)), this, SLOT(line(bool)));
    connect(m_pointAct, SIGNAL(triggered(bool)), this, SLOT(point(bool)));
    connect(m_circleAct, SIGNAL(triggered(bool)), this, SLOT(circle(bool)));
    connect(m_SquareAct, SIGNAL(triggered(bool)), this, SLOT(square(bool)));
    connect(m_polyLineAct, SIGNAL(triggered(bool)), this, SLOT(polyline(bool)));
    connect(m_ellipseAct, SIGNAL(triggered(bool)), this, SLOT(ellipse(bool)));
    connect(m_triangleAct, SIGNAL(triggered(bool)), this, SLOT(triangle(bool)));
    connect(m_touchAct, SIGNAL(triggered(bool)), cntWidget, SLOT(ObjectPresentTouch(bool)));
    connect(m_movingAct, SIGNAL(triggered(bool)), cntWidget, SLOT(moving()));
    connect(m_rotateAct, SIGNAL(triggered(bool)), cntWidget, SLOT(ObjectPresentRotate(bool)));

}

MainWnd::~MainWnd()
{}
    

//Панель Меню
void MainWnd::createMenu() {
    QIcon imageOpen(":/images/open.jpg");
    QIcon imageSave(":/images/save.png");
    QIcon imageCopy(":/images/copy.png");
    QIcon imageCut(":/images/cut.png");


    QMenu* fileMenu = menuBar()->addMenu(tr("&Файл"));
    m_OpenAct = fileMenu->addAction(imageOpen, tr("&Открыть..."), this, &MainWnd::open);
    m_OpenAct->setShortcut(QKeySequence::Open);
    connect(m_OpenAct, SIGNAL(changed()), this, SLOT(open()));
    m_saveAsAct = fileMenu->addAction(imageSave, tr("Сохранить &как..."), this, &MainWnd::saveAs);
    // Комбинация клавиш задается явным указанием
    m_saveAsAct->setShortcut(Qt::CTRL | Qt::SHIFT | Qt::Key_S);
    // Состояние действия: запрещено
    m_saveAsAct->setEnabled(false);


    QMenu* ToolMenu = menuBar()->addMenu(tr("&Операции"));
    m_copyAct = ToolMenu->addAction(imageCopy, tr("&Копировать"), this, &MainWnd::copy);
    m_copyAct->setShortcut(QKeySequence::Copy);
    m_pasteAct = ToolMenu->addAction(imageCopy, tr("&Вставить"), this, &MainWnd::insert);
    m_pasteAct->setShortcut(QKeySequence::Paste);
    m_cutAct = ToolMenu->addAction(imageCut, tr("&Вырезать"), this, &MainWnd::cut);
}


void MainWnd::mouseMoveEvent(QMouseEvent* event)
{  

    viewCoordsInStatusBar(event->position());
    
}

void MainWnd::keyPressEvent(QKeyEvent* event)
{
    cntWidget->keyPressEvent(event);
}



//Строка состояния
void MainWnd::createStatusBar()
{
    statusBar()->showMessage(tr("Тестовое сообщение на русском языке"));
}

/// <summary>
/// Создание панелей инструментов
/// </summary>

//    В классе главного окна перегрузите обработчик перемещения мыши (по умолчанию он вызывается при нажатой левой кнопке) 
//    и выполните в нем отображение координат указателя мыши в строке состояния (например, в формате (X, Y)). 
void MainWnd::viewCoordsInStatusBar( QPointF mousePos )
{
    QPointF pnt = cntWidget->mapFromParent(mousePos);
    if (pnt.y() < 0 || pnt.x() < 0)
    {
        statusBar()->showMessage(tr("Тестовое сообщение на русском языке"));
    }
    else
    {
        const QString message = tr("X %1, Y %2").arg(pnt.x()).arg(pnt.y());
        statusBar()->showMessage(message);
    }
}

void MainWnd::createToolBars()
{
    m_figureToolBar = addToolBar(tr("Выбор фигур"));
    m_figureToolBar->addAction(m_lineAct);
    m_figureToolBar->addAction(m_pointAct);
    m_figureToolBar->addAction(m_SquareAct);
    m_figureToolBar->addAction(m_polyLineAct);
    m_figureToolBar->addAction(m_ellipseAct);
    m_figureToolBar->addAction(m_circleAct);
    m_figureToolBar->addAction(m_triangleAct);
    m_figureToolBar->addAction(m_touchAct);
    m_figureToolBar->addAction(m_movingAct);
    m_figureToolBar->addAction(m_rotateAct);
    
    m_mainToolBar = addToolBar(tr("Основные операции"));
    m_mainToolBar->addAction(m_cutAct);
    m_mainToolBar->addAction(m_copyAct);
}

//Слот для открытия файла
void MainWnd::open()
{
    // Инициализация диалогового окна открытия файла
    QStringList filenames = QFileDialog::getOpenFileNames(
        this,
        tr("Open txt file"),
        QDir::currentPath(),
        tr("txt (*.txt);;All files (*.*)"));
}

//Слот для сохранения файла
void MainWnd::saveAs()
{
    QString filename = QFileDialog::getSaveFileName(
        this,
        tr("Save Image"),
        QDir::currentPath(),
        tr("Image (*.jpeg)"));
}

//Слот для копирования
void MainWnd::copy()
{
    cntWidget->CopyFig();
}

void MainWnd::insert()
{
    cntWidget->InsertFig();
}

//Слот для вырезки
void MainWnd::cut()
{

}

/// <summary>
/// Создание группы действий и задание им изображений
/// </summary>
void MainWnd::createActions()
{
    QMenu* figureMenu = menuBar()->addMenu(tr("&Фигуры"));

    const QIcon lineIcon("/images/line.png");
    m_lineAct = figureMenu->addAction(lineIcon, tr("&Линия..."), this, &MainWnd::line);
    m_lineAct->setCheckable(true);
    

    const QIcon pointIcon(":/images/point.png");
    m_pointAct = figureMenu->addAction(pointIcon, tr("&Точка..."), this, &MainWnd::point);
    m_pointAct->setCheckable(true);
    

    const QIcon squareIcon(":/images/rectangle.png");
    m_SquareAct = figureMenu->addAction(squareIcon, tr("&Квадрат..."), this, &MainWnd::square);
    m_SquareAct->setCheckable(true);
    

    const QIcon polylineIcon(":/images/polyline.png");
    m_polyLineAct = figureMenu->addAction(polylineIcon, tr("&Ломанная..."), this, &MainWnd::polyline);
    m_polyLineAct->setCheckable(true);
    

    const QIcon ellipseIcon(":/images/ellipse.png");
    m_ellipseAct = figureMenu->addAction(ellipseIcon, tr("&Эллипс..."), this, &MainWnd::ellipse);
    m_ellipseAct->setCheckable(true);
   

    const QIcon circleIcon(":/images/circle.jpg");
    m_circleAct = figureMenu->addAction(circleIcon, tr("&Окружность..."), this, &MainWnd::circle);
    m_circleAct->setCheckable(true);
    

    const QIcon triangleIcon(":/images/triangle.png");
    m_triangleAct = figureMenu->addAction(triangleIcon, tr("&Треугольник..."), this, &MainWnd::triangle);
    m_triangleAct->setCheckable(true);

    const QIcon touchIcon(":/images/touch.jpg");
    m_touchAct = figureMenu->addAction(touchIcon, tr("&Выделение..."));
    m_touchAct->setCheckable(true);

    const QIcon movingIcon(":/images/moving.png");
    m_movingAct = figureMenu->addAction(movingIcon, tr("&Перемещение..."));
    m_movingAct->setCheckable(true);
    
    const QIcon rotateIcon(":/images/rotate.png");
    m_rotateAct = figureMenu->addAction(rotateIcon, tr("&Поворот..."));
    m_rotateAct->setCheckable(true);

    QActionGroup* menuActionGroup = new QActionGroup(this);
    menuActionGroup->setExclusive(true);
    menuActionGroup->addAction(m_lineAct);
    menuActionGroup->addAction(m_pointAct);
    menuActionGroup->addAction(m_SquareAct);
    menuActionGroup->addAction(m_polyLineAct);
    menuActionGroup->addAction(m_ellipseAct);
    menuActionGroup->addAction(m_circleAct);
    menuActionGroup->addAction(m_triangleAct);
    menuActionGroup->addAction(m_touchAct);
    menuActionGroup->addAction(m_movingAct);
    menuActionGroup->addAction(m_rotateAct);
}

/// <summary>
/// Слот для выбора фигуры отрезок
/// </summary>
void MainWnd::line (bool status)
{
    if (status)
    {
        cntWidget->b_draw = true;
        cntWidget->b_touch = false;
        cntWidget->b_rotate = false;
        int t = static_cast<int>(FigureType::Line);
        cntWidget->setFigure(t);
    }
    
    
}

/// <summary>
/// Слот для выбора фигуры точка
/// </summary>
void MainWnd::point(bool status)
{
    if (status)
    {
        cntWidget->b_draw = true;
        cntWidget->b_touch = false;
        cntWidget->b_rotate = false;
        int t = static_cast<int>(FigureType::Point);
        cntWidget->setFigure(t);    
    }
    
}

/// <summary>
/// Слот для выбора фигуры квадрат
/// </summary>
void MainWnd::square(bool status)
{
    if (status)
    {
        cntWidget->b_draw = true;
        cntWidget->b_touch = false;
        cntWidget->b_rotate = false;
        int t = static_cast<int>(FigureType::Square);
        cntWidget->setFigure(t);
        
    }
    
}

/// <summary>
/// Слот для выбора фигуры кривая
/// </summary>
void MainWnd::polyline(bool status)
{
    if (status)
    {
        cntWidget->b_draw = true;
        cntWidget->b_touch = false;
        cntWidget->b_rotate = false;
        int t = static_cast<int>(FigureType::Polyline);
        cntWidget->setFigure(t);
        
    }
    
}

/// <summary>
/// Слот для выбора фигуры эллипс
/// </summary>
void MainWnd::ellipse(bool status)
{
    if (status)
    {
        cntWidget->b_draw = true;
        cntWidget->b_touch = false;
        cntWidget->b_rotate = false;
        int t = static_cast<int>(FigureType::Ellipse);
        cntWidget->setFigure(t);
        
    }
    
}

/// <summary>
/// Слот для выбора фигуры треугольник
/// </summary>
void MainWnd::triangle(bool status)
{
    if (status)
    {
        cntWidget->b_draw = true;
        cntWidget->b_touch = false;
        cntWidget->b_rotate = false;
        int t = static_cast<int>(FigureType::Triangle);
        cntWidget->setFigure(t);
        
    }
    
}



/// <summary>
/// Слот для выбора фигуры окружность
/// </summary>
void MainWnd::circle(bool status)
{
    if (status)
    {
        cntWidget->b_draw = true;
        cntWidget->b_touch = false;
        cntWidget->b_rotate = false;
        int t = static_cast<int>(FigureType::Circle);
        cntWidget->setFigure(t);
       
    }
    
}

