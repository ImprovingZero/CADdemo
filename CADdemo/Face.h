#pragma once
#include"item.h"
#include"geometry.h"
namespace geometry
{
	//class Face;
	//using FacIt = std::list<Face>::iterator;

	class Face
	{
	private:
		Face* _next;
		Face* _prev;
		Solid* _solid;
		Loop* _loop;
	public:
		Face(Solid* sd, Vertex* v);
		Face(Solid* sd, Loop* lp);
		~Face();

		Face* extrude(vec3 dir);
		Face* kfmrh(Face* cf); // cull cf in this

		Face* insertListAfter(Face* f1, Face* f2 = nullptr); //this->he1->...->he2->next
		Face* insertListBefore(Face* f1, Face* f2 = nullptr); //prev->he1->...->he2->this
		//Face* setCircleWith(Face* he); //set: this->he->this
		Face* linkAfter(Face* he); //set: this->he

		virtual void travelOutput(int x) const;
		virtual const GeoType getType() const { return FACE; }
		Solid* getSolid() const { return _solid; }
		Face* getNext() const { return _next; }
		Face* getPrev() const { return _prev; }
		Loop* getFirstLoop() const { return _loop; }
		Loop* operator[](int i) const;
		void setLoop(Loop* lp) { _loop = lp; }
	};

}

