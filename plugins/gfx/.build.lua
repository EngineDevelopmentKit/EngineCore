

zpm.plugin "GFX"
    
    files {
        "include/**.h",
        "src/**.cpp"
    }
    
    zpm.uses { 
        "Zefiros-Software/bx",
        "Zefiros-Software/bgfx",
        "EDK/Window"
        }

    zpm.export([[
        includedirs "include/"
    ]])