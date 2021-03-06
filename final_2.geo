h = 0.0001;                     // Characteristic length of a mesh element

Point(1) = {0, 0, 0, h};

//FENETRE 1
Point(2) = {0, 0.1 , 0, h};
Point(3) = {0, 0.3 , 0, h};


//CHAUFFAGE 1
Point(4) = {0, 0.45 , 0, h};
Point(5) = {0, 0.55, 0, h};


//MUR SALON CHAMBRE
Point(6) = {0, 0.65 , 0, h};
Point(7) = {0.08, 0.65 , 0, h};
Point(8) = {0.08, 0.66 , 0, h};
Point(9) = {0, 0.66 , 0, h};

//FENETRE CHAMBRE
Point(10) = {0, 0.75, 0, h};
Point(11) = {0, 0.90, 0, h};

Point(12) = {0, 1, 0, h};   
Point(13) = {0.3, 1, 0, h}; 

//MUR CHAMBRE + SALLE DE BAIN + SALON + RADIATEUR CHAMBRE ET SDB

Point(14) = {0.3, 0.95, 0, h}; 
Point(15) = {0.30, 0.85, 0, h}; 
Point(16) = {0.30, 0.66, 0, h};  
Point(17) = {0.18, 0.66, 0, h};  
Point(18) = {0.18, 0.65, 0, h};  
Point(19) = {0.35, 0.65, 0, h};  
Point(20) = {0.35, 0.66, 0, h};  
Point(21) = {0.31, 0.66, 0, h};
Point(22) = {0.31, 0.75, 0, h};
Point(23) = {0.31, 0.85, 0, h};
Point(24) = {0.31, 1, 0, h};  


Point(25) = {0.50, 1, 0, h};

//FENETRE SALLE DE BAIN
Point(26) = {0.50, 0.85, 0, h};
Point(27) = {0.50, 0.75, 0, h};

//MUR SDB-SALON
Point(28) = {0.50, 0.66 , 0, h};
Point(29) = {0.45, 0.66 , 0, h};
Point(30) = {0.45, 0.65 , 0, h};
Point(31) = {0.50, 0.65 , 0, h};

//PORTE 
Point(32) = {0.50, 0.50, 0, h};
Point(33) = {0.50, 0.40, 0, h};

Point(34) = {0.50, 0.30, 0, h};

//RADIATEUR SALON
Point(35) = {0.55, 0.30, 0, h};
Point(36) = {0.65, 0.30, 0, h};


//MUR SALON CUISINE
Point(37) = {0.70,0.30,0,h};
Point(38) = {0.70,0.05,0,h};
Point(39) = {0.71,0.05,0,h};
Point(40) = {0.71,0.30,0,h};
//FENETRE CUISINE
Point(41) = {0.81,0.30,0,h};
Point(42) = {0.91,0.30,0,h};

Point(43) = {1, 0.30, 0, h};

//RADIATEUR CUISINE
Point(44) = {1, 0.25, 0, h};
Point(45) = {1, 0.15, 0, h};
Point(46) = {1, 0, 0, h};

//FENETRE SALON
Point(47) = {0.30, 0, 0, h};
Point(48) = {0.10, 0, 0, h};



Line(1) = {1,2};            //Lines
Line(2) = {2,3};
Line(3) = {3,4};
Line(4) = {4,5};
Line(5) = {5,6};
Line(6) = {6,7};
Line(7) = {7,8};
Line(8) = {8,9};
Line(9) = {9,10};
Line(10) = {10,11};
Line(11) = {11,12};
Line(12) = {12,13};
Line(13) = {13,14};
Line(14) = {14,15};
Line(15) = {15,16};
Line(16) = {16,17};
Line(17) = {17,18};
Line(18) = {18,19};
Line(19) = {19,20};
Line(20) = {20,21};
Line(21) = {21,22};
Line(22) = {22,23};
Line(23) = {23,24};
Line(24) = {24,25};
Line(25) = {25,26};
Line(26) = {26,27};
Line(27) = {27,28};
Line(28) = {28,29};
Line(29) = {29,30};
Line(30) = {30,31};
Line(31) = {31,32};
Line(32) = {32,33};
Line(33) = {33,34};
Line(34) = {34,35};
Line(35) = {35,36};
Line(36) = {36,37};
Line(37) = {37,38};
Line(38) = {38,39};
Line(39) = {39,40};
Line(40) = {40,41};
Line(41) = {41,42};
Line(42) = {42,43};
Line(43) = {43,44};
Line(44) = {44,45};
Line(45) = {45,46};
Line(46) = {46,47};
Line(47) = {47,48};
Line(48) = {48,1};

Physical Curve(97) = {2,10,26,32,41,47};	//DIRICHLET FROID(FENETRE)
Physical Curve(98) = {4,14,22,35,44};	//DIRICHLET CHAUD(RADIATEUR)
Physical Curve(99) = {1,3,5,6,7,8,9,11,12,13,15,16,17,18,19,20,21,23,24,25,27,28,29,30,31,33,34,36,37,38,39,40,42,43,45,46,48};	//NEUMANN (LE RESTE)

Curve Loop(1) = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48};
Plane Surface(1) = {1};     // A Surface

Physical Surface(1) = {1}; // Setting a label to the Surface
//Physical Surface(2) = {2}; 
