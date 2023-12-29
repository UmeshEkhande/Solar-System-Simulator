#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <cmath>
#include <QTimer>
#include "SolarSystem.h"

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;
class QOpenGLPaintDevice;
class SolarSystem;

class OpenGLWindow :public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWindow(const QColor& background, QWidget* parent);
    ~OpenGLWindow();

    void setZoomFactor(GLfloat &zoomFactor);
    void setSpeedMultiplier(double speedMultiplier);
    void startRevolving();
    void stopRevolving();
    void resetPositions();
    void updatePositions(int numberOfDays);
    void updateSolarSystemData();
    void startRendering();
    void stopRendering();
    void updateData(std::vector<float>& vertices, std::vector<float>& colors);
    void updateData(const QVector<GLfloat>& vertices, const QVector<GLfloat>& colors, int  flag);

protected:
    void paintGL() override;
    void initializeGL() override;

    
private:
    void reset();
    QString readShaderSource(QString filePath);
    void mouseMoveEvent(QMouseEvent* event);
    void shaderWatcher();


private:
    QTimer* timer;
    SolarSystem* solar;
    QOpenGLShaderProgram* mProgram = nullptr;
    QColor mBackground;
    QMetaObject::Connection mContextWatchConnection;
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;
    GLint m_rotationAngleUniform;  // Add this line


    float* mVerticesData;
    float* mColorsData;
    GLfloat mZoomFactor;
    bool mIsRevolving;

    std::vector<float> mVertices;
    std::vector<float> mColors;

    QVector<GLfloat> verticesOfOrignalLine;
    QVector<GLfloat> colorOfOrignalLine;

    QQuaternion rotationAngle;
    QPoint lastPos;

    QFileSystemWatcher* mShaderWatcher;

    int mFlag;
};
