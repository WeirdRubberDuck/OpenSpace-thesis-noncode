  // Surface pos (norrkoping)
  var state1 = {
    Anchor: "Earth",
    Pitch: -5.827099913702227e-11,
    Position: [3623696.25, 1052259.875, 6178811.5],
    ReferenceFrame: "Earth",
    Up: [-0.8195835947990417, -0.23799316585063934, 0.5211928486824036],
    Yaw: 4.115036367213776e-10
  };
  
  var state2 = {
    Anchor: "Earth",
    Pitch: -6.827080567539667e-11,
    Position: [-12951086, -3339838.75, 7361332],
    ReferenceFrame: "Earth",
    Up: [-0.4576875567436218, -0.154915452003479, -0.8755131959915161],
    Yaw: 4.023609223580138e-10
  };
  
  // Surface pos (an island)
  var state3 = {
    Anchor: "Earth",
    Pitch: -1.0176234854775146e-10,
    Position: [-3573420, 5260148, 1104032.875],
    ReferenceFrame: "Earth",
    Up: [-0.4929982125759125, -0.15523536503314972, -0.8560693264007568],
    Yaw: 3.7770711558415826e-10
  };
  
  var state4 = {
    Anchor: "Earth",
    Pitch: 8.910000515172101e-11,
    Position: [-14012053, 20626032, 4329120.5],
    ReferenceFrame: "Earth",
    Up: [-0.4929982125759125, -0.15523536503314972, -0.8560693264007568],
    Yaw: 2.451310543438723e-10
  };
  
  var pathSpec = { Instructions: 
    [
      { NavigationState: state1 },  
      { NavigationState: state2 },  
      { NavigationState: state3 },  
      { NavigationState: state4 },   
    ] , 
  }; 