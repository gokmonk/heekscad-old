// HLine.h

#pragma once
#include "../interface/HeeksObj.h"
#include "../interface/HeeksColor.h"
#include "HGeomObject.h"

class HLine: public HGeomObject{
private:
	HeeksColor color;

public:
	gp_Pnt A, B;

	~HLine(void);
	HLine(const gp_Pnt &a, const gp_Pnt &b, const HeeksColor* col);
	HLine(const HLine &line);

	const HLine& operator=(const HLine &b);

	// HeeksObj's virtual functions
	int GetType()const{return LineType;}
	void glCommands(bool select, bool marked, bool no_color);
	void GetBox(CBox &box);
	const char* GetTypeString(void)const{return "Line";}
	HeeksObj *MakeACopy(void)const;
	void ModifyByMatrix(const double *mat);
	void SetColor(const HeeksColor &col){color = col;}
	const HeeksColor* GetColor()const{return &color;}
	void GetGripperPositions(std::list<double> *list, bool just_for_endof);
	void GetProperties(std::list<Property *> *list);
	bool FindNearPoint(const double* ray_start, const double* ray_direction, double *point);
	void Stretch(const double *p, const double* shift, double* new_position);
	void GetSegments(void(*callbackfunc)(const double *p), double pixels_per_mm, bool want_start_point = true)const;
	int Intersects(const HeeksObj *object, std::list< double > *rl)const;
	bool GetStartPoint(double* pos);
	bool GetEndPoint(double* pos);
	void CopyFrom(const HeeksObj* object){operator=(*((HLine*)object));}

	gp_Lin GetLine()const;
	int Intersects(const gp_Lin &line, std::list< double > *rl)const;
};