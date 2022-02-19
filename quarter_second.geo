SetFactory("OpenCASCADE");

h = 0.0025;                     // Characteristic length of a mesh element

Point(0) = {0,0,0,h}; 
Point(1) = {1,0,0,h}; 
Point(2) = {1,1,0,h};
Point(3) = {0,1,0,h}; 

Line(0) = {1,2};
Line(1) = {2,3};
Line(2) = {3,0};
Line(3) = {0,1};

Curve Loop(45) = {0, 1, 2, 3}; 
Plane Surface(46) = {45}; 
Physical Surface(47) = {46};
Physical Curve(97) = {0};
Physical Curve(98) = {2}; 
Physical Curve(99) = {1, 3};