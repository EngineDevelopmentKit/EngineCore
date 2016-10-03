
project "EngineCore"

    kind "StaticLib"       

    files {
        "core/src/**.cpp"
    } 

    zpm.export [[
        includedirs "core/include/"
        flags "C++11"
    ]]
	
	