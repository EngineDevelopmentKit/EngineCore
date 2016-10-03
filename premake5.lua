
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

local zefiros = require( "Zefiros-Software/Zefiros-Defaults", "@head" )

workspace "EngineDevelopmentKit"
	
	zpm.uses "Zefiros-Software/CoreLib" 

	zefiros.setDefaults( "engineCore" )
	
	project "Engine"

		kind "WindowedApp"
		flags "WinMain"
	
		configurations { "Debug", "Release", "OptimisedDebug" }
	
		platforms { "x86_64", "x86" }
	
		location( "engineCore/" )
		objdir "bin/obj/"

		vectorextensions "SSE"
		warnings "Extra"
	
		flags {
		"Unicode",
		"C++11"
		}
	
		links "engineCore"
        
		filter "platforms:x86"
			targetdir "bin/x86/"
			debugdir "bin/x86/"
			architecture "x86"
    
		filter "platforms:x86_64"
			targetdir "bin/x86_64/"
			debugdir "bin/x86_64/"
			architecture "x86_64"
        
		filter "*Debug"
			targetsuffix "d"
			defines "DEBUG"

			flags { "Symbols" }
			optimize "Off"
        
		filter "*OptimisedDebug"
			targetsuffix "od"
			flags "LinkTimeOptimization"
			optimize "Speed"

		filter "*Release"
			optimize "Speed"
			defines "NDEBUG"
        
		filter {}
		
		files { 
            "engine/main.cpp", 
            "engine/**.rc"
          } 

	
