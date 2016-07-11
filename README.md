# OpenKODE Framework
This framework based on OpenKODE focuses on easy development of games, location based application, iteractive books, and graphical applications. The framework contains useful open source libraries, tutorials, and sample applications.

#### [OpenKODE: Khronos Open Development Environment](https://www.khronos.org/openkode/)
OpenKODE® is a royalty-free, open standard that combines a set of native APIs to increase source portability for rich media and graphics applications. OpenKODE reduces mobile platform fragmentation by providing a cross-platform API for accessing operating system resources, and a media architecture for portable access to advanced mixed graphics acceleration.

### Directory Structure
```
+ 01_Develop
  + lib<Name>: Library souces 
    + Build
      - Win32-vc2015: Visual Studio 2015 Project 
    - Source
+ 02_Library
  + Include: Library header files
    - XM<Name>
  - Licence: Library licence files
  + Platform: Compiled libaries after build
    - Win32
    - iOS
    - Android
    - Linux
    - Tizen
    - Bada
+ 03_Tutorial
  + <Name>
    + Binary: Excuted files after build
      - Win32
    + Build
      - Win32-vc2015: Visual Studio 2015 Project
    - Data: User saved files
    - Resource: Application resource files
    - Source: Application source files
+ 04_Sample
+ 05_Conformance
+ 06_Document
+ 07_Project
```

### Libraries
| Type | Name | Description |
| --- | --- | --- |
| **Core** | OpenKODE | *Cross-platform middle layer* |
| **Rendering** | Cocos2D *v2, v3* | *2D Game engine* |
| | Ogre3D | *3D Rendering engine* |
| | Irrilicht3D | *3D Rendering engine* |
| | M3G | *3D Rendering library* |
| | XMGraphics | *3D Rendering library* |
| | Glues | *OpenGL Utility library* |
| **Computer Vision** | OpenCV | *Imaging computer vision framework* |
| **Video Processing** | FFmpeg | *Video processing library* |
| **Physics** | Box2D | *C++ Style 2D Physics* |
|             | Chipmunk | *C Style 2D Physics* |
|             | Bullets | *3D Physics* |
| **Network** | Curl | *URL communication* |
|             | Enet | *UDP communication* |
|             | Websockets | *Socket communication* |
| **Parser**  | XML2 | *XML parser* |
|             | TinyXML *v1, v2* | *Simple XML parser* |
|             | Lua | *Lua parser* |
|             | JSonCpp | *Json parser* |
| **Compression** | Zlib | *Commpression library* |
|                 | ZZip | *Zip library* |
| **Font** | FreeType | *True Type font library* |
| **Math** | Kazmath | *Vector, Matrix math library* |
| **DB** | Sqlite | *Sql client library* |

### Tutorials
| Content | Description |
| --- | --- |
| **OpenKODE** | *Core layer tutorials* |
| **Cocos2D** *v2* | *2D game engine tutorials* |
| **Cocos2D** *v3* | *2D game engine tutorials* |
| **Cocos2D** *Javascript* | *2D game engine tutorials* |
| **Cocos2D** *Lua* | *2D game engine tutorials* |
| **Cocos2D** *Cook Book* | *Advanced tutorials* |
| **Irrlicht3D** | *3D rendering engine tutorials* |
| **OpenCV** | *Computer vision framework tutorials* |
| **Ogre3D** | *3D rendering engine tutorials* |

### Samples
| Content | Description |
| --- | --- |
| **Angry Bird Like** | |
| **Angry Ninjas** | *Starter Kit, Angry Bird Like* |
| **Battle City** | *Game Center's old tank* |
| **Beat Bean** | |
| **Billards** | |
| **Blue Defence** | 
| **Bomber Man** | | 
| **Box2D Running Man** | *Cookie Run Like* |
| **Brick Ex** | |
| **Climbers** | |
| **Simple Game** | | 
| **Cocos Studio Example** | |
| **Cut Cut Cut** | *Fruit Ninja Like* |
| **Cut The Rope** | |
| **Fishing Joy Like** | |
| **Flying Plane** | |
| **Galaga** | |
| **Grenade** | |
| **Kawaz Buster** | *Pretty Game* |
| **Knight Fighter** | *Isometic style* |
| **Cocos2D & Irricht3D** | *Engine Integration Demo* |
| **Cocos2D & Ogre3D** | *Engine Integration Demo* |
| **Moon Warrior** | *Ported From Html5* |
| **Panorama** | *Street view demo* |
| **Ripple Effect** | *Ripple Effect demo* |
| **SBox Man** | |
| **Specal Task** | *Old Popular Action Game* |
| **Super Fashion Puzzle** | |
| **Super Mario Click** | *Simple Physics Example* |
| **The Adventure of Mira** | *Prety Game* |
| **Tower Defence** | *Waypoint sample* |
| **Zombie** | *Engine Integration Demo* |

### Projects 
| Type | Name | Status |
| --- | --- | --- | 
| **Cut Firewood** | *Casual Game* | `published` |
| **Gostop** | *Korean Card Game* | `published` |
| **Knight Fighter** | *Action Shooting Game* | `imcomplete` |
| **Monster Battle Casino** | *Betting Game* | `published` |
| **Uptris** | *Fliped Tetris* | `published` |
| **Vocano** | *Simple Game* | `complete` |

### Contact
* Homepage: [http://mcodegeeks.com](http://mcodegeeks.com)
* Email: [mcodegeeks@gmail.com](mailto:mcodegeeks@gmail.com)
 
### Licence
Cocos2d-x is licensed under the [MIT License](https://opensource.org/licenses/MIT).
