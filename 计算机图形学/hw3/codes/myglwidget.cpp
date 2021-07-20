/*###################################################
##  姓名：谷正阳
##  文件说明：实现了加载shader，两种方法绘制球。
#####################################################*/


#include "myglwidget.h"
//Shading shading = Phong;
//Shading shading = Gouraud;
Shading shading = Flat;
//float digit = 0.01f * M_PI;
//size_t Depth = 4;
float digit = 0.2 * M_PI;
size_t Depth = 2;

/*###################################################
##  函数: MyGLWidget
##  函数描述： MyGLWidget类的构造函数，实例化定时器timer
##  参数描述：
##  parent: MyGLWidget的父对象
#####################################################*/
MyGLWidget::MyGLWidget(QWidget *parent)
	:QOpenGLWidget(parent)
{
	timer = new QTimer(this); // 实例化一个定时器
	timer->start(16); // 时间间隔设置为16ms，可以根据需要调整
	connect(timer, SIGNAL(timeout()), this, SLOT(update())); // 连接update()函数，每16ms触发一次update()函数进行重新绘图
}


/*###################################################
##  函数: ~MyGLWidget
##  函数描述： ~MyGLWidget类的析构函数，删除timer
##  参数描述： 无
#####################################################*/

MyGLWidget::~MyGLWidget()
{
	delete this->timer;
}


/*###################################################
##  函数: read_code
##  函数描述：读取代码文件成字符串
##  参数描述：
##  code: 字符串的容器，其内存分配呈指数增加
##  length: 容器长度（并非字符串长度，因为字符串到'\0'就截断了
##  path: 代码文件的路径
#####################################################*/
void MyGLWidget::read_code(char* (&code), size_t &length, const char* path)
{
	FILE* fp = fopen(path, "r");
	char ch;
	size_t index = 0;
	while ((ch = fgetc(fp)) != EOF)
	{
		if (index == length)
		{
			length *= 2;
			code = (char *)realloc(code, length * sizeof(char));
		}
		code[index++] = ch;
	}
	if (index == length)
	{
		length *= 2;
		code = (char *)realloc(code, length * sizeof(char));
	}
	code[index++] = '\0';
	fclose(fp);
}


/*###################################################
##  函数: DemoLight
##  函数描述：读取代码文件成字符串
##  参数描述：
##  code: 字符串的容器，其内存分配呈指数增加
##  length: 容器长度（并非字符串长度，因为字符串到'\0'就截断了
##  path: 代码文件的路径
#####################################################*/
void MyGLWidget::DemoLight(void)
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	//glEnable(GL_NORMALIZE);

	// Light model parameters:
	// -------------------------------------------

	//GLfloat lmKa[] = { 0.0, 0.0, 0.0, 0.0 };
	//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);

	//glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
	//glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

	// -------------------------------------------
	// Spotlight Attenuation

	//GLfloat spot_direction[] = { 1.0, -1.0, -1.0 };
	//GLint spot_exponent = 30;
	//GLint spot_cutoff = 180;

	//glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	//glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
	//glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);
	//glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction);
	//glLighti(GL_LIGHT1, GL_SPOT_EXPONENT, spot_exponent);
	//glLighti(GL_LIGHT1, GL_SPOT_CUTOFF, spot_cutoff);

	//GLfloat Kc = 1.0;
	//GLfloat Kl = 0.0;
	//GLfloat Kq = 0.0;

	//glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Kc);
	//glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
	//glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);
	//glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, Kc);
	//glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, Kl);
	//glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, Kq);


	// ------------------------------------------- 
	// Lighting parameters:

	GLfloat light_pos0[] = { 10.0f, 0.0f, -50.0f, 1.0f };
	GLfloat light_pos1[] = { -10.0f, 0.0f, -50.0f, 1.0f };
	GLfloat light_Ka[] = { 1.0f, 0.5f, 0.5f, 1.0f };
	GLfloat light_Kd[] = { 1.0f, 0.1f, 0.1f, 1.0f };
	GLfloat light_Ks[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);
	glLightfv(GL_LIGHT1, GL_POSITION, light_pos1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_Ka);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_Kd);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_Ks);

	// -------------------------------------------
	// Material parameters:

	GLfloat material_Ka[] = { 0.5f, 0.0f, 0.0f, 1.0f };
	GLfloat material_Kd[] = { 0.4f, 0.4f, 0.5f, 1.0f };
	GLfloat material_Ks[] = { 0.8f, 0.8f, 0.0f, 1.0f };
	GLfloat material_Ke[] = { 0.1f, 0.0f, 0.0f, 0.0f };
	GLfloat material_Se = 20.0f;

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
	//glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
}


QOpenGLShaderProgram* program;
/*###################################################
##  函数: initializeGL
##  函数描述： 初始化绘图参数，如视窗大小、背景色等
##  参数描述： 无
#####################################################*/
void MyGLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    // vertexShader = glCreateShader(GL_VERTEX_SHADER);
    // Your Implementation
	program = new QOpenGLShaderProgram(context());

	char* code = (char *)malloc(sizeof(char));
	size_t length = 1;
	if (shading == Flat)
	{
		read_code(code, length, "flat.vert");
	}
	else if(shading == Gouraud)
    {
		read_code(code, length, "gouraud.vert");
    }
    else
	{
		read_code(code, length, "phong.vert");
	}
    program->addShaderFromSourceCode(QOpenGLShader::Vertex, code);
	if (shading == Flat)
	{
		read_code(code, length, "flat.frag");
	}
	else if(shading == Gouraud)
    {
		read_code(code, length, "gouraud.frag");
    }
    else
	{
		read_code(code, length, "phong.frag");
	}
	program->addShaderFromSourceCode(QOpenGLShader::Fragment, code);
	program->link();
	program->bind();

	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, width() / height(), 30.0f, 70.0f);

	DemoLight();

    glViewport(0, 0, width(), height());
	glEnable(GL_DEPTH_TEST);
}


