/*###################################################
##  姓名：谷正阳
##  文件说明：实现了VBO和EBO，并测试其平均运行时间。
#####################################################*/


#include "myglwidget.h"
//Shading shading = Phong;
//Shading shading = Gouraud;
Shading shading = Flat;
size_t Depth = 6;
//size_t Depth = 4;
//size_t Depth = 2;
unsigned freq = 30;
size_t MAX_V_SIZE = 0x100000;
size_t MAX_I_SIZE = 0x10000;


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
##  函数: initVBOEBO
##  函数描述： 初始化VBOEBO
##  参数描述： 无
#####################################################*/
void MyGLWidget::initVBOEBO()
{
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, MAX_V_SIZE * sizeof(GLfloat), nullptr, GL_STATIC_DRAW);
	v_size = 0;

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_I_SIZE * sizeof(GLuint), nullptr, GL_STATIC_DRAW);
	i_size = 0;
    // set the vertex attributes pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
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

	GLfloat light_pos0[] = { 0.0f, 0.0f, -50.0f, 1.0f };
	GLfloat light_Ka[] = { 1.0f, 0.5f, 0.5f, 1.0f };
	GLfloat light_Kd[] = { 1.0f, 0.1f, 0.1f, 1.0f };
	GLfloat light_Ks[] = { 1.0f, 1.0f, 1.0f, 1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, light_pos0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

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
	initVBOEBO();

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
## 1函数: spherical_subdivision
##  函数描述： 球面细分
##  参数描述： 
##  depth: 细分深度
#####################################################*/
void MyGLWidget::spherical_subdivision(size_t depth = 4)
{
	static bool is_calc = false;
	static vector<vec> vert;

	if (!is_calc)
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
			vec v = triangles.front(); triangles.pop(); vert.push_back(v);
			v = triangles.front(); triangles.pop(); vert.push_back(v);
			v = triangles.front(); triangles.pop(); vert.push_back(v);
		}
		is_calc = true;
	}
	for (int i = 0; i < vert.size(); i += 3)
	{
		glBegin(GL_TRIANGLES);
		glVertex3f(vert[i].x, vert[i].y, vert[i].z);
		glVertex3f(vert[i + 1].x, vert[i + 1].y, vert[i + 1].z);
		glVertex3f(vert[i + 2].x, vert[i + 2].y, vert[i + 2].z);
		glEnd();
	}
}


/*###################################################
##  函数: spherical_subdivision_VBO
##  函数描述： 球面细分，使用VBO
##  参数描述：
##  depth: 细分深度
#####################################################*/
void MyGLWidget::spherical_subdivision_VBO(size_t depth = 4)
{
	static bool is_calc = false;
	static int v_begin;
	static int v_end;
	if (!is_calc)
	{
		v_begin = v_size;

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

		vector<GLfloat> vertices;
		while (!triangles.empty())
		{
			vec v = triangles.front(); triangles.pop();
			vertices.push_back(v.x), vertices.push_back(v.y), vertices.push_back(v.z);
			v = triangles.front(); triangles.pop();
			vertices.push_back(v.x), vertices.push_back(v.y), vertices.push_back(v.z);
			v = triangles.front(); triangles.pop();
			vertices.push_back(v.x), vertices.push_back(v.y), vertices.push_back(v.z);
		}
		v_size = v_begin + vertices.size();
		v_end = v_size;
        // copy our vertices array in a vertex buffer for OpenGL to use
		glBufferSubData(GL_ARRAY_BUFFER, v_begin * sizeof(GLfloat), (v_end - v_begin) * sizeof(GLfloat), &vertices[0]);
		is_calc = true;
	}
	glDrawArrays(GL_TRIANGLES, v_begin / 3, (v_end - v_begin) / 3);
}


