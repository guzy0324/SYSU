/*###################################################
##  姓名：谷正阳
##  文件说明：phong shading的vertex shader，计算顶点位
##  置和法向量，且进行插值处理。
#####################################################*/


#version 140
out vec3 v;
out vec3 N;

void main(void)
{
	v = vec3(gl_ModelViewMatrix * gl_Vertex);
	N = normalize(gl_NormalMatrix * gl_Normal);
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
