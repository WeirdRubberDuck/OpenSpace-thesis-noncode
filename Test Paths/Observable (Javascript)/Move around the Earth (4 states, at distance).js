  var state1 = {
    Anchor: "Earth",
    Pitch: -7.415118519205066e-11,
    Position: [13202719, 3833845.5, 22512130],
    ReferenceFrame: "Earth",
    Up: [-0.8195835947990417, -0.23799316585063934, 0.5211928486824036],
    Yaw: 6.734888757797819e-10
  };

  var state2 = {
    Anchor: "Earth",
    Pitch: 0.0000484633055748418,
    Position: [-9037744, 25292246, 2821032.25],
    ReferenceFrame: "Earth",
    Up: [-0.8474732041358948, -0.3475807309150696, 0.40121909976005554],
    Yaw: 0.00011271261610090733
  };
  
  var state3 = {
    Anchor: "Earth",
    Pitch: 0.000048463269195053726,
    Position: [-13321788, 12692.3173828125, -23491842],
    ReferenceFrame: "Earth",
    Up: [-0.7892330884933472, -0.420719712972641, 0.44733211398124695],
    Yaw: 0.00011271255789324641
  };
  
  var state4 = {
    Anchor: "Earth",
    Pitch: -2.571026769260243e-8,
    Position: [-23861726, 758273.1875, -11218245],
    ReferenceFrame: "Earth",
    Up: [0.4198266863822937, -0.11255178600549698, -0.9005984663963318],
    Yaw: -3.3561080581279157e-9
  };
  
  var pathSpec = { Instructions: 
    [
      { NavigationState: state1 },  
      { NavigationState: state2 },  
      { NavigationState: state3 },  
      { NavigationState: state4 },  
    ] , 
  }; 