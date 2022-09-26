#version 330 core
in vec3 originalColor;
out vec4 FragColor;

void main() {
    // 0 0 / 0.2  0.8 / 0,4 0
	float borderWidth = 0.005;

	FragColor = vec4(originalColor, 1.0);
	
}