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
#include<ctime>
using namespace std;

class MyGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    Q_OBJECT

public:
    MyGLWidget(QWidget *parent = nullptr);
    ~MyGLWidget();

protected:
    void initVBOEBO();
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void read_code(char* (&code), size_t& length, const char* path);
    void DemoLight(void);
    void spherical_subdivision(size_t depth);
    void spherical_subdivision_VBO(size_t depth);
    void spherical_subdivision_EBO(size_t depth);

private:
    QTimer *timer;
    GLuint VBO;
	GLuint EBO;
    int v_size;
    int i_size;
};
#endif // MYGLWIDGET_H

enum Shading {Flat, Gouraud, Phong} ;

struct vec
{
    float x, y, z;
	vec(GLfloat xx, GLfloat yy, GLfloat zz) : x(xx), y(yy), z(zz) {}
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
