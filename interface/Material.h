// Material.h

#pragma once

class Material{
public:
	GLfloat matf[10];
	
	// initial values
	Material(void){
		matf[0] = 0.3f;
		matf[1] = 0.3f;
		matf[2] = 0.3f;
		matf[3] = 0.8f;
		matf[4] = 0.8f;
		matf[5] = 0.8f;
		matf[6] = 0.3f;
		matf[7] = 0.3f;
		matf[8] = 0.3f;
		matf[9] = 15.0f;
	}
	
	Material(float *m){memcpy(matf, m, 10*sizeof(float));}

	Material(const HeeksColor& col){
		matf[0] = 0.1f + 0.1f * (float)col.red/255;
		matf[1] = 0.1f + 0.1f * (float)col.green/255;
		matf[2] = 0.1f + 0.1f * (float)col.blue/255;
		matf[3] = 0.2f + 0.8f * (float)col.red / 255;
		matf[4] = 0.2f + 0.8f * (float)col.green / 255;
		matf[5] = 0.2f + 0.8f * (float)col.blue / 255;
		matf[6] = 0.3f;
		matf[7] = 0.3f;
		matf[8] = 0.3f;
		matf[9] = 128.0f;
	}

	void glMaterial(float opacity)
	{
		if (opacity<1) {
			glEnable(GL_BLEND);
			glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
			glDepthMask(0);
		}
		float f[4] = {0.0f, 0.0f, 0.0f, opacity};
		memcpy(f, &matf[0], 3*sizeof(float));
		glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT, f );
		memcpy(f, &matf[3], 3*sizeof(float));
		glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE, f );
		memcpy(f, &matf[6], 3*sizeof(float));
		glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR, f );
		glMaterialf( GL_FRONT_AND_BACK, GL_SHININESS, matf[9] );
	}
};