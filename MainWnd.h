#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWnd.h"
#include "CentralWidget.h"



class QToolBar;

class MainWnd : public QMainWindow
{
    Q_OBJECT
        
public:
    std::unique_ptr<Picture> picture;



public:
    explicit MainWnd(QWidget *parent = nullptr);
    ~MainWnd();

    CentralWidget* cntWidget{ nullptr };    

    void createToolBars();
    void createActions();

    
    void mouseMoveEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    void createMenu();
    void createStatusBar();
    void viewCoordsInStatusBar(QPointF mousePos);

private slots:
    void open();
    void saveAs();
    void copy();
    void insert();
    void cut();

    void line(bool);
    void point(bool);
    void square(bool);
    void polyline(bool);
    void ellipse(bool);
    void triangle(bool);
    void circle(bool);
 
private:
    Ui::MainWndClass ui;
    // Панель инструментов
    QToolBar* m_mainToolBar{};
    QToolBar* m_viewToolBar{};
    QToolBar* m_figureToolBar{};
    QAction* m_OpenAct{};
    QAction* m_saveAsAct{};
    QAction* m_printAct{};
    QAction* m_cutAct{};
    QAction* m_copyAct{};
    QAction* m_pasteAct{};
    QAction* m_lineAct{};
    QAction* m_pointAct{};
    QAction* m_SquareAct{};
    QAction* m_polyLineAct{};
    QAction* m_ellipseAct{};
    QAction* m_circleAct{};
    QAction* m_triangleAct{};
    QAction* m_touchAct{};
    QAction* m_rotateAct{};
    QAction* m_movingAct{};
};


