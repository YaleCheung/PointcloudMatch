#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif

varying vec3 v_color;

void main()
{
    gl_FragColor = vec4(v_color, 0.5f);
}
