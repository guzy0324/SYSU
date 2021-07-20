/*###################################################
##  姓名：谷正阳
##  文件说明：flat shading的vertex shader，计算多光源
##  下顶点颜色，且不进行插值处理。
#####################################################*/


#version 140
flat out vec4 intensity;

#define MAX_LIGHTS 2

void main(void)
{
	vec3 v = vec3(gl_ModelViewMatrix * gl_Vertex);
	vec3 N = normalize(gl_NormalMatrix * gl_Normal);
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;

	vec4 finalColor = vec4(0.0, 0.0, 0.0, 0.0);

	for (int i=0;i<MAX_LIGHTS;i++)
	{
		vec3 L = normalize(gl_LightSource[i].position.xyz - v);
		vec3 E = normalize(-v); // we are in Eye Coordinates, so EyePos is (0,0,0)
		vec3 R = normalize(-reflect(L,N));

		//calculate Ambient Term:
		vec4 Iamb = gl_FrontLightProduct[i].ambient;
		//calculate Diffuse Term:
		vec4 Idiff = gl_FrontLightProduct[i].diffuse * max(dot(N,L), 0.0);
		Idiff = clamp(Idiff, 0.0, 1.0);

		// calculate Specular Term:
		vec4 Ispec = gl_FrontLightProduct[i].specular
			* pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);
		Ispec = clamp(Ispec, 0.0, 1.0);

		finalColor += Iamb + Idiff + Ispec;
	}

	intensity = gl_FrontLightModelProduct.sceneColor + finalColor;
}
