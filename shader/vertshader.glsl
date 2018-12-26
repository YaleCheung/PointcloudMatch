#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif

attribute vec4 posAttr;
attribute vec3 colorAttr;

uniform mat4 mvMatrix;
uniform mat4 mvpMatrix;



varying vec3 vColor;
void main()
{
    gl_Position = mvpMatrix * posAttr;
    //gl_PointSize = 10.0;
    vColor = colorAttr;
}
