# encoding: utf-8
from yade import pack

sp=pack.SpherePack()
## corners of the initial packing
mn,mx=Vector3(0,0,0),Vector3(10,10,10)

## box between mn and mx, avg radius ± ½(20%), 2k spheres
sp.makeCloud(minCorner=mn,maxCorner=mx,rRelFuzz=.2,num=2000)

## create material #0, which will be used as default
O.materials.append(FrictMat(young=15e6,poisson=.4,frictionAngle=.4,density=2600,label='spheres'))
O.materials.append(FrictMat(young=15e6,poisson=.4,frictionAngle=.2,density=2600,label='frictionless'))


## copy spheres from the packing into the scene
## use default material, don't care about that for now
O.bodies.append([utils.sphere(center,rad,material='spheres') for center,rad in sp])
## create walls around the packing
walls=utils.aabbWalls(thickness=.1,material='frictionless')
wallIds=O.bodies.append(walls)

## hope that we got the ids right?!
triax=TriaxialCompressionEngine(
	wall_bottom_id=wallIds[2],
	wall_top_id=wallIds[3],
	wall_left_id=wallIds[0],
	wall_right_id=wallIds[1],
	wall_back_id=wallIds[4],
	wall_front_id=wallIds[5],
	## important! (otherwise it sets inertia to infinity and crashes??)
	internalCompaction=False,
	## define the rest of triax params here
	## see in pkg/dem/PreProcessor/TriaxialTest.cpp:524 etc
	## which are assigned in the c++ preprocessor actually
	sigmaIsoCompaction=50e3,
	sigmaLateralConfinement=50e3,
	max_vel=10,
	strainRate=0.05
)

O.dt=.5*utils.PWaveTimeStep() # initial timestep, to not explode right away

O.engines=[
	ForceResetter(),
	InsertionSortCollider([Bo1_Sphere_Aabb(),Bo1_Box_Aabb()],verletDist=.05),
	InteractionLoop(
		[Ig2_Sphere_Sphere_ScGeom(),Ig2_Box_Sphere_ScGeom()],
		[Ip2_FrictMat_FrictMat_FrictPhys()],
		[Law2_ScGeom_FrictPhys_CundallStrack()]
	),
	GlobalStiffnessTimeStepper(active=1,timeStepUpdateInterval=100,timestepSafetyCoefficient=0.8, defaultDt=O.dt),
	triax,
	# you can add TriaxialStateRecorder and such here…
	NewtonIntegrator(damping=.4)
]



O.saveTmp()
