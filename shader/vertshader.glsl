#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif

attribute vec4 pos_attr;
attribute vec3 color_attr;

uniform mat4 mv_matrix;
uniform mat4 mvp_matrix;



varying vec3 v_color;
void main()
{
    gl_Position = mvp_matrix * pos_attr;
    //gl_PointSize = 10.0;
    v_color = color_attr;
}
