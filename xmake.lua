set_xmakever("2.8.2")
set_project("STCampfireSync")
set_version("2.0.3")
set_languages("c++23")
set_warnings("allextra")
set_encodings("utf-8")

add_rules("mode.debug", "mode.release")

-- Keep release PDBs beside the DLL for useful crash stacks.
if is_mode("release") then
    set_symbols("debug")
end

-- CommonLibSSE-NG checkout next to this repository, with the Skyrim 1.7.x patch applied.
includes("../CommonLibSSE-NG")

target("STCampfireSync")
    add_deps("commonlibsse-ng")
    add_rules("commonlibsse-ng.plugin", {
        name = "STCampfireSync",
        author = "DJLegends",
        description = "Campfire sync for Skyrim Together (Plugin API V1)",
        options = { address_library = true }
    })
    add_files("src/STCampfireSync/*.cpp")
    add_includedirs("include")
    add_cxxflags("cl::/wd4100", "cl::/wd4200", "cl::/wd4201")
target_end()
