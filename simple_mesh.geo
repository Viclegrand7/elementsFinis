h = 0.05;                         // Characteristic length of a mesh element
Point(1) = {0, 0, 0, h};       // Point construction
Point(2) = {5, 0, 0, h};
Point(3) = {5, 5, 0, h};
Point(4) = {0.8, 5, 0, h};
Point(5) = {0.2, 5, 0, h};
Point(6) = {0, 5, 0, h};
Line(11) = {1,2};              //Lines
Line(12) = {2,3};
Line(13) = {3,4};
Line(14) = {4,5};
Line(15) = {5,6};
Line(16) = {6,1};
Curve Loop(1) = {11,12,13,14,15,16}; // A Boundary
Plane Surface(18) = {1};       // A Surface
Physical Surface(42) = {18};   // Setting a label to the Surface
Physical Curve(97) = {12}; // set physical tag 98 to Curve (=line) 1
Physical Curve(98) = {14};
Physical Curve(99) = {11,13,15,16};