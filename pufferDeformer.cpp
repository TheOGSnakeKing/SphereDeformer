
#include "bulgeDeformer.h"

MTypeId     BulgeDeformer::id(0x00000233);
MObject     BulgeDeformer::aBulgeAmount;
MObject     BulgeDeformer::aradius;

BulgeDeformer::BulgeDeformer()
{
}


BulgeDeformer::~BulgeDeformer()
{
}


void* BulgeDeformer::creator()
{
	return new BulgeDeformer();
}


MStatus BulgeDeformer::deform(MDataBlock& data, MItGeometry& itGeo,
	const MMatrix& localToWorldMatrix, unsigned int geomIndex)
{
	MStatus status;

	MArrayDataHandle hInput = data.outputArrayValue(input, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	status = hInput.jumpToElement(geomIndex);
	MDataHandle hInputElement = hInput.outputValue(&status);
	MObject oInputGeom = hInputElement.child(inputGeom).asMesh();

	MFnMesh fnMesh(oInputGeom, &status);
	CHECK_MSTATUS_AND_RETURN_IT(status);
	MFloatVectorArray normals;
	fnMesh.getVertexNormals(false, normals);

	//MBoundingBox box;
	//MPoint Center = box.center();

	float bulgeAmount = data.inputValue(aBulgeAmount).asFloat();
	float r = data.inputValue(aradius).asFloat();
	float env = data.inputValue(envelope).asFloat();
	MPoint point;
	MPoint cnt(0.0, 0.0, 0.0, 1); //assumes mesh is placed in such a way that the origin is the center of the mesh
	float w;
	for (; !itGeo.isDone(); itGeo.next())
	{
		

		point = itGeo.position(); //Curret vertex on the mesh
		MVector dis = point - cnt; //Vector from center origin to the vertex
		
		double length = dis.length(); //Magnitude of the vector
		MVector direction = dis.normal();
		w = weightValue(data, geomIndex, itGeo.index()); //Direction of the vector
		point = cnt + (direction * ((bulgeAmount*r) + ((1 - bulgeAmount)*length))) * env * w;
		
		itGeo.setPosition(point); //Assigning new location of the vertex
	}

	return MS::kSuccess;
}


MStatus BulgeDeformer::initialize()
{
	MStatus status;

	MFnNumericAttribute nAttr;

	aBulgeAmount = nAttr.create("pufferAmount", "pufferAmount", MFnNumericData::kFloat);
	nAttr.setKeyable(true);
	nAttr.setMin(0.0);
	nAttr.setMax(1.0);
	addAttribute(aBulgeAmount);
	attributeAffects(aBulgeAmount, outputGeom);

	aradius = nAttr.create("radius", "radius", MFnNumericData::kFloat);
	nAttr.setKeyable(true);
	addAttribute(aradius);
	attributeAffects(aradius, outputGeom);


	MGlobal::executeCommand("makePaintable -attrType multiFloat -sm deformer pufferMesh weights;");

	return MS::kSuccess;
}
