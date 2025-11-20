uniform sampler2D texture;
uniform float time;
uniform vec2 resolution;

void main()
{
    vec2 uv = gl_FragCoord.xy / resolution;
    
    // Эффект выпуклости ЭЛТ-монитора
    vec2 crtUV = uv - 0.5;
    crtUV *= 1.1;
    crtUV += 0.5;
    
    // Линии сканирования (как на старом ТВ)
    float scanline = sin(crtUV.y * resolution.y * 0.7 + time * 5.0) * 0.03;
    crtUV.x += scanline;
    
    // Хроматическая аберрация (RGB разделение)
    vec4 color;
    color.r = texture2D(texture, crtUV + vec2(0.003, 0.0)).r;
    color.g = texture2D(texture, crtUV).g;
    color.b = texture2D(texture, crtUV - vec2(0.003, 0.0)).b;
    color.a = 1.0;
    
    // Виньетирование (тёмные углы)
    float vignette = 1.0 - distance(uv, vec2(0.5, 0.5)) * 1.2;//0.8
    color.rgb *= vignette;
    
    // Статический шум
    float noise = fract(sin(dot(uv + time, vec2(12.9898, 78.233))) * 43758.5453) * 0.04;//0.02
    color.rgb += noise;
    
    gl_FragColor = color;
}