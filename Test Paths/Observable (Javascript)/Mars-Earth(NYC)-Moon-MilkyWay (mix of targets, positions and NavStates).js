  // Milky way
  var state = {
    Anchor: "Earth",
    Pitch: -0.1618332862854004,
    Position: [393664147028082400000, 868043988008968400000, 371178729619784200000],
    ReferenceFrame: "Root",
    Up: [-0.36321815848350525, -0.22218404710292816, 0.9048241972923279],
    Yaw: -0.14001649618148804
  }
  
  var pathSpec = { Instructions: 
    [
      { Target: "Mars", Duration: 10 },
      { Target: "Earth", Duration: 10, Position: [1547175.13, -5372715.00, 4814259.00] },  // NYC
      { Target: "Moon" }, 
      { NavigationState: state, Duration: 20 }
    ]               
  }; 