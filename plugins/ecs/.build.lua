

zpm.plugin "ECS"
    
    files {
        "include/**.h",
        "src/**.cpp"
    }

    zpm.export([[
        includedirs "include/"
    ]])