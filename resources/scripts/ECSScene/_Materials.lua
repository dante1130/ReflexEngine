Model.load_model("cat", "models/12221_Cat_v1_l3.obj")
Material.load_material("shiny", 256.0, 4.0)
Skybox.load_skybox("nightsky", {
	right = "textures/skyboxes/nightsky/nightsky_rt.tga",
	left = "textures/skyboxes/nightsky/nightsky_lf.tga",
	top = "textures/skyboxes/nightsky/nightsky_up.tga",
	bottom = "textures/skyboxes/nightsky/nightsky_dn.tga",
	front = "textures/skyboxes/nightsky/nightsky_bk.tga",
	back = "textures/skyboxes/nightsky/nightsky_ft.tga"
})
