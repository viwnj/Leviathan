function start ()
  AddComponent("Transform", { posX = 90 , posY = 495, velX = 0, velY = 0, width = 32, height = 32, scale = 1 })
  AddComponent("Sprite", { textureId = "tank" })
  AddComponent("BoxCollider", { colliderTag = "ENEMY", posX = 90, posY = 495, w = 32, h = 32, showDebugUI = true })
end

function OnCollision ()
  print('a')
end