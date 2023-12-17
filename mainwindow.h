#include <QMainWindow>
#include <QGraphicsView>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QMenuBar>
#include <QStatusBar>
#include <QTimer>
#include <QComboBox>  // Include QComboBox
#include "SolarSystem.h"

class OpenGLWindow;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void setupUi();

private slots:
    void startBtn();
    void stopBtn();
    void resetBtn();
    void updateBtn();
    void zoomSliderChanged(int value);
    void onSpeedComboBoxIndexChanged(int index);

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
    OpenGLWindow* mRenderer;
    QComboBox* mSpeedComboBox;
    QSlider* mZoomSlider;
    QGridLayout* mBaseLayout;
    QVBoxLayout* mVbuttonsLayout;
    QHBoxLayout* mButtonsLayout;
    SolarSystem* solar;
};
