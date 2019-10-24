# SphereDeformer
A custom deformer in Autodesk maya which can deform any mesh into a sphere with key-able attributes.
Please copy and paste the attached .mll to your maya plugins folder. Generally under C:/ProgramFiles/Autodesk/Maya/bin/plugins.
After that, make sure your pluugin is loaded in the plugin manager.

TO USE :

Select your mesh and run the following MEL command "deformer -type pufferMesh". This should create a new Input "pufferMesh1". You can control the radius of the sphere and the amount of displacement. If the deformer does not work, you need to change the vertex order of your mesh. Try using some sort of vertex reorder technique.

Feel free to use this in any of your projects.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Copyright © Nagaraj Raparthi.
