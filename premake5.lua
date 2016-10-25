
--[[ @cond ___LICENSE___
-- Copyright (c) 2016 Koen Visscher, Paul Visscher and individual contributors.
--
-- Permission is hereby granted, free of charge, to any person obtaining a copy
-- of this software and associated documentation files (the "Software"), to deal
-- in the Software without restriction, including without limitation the rights
-- to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
-- copies of the Software, and to permit persons to whom the Software is
-- furnished to do so, subject to the following conditions:
--
-- The above copyright notice and this permission notice shall be included in
-- all copies or substantial portions of the Software.
--
-- THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
-- IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
-- FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
-- AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
-- LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
-- OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
-- THE SOFTWARE.
--
-- @endcond
--]]

local vsandroid = require( "akaStiX/vsandroid", "@head" )

workspace "EngineDevelopmentKit"
    
    configurations { "Debug", "Release", "OptimisedDebug" }
    
    startproject "Engine"
    objdir "bin/obj/"
    
    vectorextensions "SSE"
    characterset "Unicode"
    warnings "Extra"
    
    flags "C++11"

    filter { "action:vs*" }
        platforms { "x86_64", "x86" }
     
    filter { "action:vs*", "platforms:x86" }
        targetdir "bin/x86/"
        debugdir "bin/x86/"
        architecture "x86"
    
    filter { "action:vs*", "platforms:x86_64" }
        targetdir "bin/x86_64/"
        debugdir "bin/x86_64/"
        architecture "x86_64"
      
    filter "*Debug"
        targetsuffix "d"
        defines "DEBUG"

        symbols "On"
        optimize "Off"
        
    filter "*OptimisedDebug"
        targetsuffix "od"
        symbols "On"
        optimize "Speed"
        
    filter "*Release"
        optimize "Speed"
        defines "NDEBUG"

    filter "action:android"
        targetdir "bin/android/"
        debugdir "bin/android/"
		system "vsandroid"
		architecture "arm"

    filter { "*Release", "system:not linux" }
        flags "LinkTimeOptimization"

    filter { "*OptimisedDebug", "system:not linux" }
        flags "LinkTimeOptimization"
       
    filter {}
    
    project "EngineCore"
     
        targetname "EngineCore"
        location "engine/"
        kind "StaticLib"             
        
        zpm.uses { 
            "Zefiros-Software/CoreLib",
            "Zefiros-Software/SFML",
            "Zefiros-Software/bx",
            "Zefiros-Software/bgfx" 
            }
        
        includedirs "engine/include/"
            
        files { 
           "engine/include/**.hpp",
           "engine/include/**.h",
           "engine/src/**.cpp"
            }

        filter "action:android"
            androidapilevel(21)
            cppstandard "c++11"
		    stl "libc++"

        filter {}
                
    project "Engine"

        kind "WindowedApp"
        location "engine/"
        targetname "Engine" 
    
        links "EngineCore"
        
        zpm.uses { 
            "Zefiros-Software/CoreLib",
            "Zefiros-Software/SFML",
            "Zefiros-Software/bx",
            "Zefiros-Software/bgfx" 
            }
        
        includedirs "engine/include/"
        
        files { 
            "engine/main.cpp", 
            "engine/**.rc"
          } 

        filter "action:vs*"
            kind "WindowedApp"

        filter "action:android"
            kind "SharedLib"
            androidapilevel(21)
            cppstandard "c++11"
		    stl "libc++"

        filter {}

if _ACTION == "android" then
	project "Packaging"

		kind "Packaging"
		
		links {
			"Application",
		}
		
		files {
			"%{sln.location}/res/values/strings.xml",
            "%{sln.location}/assets/**.*",
		}
		
		symbolspath "%{sln.location}/obj/%{cfg.buildcfg}/Application"
end

    
