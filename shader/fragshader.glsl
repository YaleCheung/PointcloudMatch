#ifdef GL_ES
precision mediump int;
precision mediump float;
#endif

varying vec3 vColor;

void main()
{
    gl_FragColor = vec4(vColor, 0.5f);
}