/*###################################################
##  函数: spherical_subdivision_EBO
##  函数描述： 球面细分，使用EBO
##  参数描述：
##  depth: 细分深度
#####################################################*/
void MyGLWidget::spherical_subdivision_EBO(size_t depth = 4)
{
	static bool is_calc = false;
	static int i_begin;
	static int i_end;
	if (!is_calc)
	{
		i_begin = i_size;

		float a = sqrt(3) / 3;
		vector<GLfloat> vertices;
		vertices.push_back(a), vertices.push_back(-a), vertices.push_back(a);
		vertices.push_back(-a), vertices.push_back(a), vertices.push_back(a);
		vertices.push_back(a), vertices.push_back(a), vertices.push_back(-a);
		vertices.push_back(-a), vertices.push_back(-a), vertices.push_back(-a);
		queue<GLuint> triangles;
		triangles.push(0), triangles.push(2), triangles.push(1);
		triangles.push(0), triangles.push(1), triangles.push(3);
		triangles.push(0), triangles.push(3), triangles.push(2);
		triangles.push(1), triangles.push(2), triangles.push(3);

		for (size_t i = 0; i < depth; i++)
		{
			size_t size = triangles.size();
			for (size_t j = 0; j < size; j += 3)
			{
				GLuint i0 = triangles.front(); triangles.pop();
				GLuint i1 = triangles.front(); triangles.pop();
				GLuint i2 = triangles.front(); triangles.pop();
				vec v0 = vec(vertices[3 * i0], vertices[3 * i0 + 1], vertices[3 * i0 + 2]);
				vec v1 = vec(vertices[3 * i1], vertices[3 * i1 + 1], vertices[3 * i1 + 2]);
				vec v2 = vec(vertices[3 * i2], vertices[3 * i2 + 1], vertices[3 * i2 + 2]);
				vec v01 = v0 + v1; v01.normalize();
				vec v02 = v0 + v2; v02.normalize();
				vec v12 = v1 + v2; v12.normalize();
				GLuint i01 = vertices.size() / 3;
				vertices.push_back(v01.x), vertices.push_back(v01.y), vertices.push_back(v01.z);
				GLuint i02 = vertices.size() / 3;
				vertices.push_back(v02.x), vertices.push_back(v02.y), vertices.push_back(v02.z);
				GLuint i12 = vertices.size() / 3;
				vertices.push_back(v12.x), vertices.push_back(v12.y), vertices.push_back(v12.z);
				triangles.push(i0), triangles.push(i01), triangles.push(i02);
				triangles.push(i1), triangles.push(i12), triangles.push(i01);
				triangles.push(i2), triangles.push(i02), triangles.push(i12);
				triangles.push(i01), triangles.push(i12), triangles.push(i02);
			}
		}

		int v_begin = v_size;
		v_size = v_begin + vertices.size();
        // copy our vertices array in a vertex buffer for OpenGL to use
		glBufferSubData(GL_ARRAY_BUFFER, v_begin * sizeof(GLfloat), (v_size - v_begin) * sizeof(GLfloat), &vertices[0]);
		v_begin /= 3;
		vector<GLuint> indices;
		while (!triangles.empty())
		{
			GLuint i = triangles.front(); triangles.pop();
			indices.push_back(v_begin + i);
			i = triangles.front(); triangles.pop();
			indices.push_back(v_begin + i);
			i = triangles.front(); triangles.pop();
			indices.push_back(v_begin + i);
		}
		i_end = indices.size();
        // copy our index array in a element buffer for OpenGL to use
		glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, i_begin * sizeof(GLuint), (i_end - i_begin) * sizeof(GLuint), &indices[0]);
		is_calc = true;
	}
	glDrawElements(GL_TRIANGLES, i_end - i_begin, GL_UNSIGNED_INT, (void*)(i_begin * sizeof(GLuint)));
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
	static unsigned long long method = 0;
	static double sum0 = 0.0;
	static double sum1 = 0.0;
	static double sum2 = 0.0;
	clock_t start;
	clock_t end;

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	if (vertical)
	{
		glTranslatef(0.0f, 10.0f * sin(theta), -10.0f * cos(theta) - 50.0f);
	}
	else
	{
		glTranslatef(-10.0f * sin(theta), 0.0f, -10.0f * cos(theta) - 50.0f);
	}
	glScalef(6.0f, 6.0f, 6.0f);
	if (method % freq == 0)
	{
		system("cls");
		cout << "origin\t" << sum0 / method * 3e6 << "\tus" << endl;
		cout << "VBO\t" << sum1 / method * 3e6 << "\tus" << endl;
		cout << "EBO\t" << sum2 / method * 3e6 << "\tus" << endl;
	}
	switch (method++ % 3)
	{
	case 0:
		start = clock();
		spherical_subdivision(Depth);
		end = clock();
		sum0 += (double)(end - start) / CLOCKS_PER_SEC;
		break;
	case 1:
		start = clock();
		spherical_subdivision_VBO(Depth);
		end = clock();
		sum1 += (double)(end - start) / CLOCKS_PER_SEC;
		break;
	case 2:
		start = clock();
		spherical_subdivision_EBO(Depth);
		end = clock();
		sum2 += (double)(end - start) / CLOCKS_PER_SEC;
		break;
	}
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

