// Ad Maiorem Dei Gloriam!
#include "graphics/shader.h"

Shader shader_create(const char *vertex, const char *frag) {
    Shader program;
    
    FILE *vertPtr = fopen(vertex, "r");
    if (!vertPtr) {
        printf("Error: Could not open vertex shader source code file: %s\n", vertex);
        return 0;
    }
    FILE *fragPtr = fopen(frag, "r");
    if (!fragPtr) {
        printf("Error: Could not open fragment shader source code file: %s\n", vertex);
        return 0;
    }

    fseek(vertPtr, 0, SEEK_END);
    fseek(fragPtr, 0, SEEK_END);
    unsigned int vertFileSize = ftell(vertPtr);
    unsigned int fragFileSize = ftell(fragPtr);
    fseek(vertPtr, 0, SEEK_SET);
    fseek(fragPtr, 0, SEEK_SET);

    
    char *vertSrc = (char*)malloc(vertFileSize + 1);
    if (vertSrc == NULL) {
        printf("Error: Could not compile vertex shader: Not enough memory.\n");
        return 0;
    }
    vertSrc[vertFileSize] = '\0';

    char *fragSrc = (char*)malloc(fragFileSize + 1);
    if (fragSrc == NULL) {
        printf("Error: Could not compile fragment shader: Not enough memory.\n");
        return 0;
    }
    fragSrc[fragFileSize] = '\0';

    fread(vertSrc, 1, vertFileSize, vertPtr);
    fread(fragSrc, 1, fragFileSize, fragPtr);

    fclose(vertPtr);
    fclose(fragPtr);
    
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    int success;
    char errorBuff[512];
    
    glShaderSource(vertexShader, 1, (const GLchar * const *)&vertSrc, NULL);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, errorBuff);
        printf("Error while compiling vertex shader:\n%s\n", errorBuff);

        free(vertSrc);
        free(fragSrc);
        return 0;
    }

    glShaderSource(fragmentShader, 1, (const GLchar * const *)&fragSrc, NULL);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, errorBuff);
        printf("Error while compiling fragment shader:\n%s\n", errorBuff);

        free(vertSrc);
        free(fragSrc);
        return 0;
    }

    free(vertSrc);
    free(fragSrc);

    program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, errorBuff);
        printf("Error while linking program:\n%s\n", errorBuff);
        return 0;
    }

    return program;
}

void shader_bind(Shader shader) {
    glUseProgram(shader);
}

void shader_destroy(Shader shader) {
    glDeleteProgram(shader);
}