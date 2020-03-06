{
  window.pathSpec1 = { Instructions: 
    [
    { Target: "Earth", Duration: 10 }, 
    { Target: "Mars", Duration: 10 }
    ]
  }; 
  
  // To the moon
  var state1 = {
    Anchor: "Moon",
    Pitch: 0.017751405015587807,
    Position: [4473992, -45170.92578125, 530016.5],
    ReferenceFrame: "Moon",
    Up: [-0.061942439526319504, 0.8040016889572144, 0.591391921043396],
    Yaw: 0.02121247723698616,
  };

  // To the other side of the moon
  var state2 = {
    Anchor: "Moon",
    Pitch: 0.04513531178236008,
    Position: [-3503855.25, 1606588, -2329623.75],
    ReferenceFrame: "Moon",
    Up: [-0.08416271954774857, 0.756641685962677, 0.6483902931213379],
    Yaw: 0.042563214898109436,
  };
  
  // To earth
  var state3 = {
    Anchor: "Earth",
    Pitch: 0.0013760050060227513,
    Position: [3983493.25, 12234122, 4682299],
    ReferenceFrame: "Earth",
    Up: [0.6996344923973083, -0.44250595569610596, 0.5609813928604126],
    Yaw: 0.006719366647303104,
  };
  
  window.pathSpec2 = { Instructions: 
    [
    { NavigationState: state1, Duration: 20 },  
    { NavigationState: state2 },                
    { NavigationState: state3 },                
    ]               
  }; 
  
  testPathGenerationButton;
  {
    var spec = window.pathSpec2;
    
    if (!window.connected || !spec) {
      return;
    }
    await window.openspace.autonavigation.generatePath(spec);
  }
}
