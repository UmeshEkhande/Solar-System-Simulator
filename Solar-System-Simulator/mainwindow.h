#include <QMainWindow>
#include <QGraphicsView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMenuBar>
#include <QStatusBar>
#include <QTimer>
#include <QComboBox>  
#include "SolarSystem.h"
#include "Bezier.h"
#include "Hermite.h"
#include "BSpline3D.h"

class OpenGLWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void setupUi();
    void drawCurveUsingBezier();
    void drawCurveUsingHermite();
    void drawCurveUsingBSpline();
    void clearWindow();

private slots:
    void startBtn();
    void stopBtn();
    void resetBtn();
    void updateBtn();
    void zoomSliderChanged(int value);
    void onSpeedComboBoxIndexChanged(int index);
    void onTabChanged(int tabIndex);

private:
    QMenuBar* mMenubar;
    QStatusBar* mStatusbar;
    QWidget* mCentralwidget;
    QVBoxLayout* mVerticalLayout;
    QGraphicsView* mGraphicsView;
    QHBoxLayout* mHorizontalLayout;

    QPushButton* mStartButton;
    QPushButton* mStopButton;
    QPushButton* mResetButton;
    QPushButton* mUpdateButton;
    QLineEdit* mTimeInput;

    QTimer* mTimer;
    QWidget* mWidget;
    QMenuBar* mMainMenuBar;
    QToolBar* mMainToolBar;
    QWidget* mCentralWidget;
    QStatusBar* mStatusBar;
    
    QComboBox* mSpeedComboBox;
    QSlider* mZoomSlider;
    QGridLayout* mBaseLayout;
    QVBoxLayout* mVbuttonsLayout;
    QHBoxLayout* mButtonsLayout;

    QHBoxLayout* mInputButtonsLayout;
    QVBoxLayout* mVTab2ButtonsLayout;
    QPushButton* mDrawBezierBtn;
    QPushButton* mHermiteBtn;
    QPushButton* mBSplineBtn;
    QPushButton* mClearBtn;

    QVBoxLayout* mVPoint1Layout;
    QLabel* mPoint1;
    QLineEdit* mX1Input;
    QLineEdit* mY1Input;
    QLineEdit* mZ1Input;

    QVBoxLayout* mVPoint2Layout;
    QLabel* mPoint2;
    QLineEdit* mX2Input;
    QLineEdit* mY2Input;
    QLineEdit* mZ2Input;

    QVBoxLayout* mVPoint3Layout;
    QLabel* mPoint3;
    QLineEdit* mX3Input;
    QLineEdit* mY3Input;
    QLineEdit* mZ3Input;

    QVBoxLayout* mVPoint4Layout;
    QLabel* mPoint4;
    QLineEdit* mX4Input;
    QLineEdit* mY4Input;
    QLineEdit* mZ4Input;

    SolarSystem* solar;
    QTabWidget* mTabWidget;
    QWidget* mBezier;

    OpenGLWindow* mRenderer;
    OpenGLWindow* mBezierRenderer;
    OpenGLWindow* mHermiteRenderer;
    OpenGLWindow* mBSpline3DRenderer;

    float xCoordinate;
    float yCoordinate;
    float zCoordinate;
    float x1Coordinate;
    float y1Coordinate;
    float z1Coordinate;
    float x2Coordinate;
    float y2Coordinate;
    float z2Coordinate;
    float x3Coordinate;
    float y3Coordinate;
    float z3Coordinate;

    std::vector<float> mVertices;
    std::vector<float> mColors;

    vector<float>mVerticess;
    vector<float>mColorss;

    QVector<GLfloat> ver;
    QVector<GLfloat> col;
};
