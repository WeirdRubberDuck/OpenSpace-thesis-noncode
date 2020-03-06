{
  // Olympus Mons
  var ins1 = { Target: "Mars", Position: [-2883015.00, -3006380.25, 1405841.25] };
  
  // Norrköping
  var ins2 = { Target: "Earth", Position: [3692883.50, 1072065.00, 6296840.00] };
  
  var spec = { Instructions: 
    [ ins2, ]
  };
      
  testGoToButton;
  {
    if (!window.connected) {
      return;
    }
    await window.openspace.autonavigation.generatePath(spec);
  }
}