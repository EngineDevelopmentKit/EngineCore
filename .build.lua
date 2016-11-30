
project "EngineCore"
    
    targetname "EngineCore"
    location "engine/"
    kind "StaticLib"
    
    zpm.uses { 
        "Zefiros-Software/CoreLib" 
        }
    
    zpm.export([[
        includedirs "engine/include/"
    ]])

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

    plugins.linkthis()
            
project "Engine"

    kind "WindowedApp"
    location "engine/"
    targetname "Engine" 

    links "EngineCore"
    
    zpm.uses { 
        "Zefiros-Software/CoreLib"
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

    plugins.uses()

if _ACTION == "android" then
	project "Packaging"

		kind "Packaging"
		
		links {
			"Application"
		}
		
		files {
			"%{sln.location}/res/values/strings.xml",
            "%{sln.location}/assets/**.*"
		}
		
		symbolspath "%{sln.location}/obj/%{cfg.buildcfg}/Application"
end