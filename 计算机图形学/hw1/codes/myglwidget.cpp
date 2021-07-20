#include <math.h>
#include "myglwidget.h"

MyGLWidget::MyGLWidget(QWidget *parent)
	:QOpenGLWidget(parent),
	scene_id(1)
{
}

MyGLWidget::~MyGLWidget()
{

}

void MyGLWidget::initializeGL()
{
	glViewport(0, 0, width(), height());
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glDisable(GL_DEPTH_TEST);
}

void MyGLWidget::paintGL()
{
	if (scene_id==0) {
		scene_0();
	}
	else {
		scene_1();
	}
}

void MyGLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	update();
}

void MyGLWidget::keyPressEvent(QKeyEvent *e) {
	//Press 0 or 1 to switch the scene
	if (e->key() == Qt::Key_0) {
		scene_id = 0;
		update();
	}
	else if (e->key() == Qt::Key_1) {
		scene_id = 1;
		update();
	}
}

void MyGLWidget::scene_0()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, 100.0f, 0.0f, 100.0f, -1000.0f, 1000.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(50.0f, 50.0f, 0.0f);
	
	//draw a diagonal "I"
	glPushMatrix();
	glColor3f(0.839f, 0.153f, 0.157f);
	glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glTranslatef(-2.5f, -22.5f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(5.0f, 0.0f);
	glVertex2f(0.0f, 45.0f);

	glVertex2f(5.0f, 0.0f);
	glVertex2f(0.0f, 45.0f);
	glVertex2f(5.0f, 45.0f);

	glEnd();
	glPopMatrix();	
}
/*
函数：quadrilateral
函数描述：绘制四边形，第2，3点在对角线上
参数描述：
x1：第1个点的横坐标
y1：第1个点的纵坐标
x2：第2个点的横坐标
y2：第2个点的纵坐标
x3：第3个点的横坐标
y3：第3个点的纵坐标
x4：第4个点的横坐标
y4：第4个点的纵坐标
*/
void quadrilateral(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
}
/*
函数：eliptic_ring
函数描述：以原点为圆心绘制椭圆环，根据参数方程x=a*r*cos(theta),y=b*r*sin(theta)表示椭圆
参数描述：
start_theta：起始theta值
end_theta：终止theta值
delta_theta：精度，每轮循环theta增加值
r1：内围椭圆参数r
r2：外围椭圆参数r
a：椭圆参数a
b：椭圆参数b
*/
void eliptic_ring(float start_theta, float end_theta, float delta_theta, float r1, float r2, float a, float b)
{
	float theta;
	float x1, y1, x2, y2, x3, y3, x4, y4;
	x1 = a * r1 * cos(start_theta), y1 = b * r1 * sin(start_theta);
	x2 = a * r2 * cos(start_theta), y2 = b * r2 * sin(start_theta);
	for (theta = start_theta + delta_theta; theta <= end_theta; theta += delta_theta)
	{
		x3 = a * r1 * cos(theta), y3 = b * r1 * sin(theta);
		x4 = a * r2 * cos(theta), y4 = b * r2 * sin(theta);
        quadrilateral(x1, y1, x2, y2, x3, y3, x4, y4);
		x1 = x3, y1 = y3, x2 = x4, y2 = y4;
    }
}
/*
函数：G
函数描述：绘制G，包括'C'，'-'
参数描述：None
*/
void G()
{
	float r1, r2, a, b;
    float x1, y1, x2, y2, x3, y3, x4, y4;
    //绘制一个'C'
	r1 = 50.0f, r2 = 70.0f;
	a = 1.0f, b = 1.3f;
    eliptic_ring(M_PI / 4, 2 * M_PI, M_PI / 1048576, r1, r2, a, b);
    //绘制一个'-'
    x1 = a * r2, y1 = -10.0f;
    x2 = x1, y2 = -y1;
    x3 = x1 - 60.0f, y3 = y1;
    x4 = x3, y4 = y2;
    quadrilateral(x1, y1, x2, y2, x3, y3, x4, y4);
}
/*
函数：Z
函数描述：绘制Z，包括'-'，'/'，'-'
参数描述：None
*/
void Z()
{
    float x1, y1, x2, y2, x3, y3, x4, y4;
    //绘制上面的'-'
	x1 = 60.0f, y1 = 80.0f;
    x2 = x1, y2 = y1 - 20.0f;
    x3 = -x1, y3 = y1;
    x4 = x3, y4 = y2;
    quadrilateral(x1, y1, x2, y2, x3, y3, x4, y4);
    //绘制下面的'-'
	y1 = -y1;
    y2 = -y2;
    y3 = -y3;
    y4 = -y4;
    quadrilateral(x1, y1, x2, y2, x3, y3, x4, y4);
    //绘制一个'/'
	x1 = 60.0f, y1 = 80.0f;
	x2 = 90.0f, y2 = 80.0f;
	x3 = -x2, y3 = -y2;
	x4 = -x1, y4 = -y1;
    quadrilateral(x1, y1, x2, y2, x3, y3, x4, y4);
}
/*
函数：Y
函数描述：绘制Y，包括'\'，'/'，'|'
参数描述：None
*/
void Y()
{
    float x1, y1, x2, y2, x3, y3, x4, y4;
    //绘制一个'\'
	x1 = -15.0f, y1 = 0;
    x2 = -x1, y2 = y1;
    x3 = x1 - 60.0f, y3 = 75.0f;
    x4 = x2 - 60.0f, y4 = y3;
    quadrilateral(x1, y1, x2, y2, x3, y3, x4, y4);
    //绘制一个'/'
	x1 = -x1;
    x2 = -x2;
    x3 = -x3;
    x4 = -x4;
    quadrilateral(x1, y1, x2, y2, x3, y3, x4, y4);
    //绘制一个'|'
	x1 = -15.0f, y1 = 0;
    x2 = -x1, y2 = y1;
    x3 = x1, y3 = -75.0f;
    x4 = x2, y4 = y3;
    quadrilateral(x1, y1, x2, y2, x3, y3, x4, y4);
}
/*
函数：scene_1
函数描述：绘制GZY
参数描述：None
*/
void MyGLWidget::scene_1()
{
	glClear(GL_COLOR_BUFFER_BIT);//指定及应用背景颜色
	glMatrixMode(GL_PROJECTION);
	//now we are in projection matrix stack!
	//do projection transformation here...
	glLoadIdentity();//重置当前指定的矩阵为单位矩阵
	glOrtho(0.0f, width(), 0.0f, height(), -1000.0f, 1000.0f);//垂直投影

	glMatrixMode(GL_MODELVIEW);
	//now we are in modelview matrix stack!
	//do modelview transformation here...
    //G的绘制：
	glLoadIdentity();//重置当前指定的矩阵为单位矩阵
	glTranslatef(0.5 * width(), 0.5 * height(), 0.0f);//平移
	glPushMatrix();
	glColor3f(0.839f, 0.153f, 0.157f);//指定物体颜色
	glRotatef(10.0f, 0.0f, 0.0f, 1.0f);//旋转
	glTranslatef(-180.0f, -22.5f, 0.0f);//平移
	glBegin(GL_TRIANGLES);
    G();
	glEnd();

    //Z的绘制：
	glLoadIdentity();//重置当前指定的矩阵为单位矩阵
	glTranslatef(0.5 * width(), 0.5 * height(), 0.0f);//平移
	glPushMatrix();
	glColor3f(0.157f, 0.839f, 0.153f);//指定物体颜色
	glRotatef(0.0f, 0.0f, 0.0f, 1.0f);//旋转
	glTranslatef(5.0f, -22.5f, 0.0f);//平移
	glBegin(GL_TRIANGLES);
    Z();
	glEnd();

    //Y的绘制：
	glLoadIdentity();//重置当前指定的矩阵为单位矩阵
	glTranslatef(0.5 * width(), 0.5 * height(), 0.0f);//平移
	glPushMatrix();
	glColor3f(0.153f, 0.157f, 0.839f);//指定物体颜色
	glRotatef(-10.0f, 0.0f, 0.0f, 1.0f);//旋转
	glTranslatef(180.0f, -22.5f, 0.0f);//平移
	glBegin(GL_TRIANGLES);
    Y();
	glEnd();

	glPopMatrix();
}
