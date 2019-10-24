
#include "bulgeDeformer.h"


#include <maya/MFnPlugin.h>

MStatus initializePlugin(MObject obj)
{
	MStatus status;

	MFnPlugin fnPlugin(obj, "SnakeKing", "1.0", "Any");

	status = fnPlugin.registerNode("pufferMesh",
		BulgeDeformer::id,
		BulgeDeformer::creator,
		BulgeDeformer::initialize,
		MPxNode::kDeformerNode);
	CHECK_MSTATUS_AND_RETURN_IT(status);


	return MS::kSuccess;
}


MStatus uninitializePlugin(MObject obj)
{
	MStatus status;

	MFnPlugin fnPlugin(obj);

	status = fnPlugin.deregisterNode(BulgeDeformer::id);
	CHECK_MSTATUS_AND_RETURN_IT(status);

	return MS::kSuccess;
}