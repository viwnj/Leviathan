function start ()
  AddComponent("Transform", { posX = 730, posY = 20, velX = 0, velY = 0, width = 64, height = 64, scale = 1 })
  AddComponent("Sprite", 
    { isAnimated = true, 
      textureId = "radar", 
      numFrames = 8, 
      animationSpeed = 150, 
      hasDirections = false, 
      isFixed = true 
  })
end

function update ()

end