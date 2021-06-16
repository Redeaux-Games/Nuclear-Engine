![REDx Engine Logo](coollogo_com-117703856.png "REDx Engine Logo") 
* [Engine features](https://github.com/Redeaux-Games/REDx-Game-Engine/blob/master/FEATURES.md) - A list of all working features.


+ Milestone 0.03 Alpha
	- Complete DemoGame
        - DirectX 12
        - Vulkan
        - OpenGL
        - Async Compute
        - REDAI - Advanced AI algorithm including speech synthesis (module)
        - Cross platform anti-cheat (module)

# To-dos 

  + W.I.P:
    - VirtualCameraVTK (Images to 3d models)(module) 📸
    - Bloom effect (Diligent Module) 🌋
    - ShadowMaps (Diligent Module) 💪
    - Taskflow support 🤯
    - Ray Tracing Support (Diligent Module) 💡
    - Multi-threading support 💪
    - P2P Multi-player support 🎮 (module)
    - Windows release beta (1st version x64, portable) 🪟
    - NPC2PC (NPC to Player Communication - Utilizing STT / TTS to REDAI for NPC response)(module)
    - Support of importing .usd files
	
  + Planned:
    - Mesh Animations (Diligent Module)
    - Basic Editor support
    - P2P Asset Market using a ERC-721 token built-in (game currency module)

  + Planned for next version:
    - Android Support
    - IOS Support
    - IPFS Lobby System (module)
    - Lua Scipting Library
    - XBOX export
    - Playstation export
    - Nintendo Switch export


### Building
The project has three building configuration:

Debug: Which is used in internal engine development.

Checked: Use it if you are developing a game.

Release: Provides maximum performance, use it if you are publishing your game.


Some Dependencies needs to be downloaded and built manually,
we plan to create a completely automated install that will automatically
install the dependencies.

+ __Requirements__
  - Visual Studio 2019
  - CMake

+ __Dependencies__
  - Assimp
  - DiligentEngine
  - DiligentCore
  - DiligentFX
  - DiligentTools
  - FMOD SDK
  - Nvidia PhysX 4.1
  - Freeimage
  - GLFW 
  - Python 3.6+ (REDAI & NPC2PC)
  - Node.js (p2p networking requirement)

System Requirements:
  - Intel I5 or higher / AMD Ryzen 5 or higher
  - 8gb of ram or higher
  - At least 25gb of disk space or more
  - Nvidia gtx 1050 or higher / AMD Radeon 560 or higher
  - Raytracing will require a Nvidia RTX gpu

We plan on getting the core features installed with 
an installers only around 600 to 700 megabytes, 
everything is modular. We plan on releasing for Windows,
MacOS and Linux.

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
