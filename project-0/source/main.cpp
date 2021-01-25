#include <GL/glut.h>

void box() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBegin(GL_QUADS);					// Each set of 4 vertices form a quad
		// Back (z = -0.5f)
		glColor3f(0.0f, 0.0f, 1.0f);	// Blue
		glVertex3f(-0.5f, -0.5f, -0.5f);	// x, y
		glVertex3f( 0.5f, -0.5f, -0.5f);
		glVertex3f( 0.5f,  0.5f, -0.5f);
		glVertex3f(-0.5f,  0.5f, -0.5f);
		
		// Bottom (y = -0.5f)
		glColor3f(0.0f, 1.0f, 0.0f);	// Green
		glVertex3f(-0.5f, -0.5f, -0.5f);// x, y
		glVertex3f( 0.5f, -0.5f, -0.5f);
		glVertex3f( 0.5f, -0.5f,  0.5f);
		glVertex3f(-0.5f, -0.5f,  0.5f);
		
		// Right (x = 0.5f)
		glColor3f(0.0f, 1.0f, 1.0f);	// Cyan
		glVertex3f(0.5f, -0.5f, -0.5f);	// x, y
		glVertex3f(0.5f,  0.5f, -0.5f);
		glVertex3f(0.5f,  0.5f,  0.5f);
		glVertex3f(0.5f, -0.5f,  0.5f);
		
		// Left (x = -0.5f)
		glColor3f(1.0f, 0.0f, 1.0f);	// Magenta
		glVertex3f(-0.5f, -0.5f, -0.5f);// x, y
		glVertex3f(-0.5f,  0.5f, -0.5f);
		glVertex3f(-0.5f,  0.5f,  0.5f);
		glVertex3f(-0.5f, -0.5f,  0.5f);
		
		// Top (y = 0.5f)
		glColor3f(1.0f, 0.0f, 0.0f);	// Red
		glVertex3f(-0.5f, 0.5f, -0.5f);	// x, y
		glVertex3f( 0.5f, 0.5f, -0.5f);
		glVertex3f( 0.5f, 0.5f,  0.5f);
		glVertex3f(-0.5f, 0.5f,  0.5f);
		
		// Front (z = 0.5f)
		glColor3f(1.0f, 1.0f, 0.0f);	// Yellow
		glVertex3f(-0.5f, -0.5f, 0.5f);	// x, y
		glVertex3f( 0.5f, -0.5f, 0.5f);
		glVertex3f( 0.5f,  0.5f, 0.5f);
		glVertex3f(-0.5f,  0.5f, 0.5f);
	glEnd();

	glutSwapBuffers();
	glFlush();  // Render now
}
void triangle() {
	glClear(GL_COLOR_BUFFER_BIT);		// Clear the color buffer (background)

	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex2f(-0.5f, -0.5f);		// x, y
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex2f( 0.5f, -0.5f);
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex2f( 0.5f,  0.5f);
	glEnd();

	glFlush();  // Render now
}

void square() {
	glClear(GL_COLOR_BUFFER_BIT);		// Clear the color buffer (background)

	glBegin(GL_QUADS);					// Each set of 4 vertices form a quad
		glColor3f(0.0f, 1.0f, 1.0f);
		glVertex2f(-0.5f, -0.5f);		// x, y
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex2f( 0.5f, -0.5f);
		glColor3f(1.0f, 0.0f, 1.0f);
		glVertex2f( 0.5f,  0.5f);
		glColor3f(1.0f, 0.5f, 0.0f);
		glVertex2f(-0.5f,  0.5f);
	glEnd();

	glFlush();  // Render now
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
	glutInit(&argc, argv);					// Initialize GLUT
	glEnable(GL_DEPTH_TEST);
	glutCreateWindow("13-11216 15-10123");	// Create a window with the given title
	glutDisplayFunc(square); 				// Register display callback handler for window re-paint
	glutCreateWindow("13-11216 15-10123");
	glutDisplayFunc(triangle);
	glutCreateWindow("13-11216 15-10123");
	glutDisplayFunc(box);
	/* Adjust cube position to be asthetic angle. */
		glRotatef(20, 1.0, 0.0, 0.0);
		glRotatef(-60, 0.0, 0.0, 1.0);
		//glRotatef(-20, 0.0, 1.0, 0.0);
	glutMainLoop();           // Enter the event-processing loop
	return 0;
}