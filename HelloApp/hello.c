#include <GLFW/glfw3.h>
#include <math.h>

#define PI 3.14159265358979323846

float previous_time;
float rotation_angle = 0.0f;
float rotation_speed = 360.0f; // градусов в секунду
float triangle_size = 0.25f;

void draw_triangle()
{
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 1.0f); // цвет белый
    glVertex2f(0.0f, triangle_size); // вершина 1
    glVertex2f(-triangle_size * sqrt(3) / 2.0f, -triangle_size / 2.0f); // вершина 2
    glVertex2f(triangle_size * sqrt(3) / 2.0f, -triangle_size / 2.0f); // вершина 3
    glEnd();
}

void draw(GLFWwindow* window)
{
    glClear(GL_COLOR_BUFFER_BIT); // очищаем буфер цвета

    glLoadIdentity();
    glRotatef(rotation_angle, 0.0f, 0.0f, 1.0f); // поворачиваем на угол

    draw_triangle();

    glfwSwapBuffers(window);
}

void update()
{
    float current_time = (float)glfwGetTime(); // текущее время
    float delta_time = current_time - previous_time;
    previous_time = current_time; // сохраняем текущее время для следующего кадра

    rotation_angle += rotation_speed * delta_time; // обновляем угол поворота
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
        triangle_size += 0.05f;
    }
    if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
        triangle_size -= 0.05f;
    }
    if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
        rotation_speed += 90.0f;
    }
    if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
        rotation_speed -= 90.0f;
    }
}

int main()
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(640, 480, "Triangle", NULL, NULL);
    glfwMakeContextCurrent(window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f); // устанавливаем ортографическую проекцию

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0f, 0.0f, -1.0f); // перемещаем в центр экрана

    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window))
    {
        update();
        draw(window);

        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
