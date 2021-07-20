/*###################################################
##  姓名：谷正阳
##  文件说明：phong shading的fragment shader，接收插值
##  的顶点位置和法向量，计算多光源下fragment颜色并设置
##  。
#####################################################*/


#version 140
in vec3 v;
in vec3 N;

#define MAX_LIGHTS 2

void main (void)
{
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

	// write Total Color:
	gl_FragColor = gl_FrontLightModelProduct.sceneColor + finalColor;
}
