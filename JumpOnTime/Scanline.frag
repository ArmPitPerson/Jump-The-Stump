uniform sampler2D texture;
uniform float currentTime;

void main() {
    float lineWidth = 0.0025;
    float X = gl_TexCoord[0].x;
    float Y = gl_TexCoord[0].y;
    
    float RPixelValue = clamp(sin((currentTime + 2.0) * 4.0 + Y / lineWidth) + 1, 0.95, 1.0);
    float GPixelValue = clamp(sin(currentTime * 4.0 + Y / lineWidth) + 1, 0.95, 1.0);
    float BPixelValue = clamp(sin((currentTime - 2.0) * 4.0 + Y / lineWidth) + 1, 0.95, 1.0);

    
    gl_FragColor = texture2D(texture, gl_TexCoord[0].xy) * vec4(RPixelValue, GPixelValue, BPixelValue, 1.0);
}