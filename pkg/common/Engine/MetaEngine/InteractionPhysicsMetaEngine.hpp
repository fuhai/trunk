/*************************************************************************
*  Copyright (C) 2004 by Olivier Galizzi                                 *
*  olivier.galizzi@imag.fr                                               *
*                                                                        *
*  This program is free software; it is licensed under the terms of the  *
*  GNU General Public License v2 or later. See file LICENSE for details. *
*************************************************************************/

#ifndef INTERACTIONPHYSICSMETAENGINE_HPP
#define INTERACTIONPHYSICSMETAENGINE_HPP 


#include<yade/core/MetaDispatchingEngine2D.hpp>
#include<yade/lib-multimethods/DynLibDispatcher.hpp>
#include<yade/core/PhysicalParameters.hpp>
#include<yade/core/Interaction.hpp>
#include "InteractionPhysicsEngineUnit.hpp"

class InteractionPhysicsMetaEngine : 	public MetaDispatchingEngine2D
					<	
						PhysicalParameters,					// base classe for dispatch
						PhysicalParameters,					// base classe for dispatch
						InteractionPhysicsEngineUnit,				// class that provides multivirtual call
						void,							// return type
						TYPELIST_3(	  const shared_ptr<PhysicalParameters>&	// arguments
								, const shared_ptr<PhysicalParameters>&
								, const shared_ptr<Interaction>&
							  )
					>
{		
	public :
		virtual void action(Body* body);

	REGISTER_CLASS_NAME(InteractionPhysicsMetaEngine);
	REGISTER_BASE_CLASS_NAME(MetaDispatchingEngine2D);
};

REGISTER_SERIALIZABLE(InteractionPhysicsMetaEngine,false);

#endif //  INTERACTIONPHYSICSMETAENGINE_HPP

