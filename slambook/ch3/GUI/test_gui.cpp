#include <GL/glut.h>

void display()
{
    // 清除颜色缓冲
    glClear(GL_COLOR_BUFFER_BIT);

    // 设置绘制颜色为红色
    glColor3f(1.0, 0.0, 0.0);

    // 开始绘制三角形
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5, -0.5);
    glVertex2f(0.5, -0.5);
    glVertex2f(0.0, 0.5);
    glEnd();

    // 刷新显示
    glutSwapBuffers();
}

int main(int argc, char **argv)
{
    // 初始化GLUT
    glutInit(&argc, argv);

    // 设置显示模式
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // 设置窗口大小和位置
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);

    // 创建窗口
    glutCreateWindow("OpenGL Test Window");

    // 设置背景色为白色
    glClearColor(1.0, 1.0, 1.0, 0.0);

    // 注册显示回调函数
    glutDisplayFunc(display);

    // 进入GLUT事件处理循环
    glutMainLoop();

    return 0;
}