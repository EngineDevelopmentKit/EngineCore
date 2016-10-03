
project "CoreLib"

    kind "StaticLib"       

    files {
        "core/src/**.cpp"
    } 

    zpm.export [[
        includedirs "core/include/"
    ]]