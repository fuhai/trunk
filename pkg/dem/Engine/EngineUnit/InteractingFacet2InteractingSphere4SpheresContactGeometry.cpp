/*************************************************************************
*  Copyright (C) 2008 by Sergei Dorofeenko				 *
*  sega@users.berlios.de                                                 *
*                                                                        *
*  This program is free software; it is licensed under the terms of the  *
*  GNU General Public License v2 or later. See file LICENSE for details. *
*************************************************************************/

#include"InteractingFacet2InteractingSphere4SpheresContactGeometry.hpp"
#include<yade/pkg-dem/SpheresContactGeometry.hpp>
#include<yade/pkg-common/InteractingSphere.hpp>
#include<yade/pkg-common/InteractingFacet.hpp>

#include<yade/lib-base/yadeWm3Extra.hpp>

CREATE_LOGGER(InteractingFacet2InteractingSphere4SpheresContactGeometry);

InteractingFacet2InteractingSphere4SpheresContactGeometry::InteractingFacet2InteractingSphere4SpheresContactGeometry() 
{
	shrinkFactor=0;
	hasShear=false;
}

void InteractingFacet2InteractingSphere4SpheresContactGeometry::registerAttributes()
{	
    InteractionGeometryEngineUnit::registerAttributes();
    REGISTER_ATTRIBUTE(shrinkFactor);
    REGISTER_ATTRIBUTE(hasShear);
}

bool InteractingFacet2InteractingSphere4SpheresContactGeometry::go(const shared_ptr<InteractingGeometry>& cm1,
							const shared_ptr<InteractingGeometry>& cm2,
							const Se3r& se31,
							const Se3r& se32,
							const shared_ptr<Interaction>& c)
{
	InteractingFacet*   facet = static_cast<InteractingFacet*>(cm1.get());
	/* could be written as (needs to be tested):
	 * Vector3r cl=se31.orientation.Conjugate()*(se32.position-se31.position);
	 */
	Matrix3r facetAxisT; se31.orientation.ToRotationMatrix(facetAxisT); 
	Matrix3r facetAxis = facetAxisT.Transpose();
	// local orientation
	Vector3r cl = facetAxis*(se32.position - se31.position);  // "contact line" in facet-local coords

	//
	// BEGIN everything in facet-local coordinates
	//

	Vector3r normal = facet->nf;
	Real L = normal.Dot(cl);

	int contactFace=0; // temp to save what will be maybe needed for new contact
	//assert((c->interactionGeometry&&c->isReal)||(!c->interactionGeometry&&!c->isReal));
	if(c->interactionGeometry){ // contact already exists, use old data here
		contactFace=YADE_CAST<SpheresContactGeometry*>(c->interactionGeometry.get())->facetContactFace;
		// determinate contact on negative side: reverse quantities
		if(contactFace<0){normal=-normal; L=-L;}
		// indeterminate contact on negative side: set to -1; if edge, will be reset to 0 below
		else if (contactFace==0 && L<0) { normal=-normal; L=-L; contactFace=-1; }
		// indeterminate and is on the positive side: set to 1; if edge, will be reset to 0 below
		else if(contactFace==0 && L>0) {contactFace=1;}
	} else {
		if (L<0) { normal=-normal; L=-L; contactFace=-1;} // new contact on the negative face, reverse and save that information so that since now this contact is always reversed
		else contactFace=1;
	}

	Real sphereRadius = static_cast<InteractingSphere*>(cm2.get())->radius;
	if (L>sphereRadius && !c->isReal)  return false; // no contact, but only if there was no previous contact; ortherwise, the constitutive law is responsible for setting Interaction::isReal=false

	Vector3r cp = cl - L*normal;
	const Vector3r* ne = facet->ne;
	
	Real penetrationDepth=0;
	
	Real bm = ne[0].Dot(cp);
	int m=0;
	for (int i=1; i<3; ++i)
	{
		Real b=ne[i].Dot(cp);
		if (bm<b) {bm=b; m=i;}
	}

	Real sh = sphereRadius*shrinkFactor;
	Real icr = facet->icr-sh;

	if (icr<0)
	{
		LOG_WARN("a radius of a facet's inscribed circle less than zero! So, shrinkFactor is too large and would be reduced to zero.");
		shrinkFactor=0;
		icr = facet->icr;
		sh = 0;
	}


	if (bm<icr) // contact with facet's surface
	{
		penetrationDepth = sphereRadius - L;
		normal.Normalize();
	}
	else
	{
		// edge or vertex contact: become indeterminate with respect to face
		contactFace=0;
		cp = cp + ne[m]*(icr-bm);
		if (cp.Dot(ne[(m-1<0)?2:m-1])>icr) // contact with vertex m
//			cp = facet->vertices[m];
			cp = facet->vu[m]*(facet->vl[m]-sh);
		else if (cp.Dot(ne[m=(m+1>2)?0:m+1])>icr) // contact with vertex m+1
//			cp = facet->vertices[(m+1>2)?0:m+1];
			cp = facet->vu[m]*(facet->vl[m]-sh);
		normal = cl-cp;
		penetrationDepth = sphereRadius - normal.Normalize();
	}

	//
	// END everything in facet-local coordinates
	//

	if (penetrationDepth>0 || c->isReal)
	{
		shared_ptr<SpheresContactGeometry> scm;
		if (c->interactionGeometry)
			scm = YADE_PTR_CAST<SpheresContactGeometry>(c->interactionGeometry);
		else
			{ scm = shared_ptr<SpheresContactGeometry>(new SpheresContactGeometry());
			scm->facetContactFace=contactFace; }
	  
		normal = facetAxisT*normal; // in global orientation
		scm->contactPoint = se32.position - (sphereRadius-0.5*penetrationDepth)*normal; 
		scm->normal = normal; 
		scm->penetrationDepth = penetrationDepth;
		scm->radius1 = 2*sphereRadius;
		scm->radius2 = sphereRadius;

		if (!c->interactionGeometry)
			c->interactionGeometry = scm;

		if(hasShear){
			scm->hasShear=true;
			// fictive center of the sphere representing the facet in the sphere-sphere contact
			scm->pos1=scm->contactPoint-(scm->radius1-.5*penetrationDepth)*normal; scm->pos2=se32.position;
			scm->ori1=se31.orientation; scm->ori2=se32.orientation;
			if(c->isNew){
				scm->d0=scm->radius1+scm->radius2-penetrationDepth;
				scm->d1=scm->radius1-.5*penetrationDepth; scm->d2=scm->radius2-.5*penetrationDepth;
				scm->d0fixup=-scm->radius1-.5*penetrationDepth;
				// quasi-constants
				scm->cp1rel.Align(Vector3r::UNIT_X,se31.orientation.Conjugate()*normal);
				scm->cp2rel.Align(Vector3r::UNIT_X,se32.orientation.Conjugate()*(-normal));
				scm->cp1rel.Normalize(); scm->cp2rel.Normalize();
			}
			TRVAR2(scm->contPtInTgPlane1(),scm->contPtInTgPlane2());
		}

		return true;
	}
	return false;
}


bool InteractingFacet2InteractingSphere4SpheresContactGeometry::goReverse(	const shared_ptr<InteractingGeometry>& cm1,
								const shared_ptr<InteractingGeometry>& cm2,
								const Se3r& se31,
								const Se3r& se32,
								const shared_ptr<Interaction>& c)
{
	assert(c->isNew);
	c->swapOrder();
	//LOG_WARN("Swapped interaction order for "<<c->getId2()<<"&"<<c->getId1());
	return go(cm2,cm1,se32,se31,c);
}

YADE_PLUGIN();
