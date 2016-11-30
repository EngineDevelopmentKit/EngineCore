

zpm.plugin "Window"
    
    files {
        "include/**.h",
        "src/**.cpp"
    }
    
    zpm.uses {
        "Zefiros-Software/SFML"
        }

    zpm.export([[
        includedirs "include/"
    ]])