/*###################################################
##  函数: drawUnitBall
##  函数描述： 用经纬度绘制单位球
##  参数描述： 
##  digit: 精度，即每次phi和theta的变化量
#####################################################*/
void MyGLWidget::drawUnitBall(float digit =  0.01f * M_PI)
{
	float phi, phi_next, theta;
	bool flag;
	for (phi = 0.0f; phi <= 2 * M_PI; phi = phi_next)
	{
		phi_next = phi + digit;
		flag = true;
		glBegin(GL_TRIANGLE_STRIP);
		for (theta = 0.0f; theta <= M_PI; flag = !flag)
		{
			if (flag)
			{
				if (phi_next < 2 * M_PI)
				{
					glVertex3f(sin(theta) * sin(phi_next), cos(theta), sin(theta) * cos(phi_next));
				}
				else
				{
					glVertex3f(0.0f, cos(theta), sin(theta));
				}
				theta += digit;
			}
			else
			{
				glVertex3f(sin(theta) * sin(phi), cos(theta), sin(theta) * cos(phi));
			}
		}
		if (!flag)
		{
			glVertex3f(0.0f, -1.0f, 0.0f);
		}
		glEnd();
	}
}


/*###################################################
##  函数: spherical_subdivision
##  函数描述： 球面细分
##  参数描述： 
##  depth: 细分深度
#####################################################*/
void spherical_subdivision(size_t depth = 4)
{
	float a = sqrt(3) / 3;
	queue<vec> triangles;
	vec vertexes[4] = { {a, -a, a}, {-a, a, a}, {a, a, -a}, {-a, -a, -a} };
	triangles.push(vertexes[0]), triangles.push(vertexes[2]), triangles.push(vertexes[1]);
	triangles.push(vertexes[0]), triangles.push(vertexes[1]), triangles.push(vertexes[3]);
	triangles.push(vertexes[0]), triangles.push(vertexes[3]), triangles.push(vertexes[2]);
	triangles.push(vertexes[1]), triangles.push(vertexes[2]), triangles.push(vertexes[3]);

	for (size_t i = 0; i < depth; i++)
	{
		size_t size = triangles.size();
		for (size_t j = 0; j < size; j += 3)
		{
			vec v0 = triangles.front(); triangles.pop();
			vec v1 = triangles.front(); triangles.pop();
			vec v2 = triangles.front(); triangles.pop();
			vec v01 = v0 + v1; v01.normalize();
			vec v02 = v0 + v2; v02.normalize();
			vec v12 = v1 + v2; v12.normalize();
			triangles.push(v0), triangles.push(v01), triangles.push(v02);
			triangles.push(v1), triangles.push(v12), triangles.push(v01);
			triangles.push(v2), triangles.push(v02), triangles.push(v12);
			triangles.push(v01), triangles.push(v12), triangles.push(v02);
		}
	}

	while (!triangles.empty())
	{
		vec v0 = triangles.front(); triangles.pop();
		vec v1 = triangles.front(); triangles.pop();
		vec v2 = triangles.front(); triangles.pop();
		glBegin(GL_TRIANGLES);
		glVertex3f(v0.x, v0.y, v0.z);
		glVertex3f(v1.x, v1.y, v1.z);
		glVertex3f(v2.x, v2.y, v2.z);
		glEnd();
	}
}


/*###################################################
##  函数: paintGL
##  函数描述： 绘图函数，实现图形绘制，会被update()函数调用
##  参数描述： 无
#####################################################*/
void MyGLWidget::paintGL()
{
	// Your Implementation
	static float theta = 0.0f, delta_theta = 0.01f * M_PI;
	static bool vertical = true;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	if (vertical)
	{
		glTranslatef(10.0f, 10.0f * sin(theta), -10.0f * cos(theta) - 50.0f);
	}
	else
	{
		glTranslatef(10.0f * (1 - sin(theta)), 0.0f, -10.0f * cos(theta) - 50.0f);
	}
	glScalef(6.0f, 6.0f, 6.0f);
	spherical_subdivision(Depth);
    glPopMatrix();

	glPushMatrix();
	if (vertical)
	{
		glTranslatef(-10.0f, 10.0f * sin(theta), -10.0f * cos(theta) - 50.0f);
	}
	else
	{
		glTranslatef(10.0f * (-1 - sin(theta)), 0.0f, -10.0f * cos(theta) - 50.0f);
	}
	glScalef(6.0f, 6.0f, 6.0f);
	drawUnitBall(digit);
    glPopMatrix();

	theta += delta_theta;
	if (theta >= 2 * M_PI)
	{
		theta = 0.0f;
		vertical = !vertical;
	}
}


/*###################################################
##  函数: resizeGL
##  函数描述： 当窗口大小改变时调整视窗尺寸
##  参数描述： 无
#####################################################*/
void MyGLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	update();
}

