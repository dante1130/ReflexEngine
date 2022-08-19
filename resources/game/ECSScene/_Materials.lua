Model.load_model("cat", "models/12221_Cat_v1_l3.obj")
Model.load_model("boat", "models/boat1obj.obj")
Model.load_model("lighthouse", "models/Beacon.obj")
Model.load_model("big_arrow", "models/BigArrow.obj")
Model.load_model("TheDen", "models/TheDen.obj")
Model.load_model("GlassInScene", "models/Glass.obj")


Md2.load_md2_model("duck", "models/DuckPersonNew.md2")


Texture.load_texture("water", "textures/water.png")
Texture.load_texture("sand", "textures/sand.jpg")
Texture.load_texture("rock", "textures/rock.jpg")
Texture.load_texture("snow", "textures/snow.jpg")
Texture.load_texture("grass", "textures/grass2.jpg")
Texture.load_texture("credits", "textures/reflexbullet.png")
Texture.load_texture("duck", "textures/DuckPerson.png")
Texture.load_texture("Chair", "textures/chair.jpg")
Texture.load_texture("DarkGlass", "textures/DarkGlass.png")
Texture.load_texture("GenericWalls", "textures/GenericWalls.png")
Material.load_material("shiny", 256.0, 4.0)


Audio.load_audio("duckandcover", "sounds/gamefast.wav")


Terrain.load_terrain("terrain", "textures/newheightmap.png")


Skybox.load_skybox("nightsky", {
	right = "textures/skyboxes/nightsky/nightsky_rt.tga",
	left = "textures/skyboxes/nightsky/nightsky_lf.tga",
	top = "textures/skyboxes/nightsky/nightsky_up.tga",
	bottom = "textures/skyboxes/nightsky/nightsky_dn.tga",
	front = "textures/skyboxes/nightsky/nightsky_bk.tga",
	back = "textures/skyboxes/nightsky/nightsky_ft.tga"
})
Mesh.load_mesh("water",
	{
		-10.0, 0.0, -10.0, 0.0, 0.0, 0.0, -1.0, 0.0,
		10.0, 0.0, -10.0, 100.0, 0.0, 0.0, -1.0, 0.0,
		-10.0, 0.0, 10.0, 0.0, 100.0, 0.0, -1.0, 0.0,
		10.0, 0.0, 10.0, 100.0, 100.0, 0.0, -1.0, 0.0
	},
	{
		0, 2, 1, 1, 2, 3, 0, 1, 2, 1, 3, 2
	}
)
