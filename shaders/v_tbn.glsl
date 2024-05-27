#version 330

//Zmienne jednorodne
uniform mat4 P;
uniform mat4 V;
uniform mat4 M;
uniform vec3 cameraPos;
uniform vec2 texRepeat = vec2(1,1);

//Atrybuty
in vec4 vertex; //wspolrzedne wierzcholka w przestrzeni modelu
in vec4 c1; //kolor związany z wierzchołkiem
in vec4 c2; //wektor normalny w przestrzeni modelu
in vec4 c3; //wektor normalny w przestrzeni modelu
in vec2 texCoord0;

//Zmienne interpolowane
out vec4 l;
out vec4 v;
out vec2 iTexCoord0;


void main(void) {
    vec4 lp = vec4(cameraPos, 1); //przestrzeń świata

    iTexCoord0 = texCoord0*texRepeat;

    mat4 invTBN = mat4(c1, c2, c3, vec4(0,0,0,1));
    l = normalize(invTBN * (inverse(M) * lp - vertex));
    v = normalize(invTBN * (inverse(V*M) * vec4(0,0,0,1) - vertex));

    gl_Position=P*V*M*vertex;
}
