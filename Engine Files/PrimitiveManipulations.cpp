////////////////////////////////////////////////
//	Martin Goulet
//	Project: Phase3
//	PrimitiveManipulations.cpp
////////////////////////////////////////////////

/*
	NOTE:	This contains the definitions for the
			external methods found in the namespace
			PrimitiveSpace.
*/

#include "PrimitiveManipulations.h"
using namespace PrimitiveManipulations;

////////////////////////////////////////////////
void PrimitiveManipulations::ExternPrint(const TRI& t_ref)
{
	cout << "TRI:\n";
	FundamentalManipulations::ExternPrint(t_ref.ReturnRef(0));
	FundamentalManipulations::ExternPrint(t_ref.ReturnRef(1));
	FundamentalManipulations::ExternPrint(t_ref.ReturnRef(2));
	cout << "EOF TRI\n";
}
////////////////////////////////////////////////
void PrimitiveManipulations::ExternPrint(const TRISTRIP& pts_ref)
{
	cout << "Printing TRISTRIP:\n";
	for (int i = 0; i < pts_ref.ReturnSiz(); i++)
	{
		FundamentalManipulations::ExternPrint(pts_ref.ReturnRef(i));
	}
	cout << "Printing TRISTRIP complete.\n";
}

////////////////////////////////////////////////
bool PrimitiveManipulations::ExternSplitTri(
									
									
									std::deque<TRI>& dptPosList_ref,
									std::deque<TRI>& dptOnList_ref,
									std::deque<TRI>& dptNegList_ref,
									const TRI& t_ref, const PLANE& p_ref)
{
	//creating temporary VEC3 lists representing set of VEC3S relative to the plane
	std::deque<VEC3> dvNegList;
	std::deque<VEC3> dvOnList;
	std::deque<VEC3> dvPosList;

	//NOTE: Since all polys thrown to this splitting algorithm will be tris, 
	//we will consider triangle cases explicitly.  This explicit algorithm 
	//is hard coded and will not work with any polygons what dont have 
	//a VEC3 count of 3.

	int iFirstRelative = ExternPlanarTristate(t_ref.ReturnRef(0), p_ref, 0.005f);
	int iSecondRelative = ExternPlanarTristate(t_ref.ReturnRef(1), p_ref, 0.005f);
	int iThirdRelative = ExternPlanarTristate(t_ref.ReturnRef(2), p_ref, 0.005f);

	//First VEC3
	switch (iFirstRelative)
	{
	case -1:	//add to negative list
		dvNegList.push_back(t_ref.ReturnRef(0));
		break;
	case 0:		//add to all lists
		dvNegList.push_back(t_ref.ReturnRef(0));
		dvOnList.push_back(t_ref.ReturnRef(0));
		dvPosList.push_back(t_ref.ReturnRef(0));
		break;
	case 1:		//add to positive list
		dvPosList.push_back(t_ref.ReturnRef(0));
		break;
	default:
		//ASSERTION ERROR
		cout << "RELATIVE SWITCH ASSERTION FAILED\n";
	}
	//INTERSECTION TEST BETWEEN FIRST AND SECOND VEC3
	if (iFirstRelative*iSecondRelative == -1)	//Intersection needed
	{
		TWINVEC3 tvFirstSecond(t_ref.ReturnRef(0), t_ref.ReturnRef(1));
		VEC3 vFirstIntersect;
		//calculate intersection
		ExternLinIntersect(vFirstIntersect, tvFirstSecond, p_ref);
		//add intersection point to all lists
		dvNegList.push_back(vFirstIntersect);
		dvOnList.push_back(vFirstIntersect);
		dvPosList.push_back(vFirstIntersect);
	}

	//Second VEC3
	switch (iSecondRelative)
	{
	case -1:	//add to negative list
		dvNegList.push_back(t_ref.ReturnRef(1));
		break;
	case 0:		//add to all lists
		dvNegList.push_back(t_ref.ReturnRef(1));
		dvOnList.push_back(t_ref.ReturnRef(1));
		dvPosList.push_back(t_ref.ReturnRef(1));
		break;
	case 1:		//add to positive list
		dvPosList.push_back(t_ref.ReturnRef(1));
		break;
	default:
		//ASSERTION ERROR
		cout << "RELATIVE SWITCH ASSERTION FAILED\n";
	}
	//INTERSECTION TEST BETWEEN SECOND AND THIRD VEC3
	if (iSecondRelative*iThirdRelative == -1)	//Intersection needed
	{
		TWINVEC3 tvSecondThird(t_ref.ReturnRef(1), t_ref.ReturnRef(2));
		VEC3 vSecondIntersect;
		//calculate intersection
		ExternLinIntersect(vSecondIntersect, tvSecondThird, p_ref);
		//add intersection point to all lists
		dvNegList.push_back(vSecondIntersect);
		dvOnList.push_back(vSecondIntersect);
		dvPosList.push_back(vSecondIntersect);
	}

	//Third VEC3
	switch (iThirdRelative)
	{
	case -1:	//add to negative list
		dvNegList.push_back(t_ref.ReturnRef(2));
		break;
	case 0:		//add to all lists
		dvNegList.push_back(t_ref.ReturnRef(2));
		dvOnList.push_back(t_ref.ReturnRef(2));
		dvPosList.push_back(t_ref.ReturnRef(2));
		break;
	case 1:		//add to positive list
		dvPosList.push_back(t_ref.ReturnRef(2));
		break;
	default:
		//ASSERTION ERROR
		cout << "RELATIVE SWITCH ASSERTION FAILED\n";
	}
	
	//INTERSECTION TEST BETWEEN THIRD AND FIRST VEC3
	if (iThirdRelative*iFirstRelative == -1)	//Intersection needed
	{
		TWINVEC3 tvThirdFirst(t_ref.ReturnRef(2), t_ref.ReturnRef(0));
		VEC3 vThirdIntersect;
		//calculate intersection
		ExternLinIntersect(vThirdIntersect, tvThirdFirst, p_ref);
		//add intersection point to all lists
		dvNegList.push_back(vThirdIntersect);
		dvOnList.push_back(vThirdIntersect);
		dvPosList.push_back(vThirdIntersect);
	}

	//construction of TRIs

	//***TEST***
	/*
	cout << "checking values of VEC3 count in lists:\n";
	cout << "negative list VEC3: " << dvNegList.size() << "\n";
	cout << "coincident list VEC3: " << dvOnList.size() << "\n";
	cout << "positive list VEC3:: " << dvPosList.size() << "\n";
	*/
	//***EOF TEST***

	//negative list
	if (dvNegList.size() == 3)
	{
		TRI pt1(dvNegList.at(0), dvNegList.at(1), dvNegList.at(2));
		dptNegList_ref.push_back(pt1);
	}
	if (dvNegList.size() == 4)
	{
		TRI pt1(dvNegList.at(0), dvNegList.at(1), dvNegList.at(2));
		TRI pt2(dvNegList.at(0), dvNegList.at(2), dvNegList.at(3));
		dptNegList_ref.push_back(pt1);
		dptNegList_ref.push_back(pt2);
	}
	//coincident list
	if (dvOnList.size() == 3)
	{
		TRI pt1(dvOnList.at(0), dvOnList.at(1), dvOnList.at(2));
		dptOnList_ref.push_back(pt1);
	}
	//positive list
	if (dvPosList.size() == 3)
	{
		TRI pt1(dvPosList.at(0), dvPosList.at(1), dvPosList.at(2));
		dptPosList_ref.push_back(pt1);
	}
	if (dvPosList.size() == 4)
	{
		TRI pt1(dvPosList.at(0), dvPosList.at(1), dvPosList.at(2));
		TRI pt2(dvPosList.at(0), dvPosList.at(2), dvPosList.at(3));
		dptPosList_ref.push_back(pt1);
		dptPosList_ref.push_back(pt2);
	}

	return true;
}
////////////////////////////////////////////////
bool PrimitiveManipulations::ExternCalcBarycentric(VEC3& vTarget_ref, 
										   const TWINVEC3& tv_ref, 
										   const TRI& t_ref)
{
	//parallel test
	PLANE pTemp(t_ref.ReturnRef(0), t_ref.ReturnRef(1), t_ref.ReturnRef(2));
	VEC3 vTemp;	//VEC3 to hold intersection of polyplane and ray
	if ( ExternLinIntersect(vTemp, tv_ref, pTemp) )
	{
		//intersection occured and stored into vTemp.

		//creating temporary VEC3s vQ1, vQ2, vR
		VEC3 vQ1(t_ref.ReturnRef(1));
		VEC3 vQ2(t_ref.ReturnRef(2));
		VEC3 vR(vTemp);
		vQ1.InternSub(t_ref.ReturnRef(0));
		vQ2.InternSub(t_ref.ReturnRef(0));
		vR.InternSub(t_ref.ReturnRef(0));
		//calculating matrix determinant
		// fDet = [vQ1^2*vQ2^2 - (vQ1.vQ2)^2]
		float fDet = vQ1.ReturnDot(vQ1)*vQ2.ReturnDot(vQ2);
		fDet -= pow(vQ1.ReturnDot(vQ2),2);
		//simulating matrix multiplications, and storing into fW1 & fW2
		//barycentric coordinates
		//fW1 = vQ2^2*vR.vQ1 - vQ1.vQ2*vR.vQ2
		//fW2 = vQ1^2*vR.vQ2 - vQ1.vQ2*vR.vQ1
		float fW1 = vQ2.ReturnDot(vQ2) * vR.ReturnDot(vQ1) -
					vQ1.ReturnDot(vQ2) * vR.ReturnDot(vQ2);
		float fW2 = vQ1.ReturnDot(vQ1) * vR.ReturnDot(vQ2) -
					vQ1.ReturnDot(vQ2) * vR.ReturnDot(vQ1);
		//divide barycentrics by the determinant
		fW1 = fW1 / fDet;
		fW2 = fW2 / fDet;
		//check if coordinates are valid
		//***test***
		cout << "Values of (fW1,fW2): " << fW1 << ", " << fW2 << ")\n";
		//***eof test***
        if ( (fW1>=0) && (fW2>=0) && (fW1+fW2 <=1) )
		{
			//then the tv_ptr ray intersects with the polygon.
			return true;
		}
		else
		{
			//***test***
			cout << "MISSED\n";
			//***eof test***

			//although the ray intersects with the plane, the
			//intersection is not located inside the polygon itself.
			return false;
		}
	}
	else
	{
		//intersection test failed, returning false to indicate failure.
		cout << "NO INTERSECTION.\n";
		return false;
	}

}
////////////////////////////////////////////////