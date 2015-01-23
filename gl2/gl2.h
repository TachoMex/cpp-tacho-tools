#ifndef GL2_H
#ifdef COLOR_H

	inline void glColor(const color& c){
		glColor3ub(c.r, c.g, c.b);
	}


	inline void glColorAlpha(const color& c){
		glColor4ub(c.r, c.g, c.b,255);
	}

#endif

#ifdef PUNTO3D_H

	inline void glVertex(const _3D::punto& p){
		glVertex3f((GLfloat)p.x, (GLfloat)p.y, (GLfloat)p.z);
	}

	inline void gluLookAt(const _3D::punto& from, const _3D::punto& to, const _3D::punto& up){
		gluLookAt(from.x, from.y, from.z, to.x, to.y, to.z, up.z, up.y, up.z);
	}


#endif

#ifdef LINEA3D_H

	inline void glDraw(const _3D::linea& l,int size=0){
		glBegin(GL_LINES);
		glVertex(l.inicio);
		glVertex(l.fin);
		glEnd();
	}

#endif

#ifdef IMAGEN_H

	void drawAt(const imagen& M, int h, int k){
		glBegin(GL_POINTS);
		for(int i=0;i<M.y;i++)
			for(int j=0;j<M.x;j++){
				int p,q;
				p=h+i;
				q=k+j;
				try{
					glColor(M.en(i,j););
					glVertex2i(q, p);
				}catch(int e){
				}
			}

		glEnd();
		glFlush();
	}

	inline void glReadPixels(imagen &M){
		delete M.pixels;
		M.x=glutGet(GLUT_WINDOW_WIDTH);
		M.y=glutGet(GLUT_WINDOW_HEIGHT);
		pixels = new color[x*y];
		glReadPixels(0,0,M.x,M.y,GL_RGB,GL_UNSIGNED_BYTE,M.pixels);
	}

	inline void glReadPixels(imagen &M ,int x2, int y2){
		delete M.pixels;
		M.x=x2;
		M.y=y2;
		pixels = new color[M.x*M.y];
		glReadPixels(0,0,x,y,GL_RGB, GL_UNSIGNED_BYTE, M.pixels);

	}
	
	inline void glDrawPixels(const imagen &M){
		glDrawPixels(M.x,M.y,GL_RGB,GL_UNSIGNED_BYTE, M.pixels);
	}
#endif


#ifdef PUNTO2D_H
	template<class T>
	inline void glVertex(const _2D::punto<T>& p){
		glVertex2f((GLfloat)p.x, (GLfloat)p.y);
	}
#endif

#ifdef LINEA2D_H

	template<class T>
	inline void glDraw(const _2D::linea<T>& l, int size=0){
		#ifdef PRIMITIVAS_H
			primitivas::linea(l.inicio.x, l.inicio.y, l.fin.x, l.fin.y, size);
		#else
			glBegin(GL_LINES);
				glVertex(l.inicio);
				glVertex(l.fin);
			glEnd();
		#endif
	}

#endif
#endif

