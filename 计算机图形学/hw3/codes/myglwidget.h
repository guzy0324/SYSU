#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#ifdef MAC_OS
#include <QtOpenGL/QtOpenGL>
#else
#include <GL/glew.h>
#endif
#include <QtGui>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <cmath>
#include <iostream>
#include <queue>
using namespace std;

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    MyGLWidget(QWidget *parent = nullptr);
    ~MyGLWidget();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void read_code(char* (&code), size_t& length, const char* path);
    void DemoLight(void);
    void drawUnitBall(float digit);

private:
    QTimer *timer;
    // 你可以将你的shader或者vbo声明为私有变量
    // GLuint vertexShader;
    // GLuint fragmentShader;
};
#endif // MYGLWIDGET_H

enum Shading {Flat, Gouraud, Phong} ;

struct vec
{
    float x, y, z;
    vec operator+(vec V)
    {
        return vec({ x + V.x, y + V.y, z + V.z });
    }
    void normalize()
    {
        float length = sqrt(x * x + y * y + z * z);
		x /= length;
		y /= length;
		z /= length;
    }
};
