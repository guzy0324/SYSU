/*###################################################
##  姓名：谷正阳
##  文件说明：gouraud shading的fragment shader，接收插
##  值的fragment颜色，并设置。
#####################################################*/


#version 140
in vec4 intensity;

void main (void)  
{  
	gl_FragColor = intensity;
}
