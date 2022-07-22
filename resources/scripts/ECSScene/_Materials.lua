Model.load_model("cat", "models/12221_Cat_v1_l3.obj")
Model.load_model("boat", "models/boat1obj.obj")
Model.load_model("lighthouse", "models/Beacon.obj")
Texture.load_texture("water", "textures/water.png")
Material.load_material("shiny", 256.0, 4.0)
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
		0, 2, 1, 1, 2, 3
	}
)
