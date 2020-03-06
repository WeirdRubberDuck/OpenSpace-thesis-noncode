  var s1 = {
    Anchor: "Earth",
    Pitch: 0.882921E-2,
    Position: [-8.226632E6,-1.596934E7,-5.319145E6],
    Up: [-0.704841E0,0.522800E0,-0.479457E0],
    Yaw: -0.316156E-2
  };
  
  // One side of moon
  var s2 = {
    Anchor: "Moon",
    Pitch: 0.906141E-2,
    Position: [5.427888E6,-3.928011E5,5.243726E5],
    Up: [0.345434E-1,-0.594805E0,-0.803127E0],
    Yaw: 0.191732E-2
  };
  
  // Opposite side of moon
  var s3 = {
    Anchor: "Moon",
    Pitch: 0.009061416611075401,
    Position: [-5241066.5, -1368842.625, 740758.875],
    ReferenceFrame: "Moon",
    Up: [0.008703073486685753, -0.5014886856079102, -0.8651204109191895],
    Yaw: 0.0019173307809978724,
  };
  
  // View the moon in the background, visit two of its sides and then go back to earth. 
  // Key feature: Problematic situations for linear path (moves through the moon)
  var pathSpec = { Instructions: 
    [
      { NavigationState: s1},
      { NavigationState: s2},
      { NavigationState: s3}, 
      { NavigationState: s1},
    ]               
  }; 