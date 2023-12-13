#pragma once
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLBuffer>
#include <cmath>
#include <QTimer>

class QOpenGLTexture;
class QOpenGLShader;
class QOpenGLShaderProgram;
class QOpenGLPaintDevice;

class OpenGLWindow :public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    OpenGLWindow(const QColor& background, QWidget* parent);
    ~OpenGLWindow();
    void setZoomFactor(double zoomFactor);
    void setSpeedMultiplier(double speedMultiplier);

protected:
    void paintGL() override;
    void initializeGL() override;
    

private:
    void drawCircle(QVector<GLfloat>& vertices, QVector<GLfloat>& colors, float cx, float cy, float radius, int segments, const QVector3D& planetColor);
    void drawOrbitingPlanets(QVector<GLfloat>& vertices, QVector<GLfloat>& colors);
    void reset();

public slots:
    void startRevolving();
    void stopRevolving();
    void resetPositions();
    void updatePositions(int numberOfDays);

private:
    QTimer* timer;
    double mZoomFactor;
    bool mIsRevolving;
    QVector<float> planetOrbitPeriod; 
    float mRotationSpeed;
    QOpenGLShaderProgram* mProgram = nullptr;
    QColor mBackground;
    QMetaObject::Connection mContextWatchConnection;
    GLint m_posAttr = 0;
    GLint m_colAttr = 0;
    GLint m_matrixUniform = 0;
    enum { numPlanets = 8 };
    const float sunRadius = 0.5f;
    const float planetRadius[numPlanets] = { 0.2f, 0.3f, 0.4f, 0.25f, 0.35f, 0.3f, 0.25f, 0.1f };
    const float planetDistance[numPlanets] = { 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
    const float planetSpeed[numPlanets] = { 0.25f, 0.2f, 0.15f, 0.12f, 0.1f, 0.08f, 0.06f, 0.04f };
    float planetAngles[numPlanets] = { 0.0f };
    QVector<QVector3D> mPlanetColors;
    GLfloat* mVerticesData;
    GLfloat* mColorsData;
    double mSpeedMultiplier;
};
