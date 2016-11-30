
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

vsandroid = require( "akaStiX/vsandroid", "@head" )
plugins = require( "Zefiros-Software/Plugins", "@head" )

workspace "EngineDevelopmentKit"
    
    configurations { "Debug", "Release", "OptimisedDebug" }
    
    startproject "Engine"
    
    vectorextensions "SSE"
    characterset "Unicode"
    warnings "Extra"
    flags "C++11"

    objdir "bin/obj/"
    targetdir "bin/"
    debugdir "bin/"
    platforms "x86_64"
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

    
dofile(".build.lua")