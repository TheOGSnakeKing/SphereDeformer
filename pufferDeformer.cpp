
#include "bulgeDeformer.h"

MTypeId     BulgeDeformer::id(0x00000233);
MObject     BulgeDeformer::aBulgeAmount;


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

	float bulgeAmount = data.inputValue(aBulgeAmount).asFloat();
	float env = data.inputValue(envelope).asFloat();
	MPoint point;
	float w;
	for (; !itGeo.isDone(); itGeo.next())
	{
		w = weightValue(data, geomIndex, itGeo.index());

		point = itGeo.position();

		point += normals[itGeo.index()] * bulgeAmount * w * env;

		itGeo.setPosition(point);
	}

	return MS::kSuccess;
}


MStatus BulgeDeformer::initialize()
{
	MStatus status;

	MFnNumericAttribute nAttr;

	aBulgeAmount = nAttr.create("bulgeAmount", "bulgeAmount", MFnNumericData::kFloat);
	nAttr.setKeyable(true);
	addAttribute(aBulgeAmount);
	attributeAffects(aBulgeAmount, outputGeom);

	MGlobal::executeCommand("makePaintable -attrType multiFloat -sm deformer bulgeMesh weights;");

	return MS::kSuccess;
}
