#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif

attribute vec4 pos_attr;
attribute vec3 color_attr;

uniform mat4 mvp;



varying vec3 v_color;
void main()
{
    gl_Position = mvp * pos_attr;
    v_color = color_attr;
}
