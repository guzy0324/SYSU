/*###################################################
##  姓名：谷正阳
##  文件说明：flat shading的fragment shader，接收不插值
##  的fragment颜色，并设置。
#####################################################*/


#version 140
flat in vec4 intensity;

void main (void)  
{  
	gl_FragColor = intensity;
}
