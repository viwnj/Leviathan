-- The engine expects these two functions to be passed to a Level script
function loadAssets()
  AddTexture("chopper", "./src/assets/images/chopper-spritesheet.png")
  AddTexture("jungle-tilemap", "./src/assets/tilemaps/jungle.png")
  AddTexture("radar", "./src/assets/images/radar.png")
  AddTexture("tank", "./src/assets/images/tank-big-right.png")
  AddTexture("projectile-image", "./src/assets/images/bullet-enemy.png")
  AddFont("Charriot", "./src/assets/fonts/charriot.ttf", 16)
end


-- Here's were we'll initialize our world
-- You should create the layers/entities you will need in here
function start() 
  mapLayer = CreateLayer("TileMapLayer")
  playerLayer = CreateLayer("PlayerLayer")
  UILayer = CreateLayer("UILayer")
  
  CreateTileMap({
    parentLayer = mapLayer,
    textureId = "jungle-tilemap", 
    file = './src/assets/tilemaps/jungle.map',
    scale = 2,
    tileSize = 32,
    mapSizeX = 25,
    mapSizeY = 20
  })
  
  Player = CreateGameEntity({ name = "Player", scriptFile = "./src/assets/scripts/player.lua", layer = playerLayer })
  CreateGameEntity({ name = "Tank1", scriptFile = "./src/assets/scripts/tank1.lua", layer = playerLayer })
  CreateGameEntity({ name ="WorkingProgressText", scriptFile = "./src/assets/scripts/workingProgressText.lua", layer = UILayer })
  CreateGameEntity({ name = "Radar", scriptFile = "./src/assets/scripts/radar.lua", layer = UILayer  })
  -- Handy function to make our global camera follow the Player, you can use this on any entity!
  AttachCameraToEntity(Player);
end