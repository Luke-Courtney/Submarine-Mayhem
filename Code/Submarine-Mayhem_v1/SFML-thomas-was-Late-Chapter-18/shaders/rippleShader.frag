#version 110
// attributes from vertShader.vert
//varying vec4 vColor;
//varying vec2 vTexCoord;

in  vec4 vColor;
in vec2 vTexCoord;
vec2 pCoord;


// uniforms
uniform sampler2D uTexture;
uniform float uTime;

void main() {
	float coef = sin(gl_FragCoord.y * 0.1 + 1.0 * uTime);
	pCoord=vTexCoord;
	pCoord.y +=  coef * 0.1;
   //  coef = coef *0.03;

	// vTexCoord.y +=coef;
	gl_FragColor = vColor * texture2D(uTexture, pCoord);
	//gl_FragColor = vColor * texture2D(uTexture, vTexCoord);
}
