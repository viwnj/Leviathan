function start ()
  AddComponent("Transform", { posX = 90, posY = 90, velX = 0, velY = 0, width = 32, height = 32, scale = 1 })
  AddComponent("Sprite", { isAnimated = true, textureId = "chopper", numFrames = 2, animationSpeed = 100, hasDirections = true, isFixed = false })
  AddComponent("KeyboardControl", { upKey = "w", rightKey ="d", downKey = "s", leftKey = "a", shootKey = "space" })
  AddComponent("BoxCollider", { colliderTag = "PLAYER", posX = 90, posY = 90, w = 32, h = 32, showDebugUI = true })
end

function update ()
  print("Hello I'm the updater function")
end